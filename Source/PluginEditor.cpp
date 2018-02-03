/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
NegativeDelayAudioProcessorEditor::NegativeDelayAudioProcessorEditor (NegativeDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	setResizable(true,true);
	// This is where our plugin’s editor size is set.
	setSize(400, 400);

	// these define the parameters of our slider object
	delayTimeSlider_.setSliderStyle(Slider::LinearHorizontal);
	//(double)NegativeDelayAudioProcessor::pluginLatency_
	delayTimeSlider_.setRange(0.0, processor.getLatencySamples(), 1.0);
	delayTimeSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	delayTimeSlider_.setPopupDisplayEnabled(true, false, this);
	delayTimeSlider_.setTextValueSuffix(" Delay Time");
	delayTimeSlider_.setValue(0.0);

	// this function adds the slider to the editor
	addAndMakeVisible(&delayTimeSlider_); // why does this use the address-of operator?

	// add the listener to the slider
	delayTimeSlider_.addListener(this);

	delayReadPositionLabel_.setFont(Font(28.0f, Font::bold));
	delayWritePositionLabel_.setFont(Font(28.0f, Font::bold));

	addAndMakeVisible(&delayReadPositionLabel_);	
	addAndMakeVisible(&delayWritePositionLabel_);

	startTimerHz(10);
}

NegativeDelayAudioProcessorEditor::~NegativeDelayAudioProcessorEditor()
{
}

//==============================================================================
void NegativeDelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void NegativeDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	delayTimeSlider_.setBounds(40, 30, 300, 20);
	delayReadPositionLabel_.setBounds(40, 50, 300, 40);
	delayWritePositionLabel_.setBounds(40, 90, 300, 40);
}

void NegativeDelayAudioProcessorEditor::sliderValueChanged(Slider * slider)
{
	processor.delayTime_ = delayTimeSlider_.getValue();	
}

void NegativeDelayAudioProcessorEditor::timerCallback() {
	delayReadPositionLabel_.setText("dpr: " + String(processor.delayReadPosition_), dontSendNotification);
	delayWritePositionLabel_.setText("dpw: " + String(processor.delayWritePosition_), dontSendNotification);
}
