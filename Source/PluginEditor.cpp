/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveNetVaAudioProcessorEditor::WaveNetVaAudioProcessorEditor (WaveNetVaAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(loadButton);
    loadButton.setButtonText("LOAD MODEL");
    loadButton.addListener(this);
    addAndMakeVisible(preGainKnob);
    preGainKnob.addListener(this);
    preGainKnob.setRange(-24.0, 24.0);
    preGainKnob.setValue(0.0);
    preGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    preGainKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    preGainKnob.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(postGainKnob);
    postGainKnob.addListener(this);
    postGainKnob.setRange(-24.0, 24.0);
    postGainKnob.setValue(0.0);
    postGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    postGainKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20 );
    postGainKnob.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(preGainLabel);
    preGainLabel.setText("Pre Gain", juce::NotificationType::dontSendNotification);
    preGainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(postGainLabel);
    postGainLabel.setText("Post Gain", juce::NotificationType::dontSendNotification);
    postGainLabel.setJustificationType(juce::Justification::centred);
    auto font = postGainLabel.getFont();
    float height = font.getHeight();
    font.setHeight(height*0.75);
    postGainLabel.setFont(font);
    preGainLabel.setFont(font);
    setSize (400, 300);
}

WaveNetVaAudioProcessorEditor::~WaveNetVaAudioProcessorEditor()
{
}

//==============================================================================
void WaveNetVaAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
}

void WaveNetVaAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    loadButton.setBounds(50, 150, getWidth()-100, 20);
    preGainKnob.setBounds(25, 50, 50, 85);
    postGainKnob.setBounds(325, 50, 50, 85);
    preGainLabel.setBounds(10,35, 80, 10);
    postGainLabel.setBounds(310,35, 80, 10);

}

void WaveNetVaAudioProcessorEditor::buttonClicked(juce::Button *button)
{
    if (button == &loadButton)
        loadButtonClicked();
}

void WaveNetVaAudioProcessorEditor::loadButtonClicked()
{
    FileChooser chooser ("Load a trained WaveNet model...",
                         {},
                         "*.json");
    if (chooser.browseForFileToOpen())
    {
        File file = chooser.getResult();
        processor.loadConfig(file);
    }
}

void WaveNetVaAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &preGainKnob)
        processor.setPreGain(slider->getValue());
    else if (slider == &postGainKnob)
        processor.setPostGain(slider->getValue());
}
