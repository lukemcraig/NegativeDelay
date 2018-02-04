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
	// This is where our plugin�s editor size is set.
	setSize(400, 400);
	// these define the parameters of our slider object
	negativeDelayTimeSlider_.setSliderStyle(Slider::LinearHorizontal);
	//(double)NegativeDelayAudioProcessor::pluginLatency_
	negativeDelayTimeSlider_.setRange(0.0, processor.pluginLatency_, 1.0);
	negativeDelayTimeSlider_.setTextBoxStyle(Slider::TextBoxLeft, false, 90, negativeDelayTimeSlider_.getTextBoxHeight());
	negativeDelayTimeSlider_.setPopupDisplayEnabled(true, false, this);
	negativeDelayTimeSlider_.setTextValueSuffix(" Negative Delay Time");
	negativeDelayTimeSlider_.setValue(0.0);

	// this function adds the slider to the editor
	addAndMakeVisible(&negativeDelayTimeSlider_);

	// add the listener to the slider
	negativeDelayTimeSlider_.addListener(this);

	// these define the parameters of our slider object
	delayTimeSlider_.setSliderStyle(Slider::LinearHorizontal);
	//(double)NegativeDelayAudioProcessor::pluginLatency_
	delayTimeSlider_.setRange(0.0, processor.pluginLatency_, 1.0);
	delayTimeSlider_.setTextBoxStyle(Slider::TextBoxLeft, false, 90, delayTimeSlider_.getTextBoxHeight());
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

	delayReadPositionSlider_.setSliderStyle(Slider::LinearHorizontal);
	delayReadPositionSlider_.setRange(0.0, processor.pluginLatency_, 1.0);
	delayReadPositionSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);	
	delayReadPositionSlider_.setValue(0.0);

	addAndMakeVisible(&delayReadPositionSlider_);

	delayWritePositionSlider_.setSliderStyle(Slider::LinearHorizontal);
	delayWritePositionSlider_.setRange(0.0, processor.pluginLatency_, 1.0);
	delayWritePositionSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	delayWritePositionSlider_.setValue(0.0);

	addAndMakeVisible(&delayWritePositionSlider_);

	millisecondsLabel_.setFont(Font(28.0f, Font::bold));	
	millisecondsLabel_.setText("0 ms", dontSendNotification);
	addAndMakeVisible(&millisecondsLabel_);

	bpmLabel_.setFont(Font(28.0f, Font::bold));
	bpmLabel_.setText("bpm", dontSendNotification);
	addAndMakeVisible(&bpmLabel_);

	millisecondsSlider_.setSliderStyle(Slider::LinearHorizontal);
	millisecondsSlider_.setRange(0.0, (processor.pluginLatency_/processor.getSampleRate())*1000.0, 0.01);
	millisecondsSlider_.setTextBoxStyle(Slider::TextBoxLeft, false, 90, millisecondsSlider_.getTextBoxHeight());
	millisecondsSlider_.setTextValueSuffix(" ms");
	millisecondsSlider_.setValue(0.0);

	addAndMakeVisible(&millisecondsSlider_);

	// add the listener to the slider
	millisecondsSlider_.addListener(this);

	initializeNoteDurationHashMap();
	int j = 0;
	for (HashMap<String, double>::Iterator i(noteDurationHashMap_); i.next();)
		noteDurationComboBox_.addItem(i.getKey(), ++j);

	addAndMakeVisible(&noteDurationComboBox_);
	noteDurationComboBox_.addListener(this);

	startTimerHz(10);
}

NegativeDelayAudioProcessorEditor::~NegativeDelayAudioProcessorEditor()
{
}

//==============================================================================
void NegativeDelayAudioProcessorEditor::initializeNoteDurationHashMap() {
	noteDurationHashMap_.set("1/64 T", 1.0 / 96.0);
	noteDurationHashMap_.set("1/64", 0.015625);
	noteDurationHashMap_.set("1/32 T", 1.0 / 48.0);
	noteDurationHashMap_.set("1/32", 0.03125);
	noteDurationHashMap_.set("1/16 T", 1.0/24.0);
	noteDurationHashMap_.set("1/16", 0.0625);
	noteDurationHashMap_.set("1/8 T", 1.0 /12.0);
	noteDurationHashMap_.set("1/8", 0.125);
	noteDurationHashMap_.set("1/4 T", 1.0 /6.0);
	noteDurationHashMap_.set("1/4", 0.25);
	noteDurationHashMap_.set("1/2 T", 1.0 /3.0);
	noteDurationHashMap_.set("1/2", 0.5);
	noteDurationHashMap_.set("1/2 D", 0.5);
	noteDurationHashMap_.set("1 Bar T", 2.0 /3.0);
	noteDurationHashMap_.set("1 Bar", 1.0);
}

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
	negativeDelayTimeSlider_.setBounds(40, 10, 300, 20);

	delayTimeSlider_.setBounds(40, 30, 300, 20);

	delayWritePositionLabel_.setBounds(40, 50, 300, 40);
	delayWritePositionSlider_.setBounds(40, 90, 300, 20);

	delayReadPositionLabel_.setBounds(40, 110, 300, 40);
	delayReadPositionSlider_.setBounds(40, 150, 300, 20);

	millisecondsLabel_.setBounds(40,170,300,40);
	bpmLabel_.setBounds(40, 210, 300, 40);

	millisecondsSlider_.setBounds(40, 250, 300, 20);

	noteDurationComboBox_.setBounds(40, 270, 300, 20);
}

void NegativeDelayAudioProcessorEditor::comboBoxChanged(ComboBox* comboBox)
{	
	if (comboBox == &noteDurationComboBox_) {
		double barInMS = 240000.0 / processor.lastPosInfo.bpm;
		String selectedText = comboBox->getText();
		//int denominator = comboBox->getSelectedId();
		//double selectedDuration = 1.0 / denominator;
		double selectedDuration = noteDurationHashMap_.operator[](selectedText);
		double ms = selectedDuration * barInMS;
		millisecondsSlider_.setValue(ms);
	}
}

void NegativeDelayAudioProcessorEditor::sliderValueChanged(Slider * slider)
{
	if (slider == &delayTimeSlider_) // if the pointer slider is pointing at the memory address where delayTimeSlider_ is stored
		processor.setDelayTime((int)(delayTimeSlider_.getValue()));
	if (slider == &negativeDelayTimeSlider_) 
		delayTimeSlider_.setValue(processor.pluginLatency_-negativeDelayTimeSlider_.getValue());
	if (slider == &millisecondsSlider_)
		negativeDelayTimeSlider_.setValue(millisecondsSlider_.getValue() * processor.getSampleRate()/1000.0);
	millisecondsLabel_.setText("-"+String((negativeDelayTimeSlider_.getValue()/processor.getSampleRate()) * 1000)+" ms", dontSendNotification);
}

void NegativeDelayAudioProcessorEditor::timerCallback() {
	delayReadPositionLabel_.setText("dpr: " + String(processor.delayReadPosition_), dontSendNotification);
	delayWritePositionLabel_.setText("dpw: " + String(processor.delayWritePosition_), dontSendNotification);

	delayWritePositionSlider_.setValue(processor.delayWritePosition_);
	delayReadPositionSlider_.setValue(processor.delayReadPosition_);

	updateTimecodeDisplay(processor.lastPosInfo);
}

void NegativeDelayAudioProcessorEditor::updateTimecodeDisplay(AudioPlayHead::CurrentPositionInfo pos)
{
	bpmLabel_.setText(String(pos.bpm)+" bpm",dontSendNotification);
}
