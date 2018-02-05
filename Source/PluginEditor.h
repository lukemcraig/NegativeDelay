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
class NegativeDelayAudioProcessorEditor  : public AudioProcessorEditor, 
	private Slider::Listener, 
	private Button::Listener,
	private Timer
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

	void buttonClicked(Button* button) override;
	
	void noteDurationToMS(double factor);
	void updateBPMLabel(AudioPlayHead::CurrentPositionInfo);
	void createDurationMenu();
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

	TextButton durationButton_;

	struct NoteDuration {
		String label; // add T for triplets, D for Dotted
		double factor; // 1 bar = 1.0; 1/2 note =0.5
	};
	static const int numberOfNoteDurations_ = 20;
	struct NoteDuration noteDurations_[numberOfNoteDurations_];

	int straightNoteIndexStart_;
	int straightNoteIndexEnd_;

	int tripletNoteIndexStart_;
	int tripletNoteIndexEnd_;

	int dottedNoteIndexStart_;
	int dottedNoteIndexEnd_;

	PopupMenu durationMenu_;
	Slider durationSlider_;

	TextButton straightNotesButton_;
	TextButton tripletNotesButton_;
	TextButton dottedNotesButton_;

	static void durationMenuCallBack(int result, NegativeDelayAudioProcessorEditor* editor);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NegativeDelayAudioProcessorEditor)
};
