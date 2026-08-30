#pragma once
#include <JuceHeader.h>
#include "../YM2203_Emulator/YM2203.h"
#include "../VGZParser/VGZParser.h"

class YM2203SynthAudioProcessor : public juce::AudioProcessor
{
public:
    YM2203SynthAudioProcessor();
    ~YM2203SynthAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock&) override;
    void setStateInformation(const void*, int) override;

    YM2203& getYM2203() { return ym2203; }
    VGZParser& getVGZParser() { return vgzParser; }

    void loadVGZFile(const juce::String& filePath);
    void playVGZFile();
    void stopPlayback();

private:
    YM2203 ym2203;
    VGZParser vgzParser;
    
    size_t currentCommandIndex = 0;
    uint32_t delayCounter = 0;
    bool isPlaying = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(YM2203SynthAudioProcessor)
};
