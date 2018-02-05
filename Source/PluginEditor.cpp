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


	createDurationMenu();

	durationButton_.setButtonText("Note Durations");
	durationButton_.setTriggeredOnMouseDown(true);
	durationButton_.addListener(this);
	addAndMakeVisible(durationButton_);

	startTimerHz(10);
}

NegativeDelayAudioProcessorEditor::~NegativeDelayAudioProcessorEditor()
{
	
}

//==============================================================================
void NegativeDelayAudioProcessorEditor::durationMenuCallBack(int result, NegativeDelayAudioProcessorEditor* editor)//HashMap<int, String> * noteDurationIntHashMap)
{

		if (result != 0) {
			String selectedDurationString = editor->noteDurations_[result - 1].label;
			editor->durationButton_.setButtonText(selectedDurationString);
			editor->noteDurationToMS(editor->noteDurations_[result - 1].factor);
		}

}

void NegativeDelayAudioProcessorEditor::buttonClicked(Button* button)
{
	if (button = &durationButton_) {
		durationMenu_.showMenuAsync(PopupMenu::Options().withTargetComponent(&durationButton_),
					ModalCallbackFunction::create(durationMenuCallBack, this));
	}
}

void NegativeDelayAudioProcessorEditor::createDurationMenu()
{
	//struct NoteDuration sixty_fourth = {"1/64", 0.015625};
	/*struct NoteDuration noteDurations[20];*/
	//noteDurations[0] = { /*label*/ "1/64", /*factor*/ 0.015625 };

	noteDurations_[0].label = "1/64";		noteDurations_[0].factor = 0.015625;
	noteDurations_[1].label = "1/32";		noteDurations_[1].factor = 0.03125;
	noteDurations_[2].label = "1/16";		noteDurations_[2].factor = 0.0625;
	noteDurations_[3].label = "1/8";		noteDurations_[3].factor = 0.125;
	noteDurations_[4].label = "1/4";		noteDurations_[4].factor = 0.25;
	noteDurations_[5].label = "1/2";		noteDurations_[5].factor = 0.5;
	noteDurations_[6].label = "1 Bar";		noteDurations_[6].factor = 1.0;

	noteDurations_[7].label = "1/64 T";		noteDurations_[7].factor = 1.0 / 96.0;
	noteDurations_[8].label = "1/32 T";		noteDurations_[8].factor = 1.0 / 48.0;
	noteDurations_[9].label = "1/16 T";		noteDurations_[9].factor = 1.0 / 24.0;
	noteDurations_[10].label = "1/8 T";		noteDurations_[10].factor = 1.0 / 12.0;
	noteDurations_[11].label = "1/4 T";		noteDurations_[11].factor = 1.0 / 6.0;
	noteDurations_[12].label = "1/2 T";		noteDurations_[12].factor = 1.0 / 3.0;
	noteDurations_[13].label = "1 Bar T";	noteDurations_[13].factor = 2.0 / 3.0;

	noteDurations_[14].label = "1/64 D";	noteDurations_[14].factor = 0.0234375;
	noteDurations_[15].label = "1/32 D";	noteDurations_[15].factor = 0.046875;
	noteDurations_[16].label = "1/16 D";	noteDurations_[16].factor = 0.09375;
	noteDurations_[17].label = "1/8 D";		noteDurations_[17].factor = 0.1875;
	noteDurations_[18].label = "1/4 D";		noteDurations_[18].factor = 0.375;
	noteDurations_[19].label = "1/2 D";		noteDurations_[19].factor = 0.75;

	PopupMenu straightSubMenu;
	for (int i = 1; i < 8; i++) {
		straightSubMenu.addItem(i, noteDurations_[i-1].label);
	}
	durationMenu_.addSubMenu("Straight", straightSubMenu);

	PopupMenu tripletSubMenu;
	for (int i = 8; i < 15; i++) {
		tripletSubMenu.addItem(i, noteDurations_[i - 1].label);
	}
	durationMenu_.addSubMenu("Triplet", tripletSubMenu);

	PopupMenu dottedSubMenu;
	for (int i = 15; i < 21; i++) {
		dottedSubMenu.addItem(i, noteDurations_[i - 1].label);
	}
	durationMenu_.addSubMenu("Dotted", dottedSubMenu);	
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

	durationButton_.setBounds(40, 290, 300, 20);
}

void NegativeDelayAudioProcessorEditor::noteDurationToMS(double factor)
{
	double barInMS = 240000.0 / processor.lastPosInfo.bpm;
	double ms = factor * barInMS;
	millisecondsSlider_.setValue(ms);
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
