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
	// This is where our plugin’s editor size is set.
	setSize(400, 400);

	// these define the parameters of our slider object
	delayTimeSlider_.setSliderStyle(Slider::LinearHorizontal);
	//(double)NegativeDelayAudioProcessor::pluginLatency_
	delayTimeSlider_.setRange(-(double)NegativeDelayAudioProcessor::pluginLatency_, 0.0, 1.0);
	delayTimeSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	delayTimeSlider_.setPopupDisplayEnabled(true, false, this);
	delayTimeSlider_.setTextValueSuffix(" Delay Time");
	delayTimeSlider_.setValue(-(double)NegativeDelayAudioProcessor::pluginLatency_/2.0);

	// this function adds the slider to the editor
	addAndMakeVisible(&delayTimeSlider_);

	// add the listener to the slider
	delayTimeSlider_.addListener(this);
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
	delayTimeSlider_.setBounds(40, 30, 300, 100);
}

void NegativeDelayAudioProcessorEditor::sliderValueChanged(Slider * slider)
{
	processor.delayTime_ = processor.pluginLatency_ - delayTimeSlider_.getValue();
}
