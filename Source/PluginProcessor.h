/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class NegativeDelayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    NegativeDelayAudioProcessor();
    ~NegativeDelayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
	void setDelayReadPosition();
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	void setDelayTime(int newDelayTime);

	static const int pluginLatency_ = 192000; //1 bar of 4/4 in 60BPM at 48kHz (4000ms)
	double delayTime_;
	int delayReadPosition_;
	int delayWritePosition_;

	AudioPlayHead::CurrentPositionInfo lastPosInfo;

	double sampleRate_;
	AudioParameterFloat* delayTimeParam_;
private:
	void updateCurrentTimeInfoFromHost();
	//==============================================================================
	
	//==============================================================================
	AudioSampleBuffer delayBuffer_;
	int delayBufferLength_;
	
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NegativeDelayAudioProcessor)
};
