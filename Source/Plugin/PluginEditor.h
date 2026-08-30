#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class YM2203SynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit YM2203SynthAudioProcessorEditor(YM2203SynthAudioProcessor&);
    ~YM2203SynthAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    YM2203SynthAudioProcessor& processor;
    
    juce::TextButton loadButton{"Load VGZ"};
    juce::TextButton playButton{"Play"};
    juce::TextButton stopButton{"Stop"};
    juce::Label statusLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(YM2203SynthAudioProcessorEditor)
};
