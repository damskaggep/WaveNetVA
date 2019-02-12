/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class WaveNetVaAudioProcessorEditor  : public AudioProcessorEditor,
                                       private Button::Listener,
                                       private Slider::Listener
{
public:
    WaveNetVaAudioProcessorEditor (WaveNetVaAudioProcessor&);
    ~WaveNetVaAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WaveNetVaAudioProcessor& processor;
    TextButton loadButton;
    Slider preGainKnob;
    Slider postGainKnob;
    Label preGainLabel;
    Label postGainLabel;

    virtual void buttonClicked(Button* button) override;
    virtual void sliderValueChanged(Slider* slider) override;
    void loadButtonClicked();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveNetVaAudioProcessorEditor)
};
