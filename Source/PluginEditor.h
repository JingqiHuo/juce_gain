/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Gain_plugin_demoAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Gain_plugin_demoAudioProcessorEditor (Gain_plugin_demoAudioProcessor&);
    ~Gain_plugin_demoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Gain_plugin_demoAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Gain_plugin_demoAudioProcessorEditor)
};
