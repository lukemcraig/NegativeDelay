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
class NegativeDelayAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener, private ComboBox::Listener, private Timer
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
	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
	void updateTimecodeDisplay(AudioPlayHead::CurrentPositionInfo);

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NegativeDelayAudioProcessor& processor;

	Slider negativeDelayTimeSlider_;
	Slider delayTimeSlider_;
	Label delayReadPositionLabel_;
	Label delayWritePositionLabel_;
	Slider delayReadPositionSlider_;
	Slider delayWritePositionSlider_;

	Label millisecondsLabel_;
	Slider millisecondsSlider_;
	Label bpmLabel_;

	ComboBox noteDurationComboBox_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NegativeDelayAudioProcessorEditor)
};
