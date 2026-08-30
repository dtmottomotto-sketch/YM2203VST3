#pragma once

namespace YM2203Params
{
    // YM2203 Register Addresses
    enum class Register : unsigned char
    {
        // Channel A
        FNUM_A_LSB = 0x00,
        FNUM_A_MSB = 0x01,
        FNUM_B_LSB = 0x02,
        FNUM_B_MSB = 0x03,
        FNUM_C_LSB = 0x04,
        FNUM_C_MSB = 0x05,
        
        // Noise/LFO
        NOISE_FREQ = 0x06,
        LFO_CTRL = 0x07,
        
        // Envelope
        ENV_FREQ_LSB = 0x08,
        ENV_FREQ_MSB = 0x09,
        ENV_SHAPE = 0x0A,
        
        // Channel Settings
        CH_A_CTRL = 0x0B,
        CH_B_CTRL = 0x0C,
        CH_C_CTRL = 0x0D,
        
        // Port I/O
        PORT_A = 0x0E,
        PORT_B = 0x0F,
    };

    // Channel Control Bits
    struct ChannelControl
    {
        unsigned char level : 4;    // Amplitude (0-15)
        unsigned char mode : 1;     // 0=Tone, 1=Noise
        unsigned char envelope : 1; // 0=Manual, 1=Envelope
        unsigned char reserved : 2;
    };

    // LFO Control
    enum class LFOMode
    {
        OFF = 0,
        ON = 1
    };

    // Envelope Shapes
    enum class EnvelopeShape
    {
        DECAY = 0,
        SUSTAIN = 4,
        REPEAT = 8,
        HOLD = 12
    };
}
