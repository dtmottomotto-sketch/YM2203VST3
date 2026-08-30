#include "PluginProcessor.h"
#include "PluginEditor.h"

YM2203SynthAudioProcessor::YM2203SynthAudioProcessor()
    : ym2203(4000000)
{
}

YM2203SynthAudioProcessor::~YM2203SynthAudioProcessor()
{
}

void YM2203SynthAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    ym2203.reset();
}

void YM2203SynthAudioProcessor::releaseResources()
{
}

void YM2203SynthAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    std::vector<int16_t> tempBuffer(buffer.getNumSamples());
    ym2203.generateBuffer(tempBuffer.data(), buffer.getNumSamples());

    if (isPlaying && !vgzParser.getCommands().empty()) {
        const auto& commands = vgzParser.getCommands();
        
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            delayCounter--;
            
            while (delayCounter <= 0 && currentCommandIndex < commands.size()) {
                const auto& cmd = commands[currentCommandIndex];
                
                if (cmd.command == 0x52 || cmd.command == 0x53) {
                    ym2203.writeReg(cmd.reg, cmd.data);
                }
                
                delayCounter += cmd.delay;
                currentCommandIndex++;
            }
            
            if (currentCommandIndex >= commands.size()) {
                isPlaying = false;
                break;
            }
        }
    }

    for (int channel = 0; channel < totalNumOutputChannels; ++channel) {
        auto* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            channelData[sample] = tempBuffer[sample] / 32768.0f;
        }
    }
}

juce::AudioProcessorEditor* YM2203SynthAudioProcessor::createEditor()
{
    return new YM2203SynthAudioProcessorEditor(*this);
}

void YM2203SynthAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
}

void YM2203SynthAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
}

void YM2203SynthAudioProcessor::loadVGZFile(const juce::String& filePath)
{
    vgzParser.reset();
    vgzParser.parseFile(filePath.toStdString());
    currentCommandIndex = 0;
    delayCounter = 0;
}

void YM2203SynthAudioProcessor::playVGZFile()
{
    isPlaying = true;
    currentCommandIndex = 0;
    delayCounter = 0;
    ym2203.reset();
}

void YM2203SynthAudioProcessor::stopPlayback()
{
    isPlaying = false;
    ym2203.reset();
}
