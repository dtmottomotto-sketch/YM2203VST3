#pragma once
#include <cstdint>
#include <string>
#include <vector>

struct VGMCommand
{
    uint8_t command;
    uint8_t port;
    uint8_t reg;
    uint8_t data;
    uint32_t delay;
};

class VGZParser
{
public:
    VGZParser();
    ~VGZParser();
    
    bool parseFile(const std::string& filePath);
    bool parseFromMemory(const uint8_t* data, size_t size);
    
    const std::vector<VGMCommand>& getCommands() const { return commands; }
    uint32_t getSampleRate() const { return sampleRate; }
    uint32_t getClockSpeed() const { return clockSpeed; }
    
    void reset();
    
private:
    std::vector<VGMCommand> commands;
    uint32_t sampleRate;
    uint32_t clockSpeed;
    
    bool parseVGM(const uint8_t* data, size_t size);
    bool parseVGZ(const uint8_t* data, size_t size);
    
    uint32_t readLE32(const uint8_t* data, size_t offset);
    uint16_t readLE16(const uint8_t* data, size_t offset);
};
