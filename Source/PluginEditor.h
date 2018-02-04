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
	private ComboBox::Listener, 
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
	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
	void buttonClicked(Button* button) override;
	

	void updateTimecodeDisplay(AudioPlayHead::CurrentPositionInfo);
	void initializeNoteDurationHashMap();

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
	HashMap<String, double> noteDurationHashMap_;

	TextButton durationButton_;

	PopupMenu getDurationMenu()
	{

		PopupMenu durationMenu;

		PopupMenu straightSubMenu;
		straightSubMenu.addItem(1, "1/64");
		straightSubMenu.addItem(2, "1/32");
		straightSubMenu.addItem(3, "1/16");
		straightSubMenu.addItem(4, "1/8");
		straightSubMenu.addItem(5, "1/4");
		straightSubMenu.addItem(6, "1/2");
		straightSubMenu.addItem(7, "1 Bar");
		durationMenu.addSubMenu("Straight", straightSubMenu);
		
		PopupMenu tripletSubMenu;
		tripletSubMenu.addItem(1, "1/64 T");
		tripletSubMenu.addItem(2, "1/32 T");
		tripletSubMenu.addItem(3, "1/16 T");
		tripletSubMenu.addItem(4, "1/8 T");
		tripletSubMenu.addItem(5, "1/4 T");
		tripletSubMenu.addItem(6, "1/2 T");
		tripletSubMenu.addItem(7, "1 Bar T");
		durationMenu.addSubMenu("Triplet", tripletSubMenu);

		PopupMenu dottedSubMenu;
		dottedSubMenu.addItem(1, "1/64 D");
		dottedSubMenu.addItem(2, "1/32 D");
		dottedSubMenu.addItem(3, "1/16 D");
		dottedSubMenu.addItem(4, "1/8 D");
		dottedSubMenu.addItem(5, "1/4 D");
		dottedSubMenu.addItem(6, "1/2 D");
		durationMenu.addSubMenu("Dotted", dottedSubMenu);

		return durationMenu;
	}

	static void testcallback(int result, Slider* slider);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NegativeDelayAudioProcessorEditor)
};
