#include "YM2203.h"
#include <cmath>

YM2203::YM2203(uint32_t clock)
    : sampleClock(clock), clockCounter(0), noiseRegister(0x1)
{
    std::memset(registers, 0, sizeof(registers));
    std::memset(&envelope, 0, sizeof(envelope));
    std::memset(&lfo, 0, sizeof(lfo));
    std::memset(channels, 0, sizeof(channels));
    reset();
}

YM2203::~YM2203()
{
}

void YM2203::reset()
{
    std::memset(registers, 0, sizeof(registers));
    std::memset(&envelope, 0, sizeof(envelope));
    std::memset(&lfo, 0, sizeof(lfo));
    std::memset(channels, 0, sizeof(channels));
    noiseRegister = 0x1;
    clockCounter = 0;
}

void YM2203::writeReg(uint8_t reg, uint8_t data)
{
    if (reg >= 0x10) return;
    
    registers[reg] = data;
    
    switch (reg) {
        case 0x00: // FNUM_A_LSB
        case 0x01: // FNUM_A_MSB
            channels[0].fnum = (registers[0x01] << 8) | registers[0x00];
            break;
            
        case 0x02: // FNUM_B_LSB
        case 0x03: // FNUM_B_MSB
            channels[1].fnum = (registers[0x03] << 8) | registers[0x02];
            break;
            
        case 0x04: // FNUM_C_LSB
        case 0x05: // FNUM_C_MSB
            channels[2].fnum = (registers[0x05] << 8) | registers[0x04];
            break;
            
        case 0x06: // NOISE_FREQ
            // Noise frequency setting
            break;
            
        case 0x07: // LFO_CTRL
            lfo.control = data;
            break;
            
        case 0x08: // ENV_FREQ_LSB
        case 0x09: // ENV_FREQ_MSB
            envelope.freq = (registers[0x09] << 8) | registers[0x08];
            break;
            
        case 0x0A: // ENV_SHAPE
            envelope.shape = data;
            envelope.counter = 0;
            break;
            
        case 0x0B: // CH_A_CTRL
            channels[0].control = data;
            channels[0].volume = data & 0x0F;
            break;
            
        case 0x0C: // CH_B_CTRL
            channels[1].control = data;
            channels[1].volume = data & 0x0F;
            break;
            
        case 0x0D: // CH_C_CTRL
            channels[2].control = data;
            channels[2].volume = data & 0x0F;
            break;
    }
}

uint8_t YM2203::readReg(uint8_t reg)
{
    if (reg >= 0x10) return 0;
    return registers[reg];
}

int16_t YM2203::generateSample()
{
    int32_t output = 0;
    
    // Generate tone for each channel
    for (int ch = 0; ch < 3; ch++) {
        updateChannel(ch);
        output += channels[ch].output;
    }
    
    // Mix and clamp
    output = (output * 2730) / 3; // Normalize
    if (output > 32767) output = 32767;
    if (output < -32768) output = -32768;
    
    return static_cast<int16_t>(output);
}

void YM2203::generateBuffer(int16_t* buffer, int numSamples)
{
    for (int i = 0; i < numSamples; i++) {
        buffer[i] = generateSample();
    }
}

int16_t YM2203::calculateTone(int ch)
{
    if (channels[ch].fnum == 0) return 0;
    
    // Simple sine wave generation
    const float freq = (channels[ch].fnum * sampleClock) / (1 << (20 - channels[ch].block));
    clockCounter++;
    
    float phase = static_cast<float>(clockCounter) * freq / sampleClock;
    int16_t sample = static_cast<int16_t>(std::sin(phase * 2.0f * 3.14159265f) * 32767.0f);
    
    // Apply volume
    sample = (sample * (channels[ch].volume + 1)) / 16;
    
    return sample;
}

int16_t YM2203::calculateNoise()
{
    noiseCounter++;
    if (noiseCounter >= 32) {
        noiseCounter = 0;
        uint16_t feedback = ((noiseRegister >> 0) ^ (noiseRegister >> 2)) & 1;
        noiseRegister = ((noiseRegister >> 1) | (feedback << 16));
    }
    
    return (noiseRegister & 1) ? 16384 : -16384;
}

int16_t YM2203::calculateEnvelope()
{
    if (envelope.freq == 0) return 0;
    
    envelope.counter++;
    uint32_t envPeriod = (envelope.freq * sampleClock) / 256;
    
    if (envelope.counter >= envPeriod) {
        envelope.counter = 0;
        
        switch (envelope.shape) {
            case 0: // Decay
                envelope.level -= 256;
                break;
            case 4: // Sustain
                envelope.level = 0;
                break;
            case 8: // Repeat
                if (envelope.level <= 0) envelope.level = 32767;
                else envelope.level -= 256;
                break;
            case 12: // Hold
                envelope.level = 32767;
                break;
        }
    }
    
    if (envelope.level < 0) envelope.level = 0;
    if (envelope.level > 32767) envelope.level = 32767;
    
    return envelope.level;
}

void YM2203::updateChannel(int ch)
{
    int16_t sample = 0;
    
    if (channels[ch].control & 0x10) {
        // Noise mode
        sample = calculateNoise();
    } else {
        // Tone mode
        sample = calculateTone(ch);
    }
    
    if (channels[ch].control & 0x20) {
        // Envelope mode
        int16_t env = calculateEnvelope();
        sample = (sample * env) / 32767;
    }
    
    channels[ch].output = sample;
}

void YM2203::saveState(uint8_t* state, size_t& size)
{
    size = sizeof(registers) + sizeof(channels) + sizeof(envelope) + sizeof(lfo);
    std::memcpy(state, registers, sizeof(registers));
    std::memcpy(state + sizeof(registers), &channels, sizeof(channels));
    std::memcpy(state + sizeof(registers) + sizeof(channels), &envelope, sizeof(envelope));
    std::memcpy(state + sizeof(registers) + sizeof(channels) + sizeof(envelope), &lfo, sizeof(lfo));
}

void YM2203::loadState(const uint8_t* state, size_t size)
{
    if (size < sizeof(registers) + sizeof(channels) + sizeof(envelope) + sizeof(lfo)) return;
    
    std::memcpy(registers, state, sizeof(registers));
    std::memcpy(&channels, state + sizeof(registers), sizeof(channels));
    std::memcpy(&envelope, state + sizeof(registers) + sizeof(channels), sizeof(envelope));
    std::memcpy(&lfo, state + sizeof(registers) + sizeof(channels) + sizeof(envelope), sizeof(lfo));
}
