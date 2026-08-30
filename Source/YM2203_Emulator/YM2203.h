#pragma once
#include <cstdint>
#include <cstring>

class YM2203
{
public:
    YM2203(uint32_t clock = 4000000); // PC-8801mk2SR: 4MHz
    ~YM2203();
    
    void reset();
    void writeReg(uint8_t reg, uint8_t data);
    uint8_t readReg(uint8_t reg);
    
    // Audio output
    int16_t generateSample();
    void generateBuffer(int16_t* buffer, int numSamples);
    
    // State management
    void saveState(uint8_t* state, size_t& size);
    void loadState(const uint8_t* state, size_t size);
    
private:
    uint32_t sampleClock;
    uint32_t clockCounter;
    
    // Registers
    uint8_t registers[0x10];
    
    // Channel data
    struct Channel {
        uint16_t fnum;
        uint8_t block;
        uint8_t volume;
        uint8_t control;
        int16_t output;
    } channels[3];
    
    // Envelope
    struct Envelope {
        uint16_t freq;
        uint8_t shape;
        uint32_t counter;
        int16_t level;
    } envelope;
    
    // LFO
    struct LFO {
        uint8_t freq;
        uint8_t control;
        uint32_t counter;
    } lfo;
    
    // Noise
    uint32_t noiseCounter;
    uint16_t noiseRegister;
    
    // Internal methods
    void updateChannel(int ch);
    int16_t calculateTone(int ch);
    int16_t calculateNoise();
    int16_t calculateEnvelope();
};
