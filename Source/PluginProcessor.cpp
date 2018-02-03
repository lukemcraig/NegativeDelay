/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
NegativeDelayAudioProcessor::NegativeDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{	
	//setLatencySamples(pluginLatency_);
	delayReadPosition_ = 0;
	delayWritePosition_ = 0;
	delayTime_ = 0;
}

NegativeDelayAudioProcessor::~NegativeDelayAudioProcessor()
{
}

//==============================================================================
const String NegativeDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NegativeDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NegativeDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NegativeDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NegativeDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NegativeDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NegativeDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NegativeDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String NegativeDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void NegativeDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//void NegativeDelayAudioProcessor::setLatencySamples(int newLatency)
//{
//}

//==============================================================================
void NegativeDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	//delayBufferLength_ = (int)(2.0*sampleRate);
	delayBufferLength_ = pluginLatency_+1;
	if (delayBufferLength_ < 1)
		delayBufferLength_ = 1;

	delayBuffer_.setSize(2, delayBufferLength_);
	delayBuffer_.clear();

	setDelayReadPosition();
}

void NegativeDelayAudioProcessor::setDelayReadPosition()
{
	delayReadPosition_ = (int)(delayWritePosition_ - (int)(delayTime_)+delayBufferLength_) % delayBufferLength_;
}

void NegativeDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NegativeDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void NegativeDelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	const int totalNumInputChannels = getTotalNumInputChannels();
	const int totalNumOutputChannels = getTotalNumOutputChannels();
	const int numSamples = buffer.getNumSamples();

	int dpr; // delay pointer read
	int dpw; // delay pointer write

	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		float* channelData = buffer.getWritePointer(channel);
		float* delayData = delayBuffer_.getWritePointer(channel);
		// copy the variables so that the channels are independent
		dpr = delayReadPosition_;
		dpw = delayWritePosition_;

		for (int sample = 0; sample < numSamples; ++sample) {
			// the input sample is written to delayData at the write pointer
			delayData[dpw] = channelData[sample];

			// the output sample is read from delayData at the read pointer
			channelData[sample] = delayData[dpr];

			// the read and write pointers are incremented
			if (++dpw >= delayBufferLength_)
				dpw = 0;
			if (++dpr >= delayBufferLength_)
				dpr = 0;
		}
	}
	delayReadPosition_ = dpr;
	delayWritePosition_ = dpw;

	for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i) {
		buffer.clear(i, 0, buffer.getNumSamples());
	}
}

//==============================================================================
bool NegativeDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NegativeDelayAudioProcessor::createEditor()
{
    return new NegativeDelayAudioProcessorEditor (*this);
}

//==============================================================================
void NegativeDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NegativeDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void NegativeDelayAudioProcessor::setDelayTime(int newDelayTime)
{
	delayTime_ = newDelayTime;
	setDelayReadPosition();
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NegativeDelayAudioProcessor();
}
