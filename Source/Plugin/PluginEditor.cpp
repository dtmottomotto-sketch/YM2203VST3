#include "PluginEditor.h"

YM2203SynthAudioProcessorEditor::YM2203SynthAudioProcessorEditor(YM2203SynthAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    setSize(400, 300);
    
    addAndMakeVisible(loadButton);
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(statusLabel);
    
    loadButton.onClick = [this] {
        juce::FileChooser chooser("Load VGZ file", juce::File::getSpecialLocation(juce::File::userDocumentsDirectory), "*.vgz;*.vgm");
        if (chooser.browseForFileToOpen()) {
            processor.loadVGZFile(chooser.getResult().getFullPathName());
            statusLabel.setText("Loaded: " + chooser.getResult().getFileName(), juce::dontSendNotification);
        }
    };
    
    playButton.onClick = [this] {
        processor.playVGZFile();
        statusLabel.setText("Playing...", juce::dontSendNotification);
    };
    
    stopButton.onClick = [this] {
        processor.stopPlayback();
        statusLabel.setText("Stopped", juce::dontSendNotification);
    };
    
    statusLabel.setText("Ready", juce::dontSendNotification);
}

YM2203SynthAudioProcessorEditor::~YM2203SynthAudioProcessorEditor()
{
}

void YM2203SynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void YM2203SynthAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(10);
    
    loadButton.setBounds(area.removeFromTop(40));
    playButton.setBounds(area.removeFromTop(40));
    stopButton.setBounds(area.removeFromTop(40));
    statusLabel.setBounds(area.removeFromTop(40));
}
