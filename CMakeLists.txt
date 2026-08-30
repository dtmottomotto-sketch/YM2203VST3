cmake_minimum_required(VERSION 3.20)
project(YM2203Synth VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JUCE_PATH "C:/JUCE" CACHE PATH "Path to JUCE")

add_subdirectory("${JUCE_PATH}" JUCE)

juce_add_plugin(YM2203Synth
    PRODUCT_NAME "YM2203Synth"
    COMPANY_NAME "YM2203VST3"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    PLUGIN_MANUFACTURER_CODE YM22
    PLUGIN_CODE YM22
    FORMATS VST3
    VST3_CATEGORIES "Instrument"
)

target_sources(YM2203Synth PRIVATE
    Source/YM2203_Emulator/YM2203.cpp
    Source/YM2203_Emulator/YM2203.h
    Source/VGZParser/VGZParser.cpp
    Source/VGZParser/VGZParser.h
    Source/Plugin/PluginProcessor.cpp
    Source/Plugin/PluginProcessor.h
    Source/Plugin/PluginEditor.cpp
    Source/Plugin/PluginEditor.h
    Source/PluginParams.h
)

target_include_directories(YM2203Synth PRIVATE
    Source/
    Source/YM2203_Emulator/
    Source/VGZParser/
    Source/Plugin/
)

target_link_libraries(YM2203Synth PRIVATE
    juce::juce_audio_processors
    juce::juce_gui_basics
    juce::juce_core
)
