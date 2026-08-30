#include "VGZParser.h"
#include <cstring>
#include <algorithm>
#include <cstdio>

VGZParser::VGZParser()
    : sampleRate(44100), clockSpeed(4000000)
{
}

VGZParser::~VGZParser()
{
}

uint32_t VGZParser::readLE32(const uint8_t* data, size_t offset)
{
    return data[offset] | (data[offset + 1] << 8) | (data[offset + 2] << 16) | (data[offset + 3] << 24);
}

uint16_t VGZParser::readLE16(const uint8_t* data, size_t offset)
{
    return data[offset] | (data[offset + 1] << 8);
}

bool VGZParser::parseFile(const std::string& filePath)
{
    FILE* file = fopen(filePath.c_str(), "rb");
    if (!file) return false;
    
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    std::vector<uint8_t> data(fileSize);
    fread(data.data(), 1, fileSize, file);
    fclose(file);
    
    if (fileSize >= 2 && data[0] == 0x1F && data[1] == 0x8B) {
        return parseVGZ(data.data(), fileSize);
    } else {
        return parseVGM(data.data(), fileSize);
    }
}

bool VGZParser::parseFromMemory(const uint8_t* data, size_t size)
{
    if (size < 2) return false;
    
    if (data[0] == 0x1F && data[1] == 0x8B) {
        return parseVGZ(data, size);
    } else {
        return parseVGM(data, size);
    }
}

bool VGZParser::parseVGM(const uint8_t* data, size_t size)
{
    if (size < 0x40) return false;
    
    if (std::memcmp(data, "Vgm ", 4) != 0) return false;
    
    uint32_t eofOffset = readLE32(data, 0x04);
    clockSpeed = readLE32(data, 0x08);
    sampleRate = readLE32(data, 0x18);
    
    if (sampleRate == 0) sampleRate = 44100;
    if (clockSpeed == 0) clockSpeed = 4000000;
    
    uint32_t dataOffset = 0x34;
    if (size >= 0x34) {
        uint32_t headerSize = readLE32(data, 0x34);
        if (headerSize > 0) dataOffset = 0x34 + headerSize;
    }
    
    uint32_t pos = dataOffset;
    uint32_t delay = 0;
    
    while (pos < size && pos < (eofOffset + 4)) {
        uint8_t cmd = data[pos++];
        
        switch (cmd) {
            case 0x50:
                if (pos + 1 < size) {
                    commands.push_back({cmd, 0, 0, data[pos], delay});
                    pos++;
                    delay = 0;
                }
                break;
                
            case 0x52:
            case 0x53:
                if (pos + 1 < size) {
                    uint8_t reg = data[pos++];
                    uint8_t val = data[pos++];
                    commands.push_back({cmd, (cmd == 0x52) ? 0 : 1, reg, val, delay});
                    delay = 0;
                }
                break;
                
            case 0x61:
                if (pos + 1 < size) {
                    delay += readLE16(data, pos);
                    pos += 2;
                }
                break;
                
            case 0x62:
                delay += 735;
                break;
                
            case 0x63:
                delay += 882;
                break;
                
            case 0x66:
                return true;
                
            default:
                if ((cmd & 0xF0) == 0x70) {
                    delay += (cmd & 0x0F) + 1;
                }
                break;
        }
    }
    
    return true;
}

bool VGZParser::parseVGZ(const uint8_t* data, size_t size)
{
    return false;
}

void VGZParser::reset()
{
    commands.clear();
    sampleRate = 44100;
    clockSpeed = 4000000;
}
