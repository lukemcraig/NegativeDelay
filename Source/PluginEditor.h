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
class NegativeDelayAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener, private Timer
{
public:
    NegativeDelayAudioProcessorEditor (NegativeDelayAudioProcessor&);
    ~NegativeDelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void timerCallback() override;

private:
	void sliderValueChanged(Slider* slider) override;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NegativeDelayAudioProcessor& processor;

	Slider negativeDelayTimeSlider_;
	Slider delayTimeSlider_;
	Label delayReadPositionLabel_;
	Label delayWritePositionLabel_;
	Slider delayReadPositionSlider_;
	Slider delayWritePositionSlider_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NegativeDelayAudioProcessorEditor)
};
