/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveNetVaAudioProcessor::WaveNetVaAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
        waveNet(1, 1, 1, 1, "linear", {1})
#endif
{
}

WaveNetVaAudioProcessor::~WaveNetVaAudioProcessor()
{
}

//==============================================================================
const String WaveNetVaAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WaveNetVaAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WaveNetVaAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WaveNetVaAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WaveNetVaAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WaveNetVaAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WaveNetVaAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WaveNetVaAudioProcessor::setCurrentProgram (int index)
{
}

const String WaveNetVaAudioProcessor::getProgramName (int index)
{
    return {};
}

void WaveNetVaAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void WaveNetVaAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    waveNet.prepareToPlay(samplesPerBlock);
}

void WaveNetVaAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WaveNetVaAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void WaveNetVaAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    buffer.applyGain(preGain);
    waveNet.process(buffer.getArrayOfReadPointers(), buffer.getArrayOfWritePointers(),
                    buffer.getNumSamples());
    buffer.applyGain(postGain);
    for (int ch = 1; ch < buffer.getNumChannels(); ++ch)
        buffer.copyFrom(ch, 0, buffer, 0, 0, buffer.getNumSamples());
}

//==============================================================================
bool WaveNetVaAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* WaveNetVaAudioProcessor::createEditor()
{
    return new WaveNetVaAudioProcessorEditor (*this);
}

//==============================================================================
void WaveNetVaAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WaveNetVaAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void WaveNetVaAudioProcessor::loadConfig(File configFile)
{
    this->suspendProcessing(true);
    WaveNetLoader loader (configFile);
    int numChannels = loader.numChannels;
    int inputChannels = loader.inputChannels;
    int outputChannels = loader.outputChannels;
    int filterWidth = loader.filterWidth;
    std::vector<int> dilations = loader.dilations;
    std::string activation = loader.activation;
    waveNet.setParams(inputChannels, outputChannels, numChannels, filterWidth, activation,
                      dilations);
    loader.loadVariables(waveNet);
    this->suspendProcessing(false);
}

void WaveNetVaAudioProcessor::setPreGain(float dbValue)
{
    preGain = decibelToLinear(dbValue);
}

void WaveNetVaAudioProcessor::setPostGain(float dbValue)
{
    postGain = decibelToLinear(dbValue);
}

float WaveNetVaAudioProcessor::decibelToLinear(float dbValue)
{
    return powf(10.0, dbValue/20.0);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WaveNetVaAudioProcessor();
}
