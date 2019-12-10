/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BumbongSynthAudioProcessorEditor::BumbongSynthAudioProcessorEditor (BumbongSynthAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), keyboardComponent(keyboardState, MidiKeyboardComponent::horizontalKeyboard), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(1100, 600);

	//	UI Elements

	addAndMakeVisible(keyboardComponent);
	keyboardState.addListener(this);
	keyboardComponent.setOctaveForMiddleC(4);
	//keyboardComponent.setAvailableRange(0, 127);

	addAndMakeVisible(blowCutoffSlider);
	blowCutoffAttachment.reset(new SliderAttachment(valueTreeState, "blowCutoff", blowCutoffSlider));
	blowCutoffSlider.setSliderStyle(Slider::Rotary);
	blowCutoffSlider.setTextBoxStyle(Slider::TextBoxBelow,true,80,20);
	blowCutoffSlider.onValueChange = [this] {
		processor.setBlowCutoff(blowCutoffSlider.getValue());
	};

	addAndMakeVisible(blowCutoffLabel);
	blowCutoffLabel.setJustificationType(Justification::centred);
	blowCutoffLabel.attachToComponent(&blowCutoffSlider,false);
	blowCutoffLabel.setText("Blow Cutoff",dontSendNotification);

	addAndMakeVisible(blowPressureSlider);
	blowPressureAttachment.reset(new SliderAttachment(valueTreeState, "blowPressure", blowPressureSlider));
	blowPressureSlider.setSliderStyle(Slider::LinearVertical);
	blowPressureSlider.setTextBoxStyle(Slider::TextBoxBelow,true,50,20);
	blowPressureSlider.onValueChange = [this] {
		processor.setBlowPressure(blowPressureSlider.getValue());
	};

	addAndMakeVisible(blowPressureLabel);
	blowPressureLabel.setJustificationType(Justification::centred);
	blowPressureLabel.attachToComponent(&blowPressureSlider, false);
	blowPressureLabel.setText("Blow Pressure", dontSendNotification);
	
	addAndMakeVisible(blowAttackSlider);
	blowAttackAttachment.reset(new SliderAttachment(valueTreeState, "blowAttack", blowAttackSlider));
	blowAttackSlider.setSliderStyle(Slider::LinearVertical);
	blowAttackSlider.setTextBoxStyle(Slider::TextBoxBelow,true,50,20);
	blowAttackSlider.onValueChange = [this] {
		processor.setBlowAttack(blowAttackSlider.getValue());
	};

	addAndMakeVisible(blowAttackLabel);
	blowAttackLabel.setJustificationType(Justification::centred);
	blowAttackLabel.attachToComponent(&blowAttackSlider, false);
	blowAttackLabel.setText("Blow Attack", dontSendNotification);

	addAndMakeVisible(blowReleaseSlider);
	blowReleaseAttachment.reset(new SliderAttachment(valueTreeState, "blowRelease", blowReleaseSlider));
	blowReleaseSlider.setSliderStyle(Slider::LinearVertical);
	blowReleaseSlider.setTextBoxStyle(Slider::TextBoxBelow,true,50,20);
	blowReleaseSlider.onValueChange = [this] {
		processor.setBlowRelease(blowReleaseSlider.getValue());
	};

	addAndMakeVisible(blowReleaseLabel);
	blowReleaseLabel.setJustificationType(Justification::centred);
	blowReleaseLabel.attachToComponent(&blowReleaseSlider, false);
	blowReleaseLabel.setText("Blow Release", dontSendNotification);

	addAndMakeVisible(blowVibratoFreqSlider);
	blowVibratoFreqAttachment.reset(new SliderAttachment(valueTreeState, "blowVibratoFreq", blowVibratoFreqSlider));
	blowVibratoFreqSlider.setSliderStyle(Slider::Rotary);
	blowVibratoFreqSlider.setTextBoxStyle(Slider::TextBoxBelow,true,80,20);
	blowVibratoFreqSlider.onValueChange = [this] {
		processor.setBlowVibratoFreq(blowVibratoFreqSlider.getValue());
	};

	addAndMakeVisible(blowVibratoFreqLabel);
	blowVibratoFreqLabel.setJustificationType(Justification::centred);
	blowVibratoFreqLabel.attachToComponent(&blowVibratoFreqSlider, false);
	blowVibratoFreqLabel.setText("Vibrato Frequency", dontSendNotification);

	addAndMakeVisible(blowVibratoGainSlider);
	blowVibratoGainAttachment.reset(new SliderAttachment(valueTreeState, "blowVibratoGain", blowVibratoGainSlider));
	blowVibratoGainSlider.setSliderStyle(Slider::LinearVertical);
	blowVibratoGainSlider.setTextBoxStyle(Slider::TextBoxBelow,true,50,20);
	blowVibratoGainSlider.onValueChange = [this] {
		processor.setBlowVibratoGain(blowVibratoGainSlider.getValue());
	};

	addAndMakeVisible(blowVibratoGainLabel);
	blowVibratoGainLabel.setJustificationType(Justification::centred);
	blowVibratoGainLabel.attachToComponent(&blowVibratoGainSlider, false);
	blowVibratoGainLabel.setText("Vibrato Gain", dontSendNotification);

	addAndMakeVisible(closedToOpenEndRatioSlider);
	closedToOpenEndRatioAttachment.reset(new SliderAttachment(valueTreeState, "closedToOpenEndRatio", closedToOpenEndRatioSlider));
	closedToOpenEndRatioSlider.setSliderStyle(Slider::LinearVertical);
	closedToOpenEndRatioSlider.setTextBoxStyle(Slider::TextBoxBelow,true,50,20);
	closedToOpenEndRatioSlider.onValueChange = [this] {
		processor.setClosedToOpenEndRatio(closedToOpenEndRatioSlider.getValue());
	};

	addAndMakeVisible(closedToOpenEndRatioLabel);
	closedToOpenEndRatioLabel.setJustificationType(Justification::centred);
	closedToOpenEndRatioLabel.attachToComponent(&closedToOpenEndRatioSlider, false);
	closedToOpenEndRatioLabel.setText("Mouthpiece Position", dontSendNotification);

	addAndMakeVisible(closedEndDispersionRatioSlider);
	closedEndDispersionRatioAttachment.reset(new SliderAttachment(valueTreeState, "closedEndDispersionRatio", closedEndDispersionRatioSlider));
	closedEndDispersionRatioSlider.setSliderStyle(Slider::LinearVertical);
	closedEndDispersionRatioSlider.setTextBoxStyle(Slider::TextBoxBelow,true,50,20);
	closedEndDispersionRatioSlider.onValueChange = [this] {
		processor.setClosedEndDispersionRatio(closedEndDispersionRatioSlider.getValue());
	};

	addAndMakeVisible(closedEndDispersionRatioLabel);
	closedEndDispersionRatioLabel.setJustificationType(Justification::centred);
	closedEndDispersionRatioLabel.attachToComponent(&closedEndDispersionRatioSlider, false);
	closedEndDispersionRatioLabel.setText("Closed End Dispersion", dontSendNotification);

	addAndMakeVisible(closedEndReflectionRatioSlider);
	closedEndReflectionRatioAttachment.reset(new SliderAttachment(valueTreeState, "closedEndReflectionRatio", closedEndReflectionRatioSlider));
	closedEndReflectionRatioSlider.setSliderStyle(Slider::LinearVertical);
	closedEndReflectionRatioSlider.setTextBoxStyle(Slider::TextBoxBelow,true,50,20);
	closedEndReflectionRatioSlider.onValueChange = [this] {
		processor.setClosedEndReflectionRatio(closedEndReflectionRatioSlider.getValue());
	};

	addAndMakeVisible(closedEndReflectionRatioLabel);
	closedEndReflectionRatioLabel.setJustificationType(Justification::centred);
	closedEndReflectionRatioLabel.attachToComponent(&closedEndReflectionRatioSlider, false);
	closedEndReflectionRatioLabel.setText("Closed End Reflection", dontSendNotification);

	addAndMakeVisible(openEndDispersionRatioSlider);
	openEndDispersionRatioAttachment.reset(new SliderAttachment(valueTreeState, "openEndDispersionRatio", openEndDispersionRatioSlider));
	openEndDispersionRatioSlider.setSliderStyle(Slider::LinearVertical);
	openEndDispersionRatioSlider.setTextBoxStyle(Slider::TextBoxBelow,true,50,20);
	openEndDispersionRatioSlider.onValueChange = [this] {
		processor.setOpenEndDispersionRatio(openEndDispersionRatioSlider.getValue());
	};

	addAndMakeVisible(openEndDispersionRatioLabel);
	openEndDispersionRatioLabel.setJustificationType(Justification::centred);
	openEndDispersionRatioLabel.attachToComponent(&openEndDispersionRatioSlider, false);
	openEndDispersionRatioLabel.setText("Open End Dispersion", dontSendNotification);

	addAndMakeVisible(openEndReflectionRatioSlider);
	openEndReflectionRatioAttachment.reset(new SliderAttachment(valueTreeState, "openEndReflectionRatio", openEndReflectionRatioSlider));
	openEndReflectionRatioSlider.setSliderStyle(Slider::LinearVertical);
	openEndReflectionRatioSlider.setTextBoxStyle(Slider::TextBoxBelow,true,50,20);
	openEndReflectionRatioSlider.onValueChange = [this] {
		processor.setOpenEndReflectionRatio(openEndReflectionRatioSlider.getValue());
	};

	addAndMakeVisible(openEndReflectionRatioLabel);
	openEndReflectionRatioLabel.setJustificationType(Justification::centred);
	openEndReflectionRatioLabel.attachToComponent(&openEndReflectionRatioSlider, false);
	openEndReflectionRatioLabel.setText("Open End Reflection", dontSendNotification);

	addAndMakeVisible(reverbLevelSlider);
	reverbLevelAttachment.reset(new SliderAttachment(valueTreeState, "reverbLevel", reverbLevelSlider));
	reverbLevelSlider.setSliderStyle(Slider::Rotary);
	reverbLevelSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
	reverbLevelSlider.onValueChange = [this] {
		processor.setReverbLevel(reverbLevelSlider.getValue());
	};

	addAndMakeVisible(reverbLevelLabel);
	reverbLevelLabel.setJustificationType(Justification::centred);
	reverbLevelLabel.attachToComponent(&reverbLevelSlider, false);
	reverbLevelLabel.setText("Reverb Level", dontSendNotification);

	addAndMakeVisible(wetMixLevelSlider);
	wetMixLevelAttachment.reset(new SliderAttachment(valueTreeState, "wetMixLevel", wetMixLevelSlider));
	wetMixLevelSlider.setSliderStyle(Slider::Rotary);
	wetMixLevelSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
	wetMixLevelSlider.onValueChange = [this] {
		processor.setWetMixLevel(wetMixLevelSlider.getValue());
	};

	addAndMakeVisible(wetMixLevelLabel);
	wetMixLevelLabel.setJustificationType(Justification::centred);
	wetMixLevelLabel.attachToComponent(&wetMixLevelSlider, false);
	wetMixLevelLabel.setText("Wet Mix Level", dontSendNotification);

	//	here to add a frame
	tubeGroup.setText("Tube Parameters");
	tubeGroup.setTextLabelPosition(Justification::centredLeft);
	addAndMakeVisible(tubeGroup);

	blowerGroup.setText("Blower Parameters");
	blowerGroup.setTextLabelPosition(Justification::centredLeft);
	addAndMakeVisible(blowerGroup);

	reverbGroup.setText("Reverb Parameters");
	reverbGroup.setTextLabelPosition(Justification::centredLeft);
	addAndMakeVisible(reverbGroup);

	//	Select Midi Input

	addAndMakeVisible(midiInputListLabel);
	midiInputListLabel.setText("MIDI Input:", dontSendNotification);
	midiInputListLabel.attachToComponent(&midiInputList, true);

	addAndMakeVisible(midiInputList);
	midiInputList.setTextWhenNoChoicesAvailable("No MIDI Inputs Enabled");
	auto midiInputs = MidiInput::getAvailableDevices();

	StringArray midiInputNames;
	for (auto input : midiInputs)
		midiInputNames.add(input.name);

	midiInputList.addItemList(midiInputNames, 1);
	midiInputList.onChange = [this] { setMidiInput(midiInputList.getSelectedItemIndex()); };

	// find the first enabled device and use that by default
	for (auto input : midiInputs)
	{
		if (deviceManager.isMidiInputDeviceEnabled(input.identifier))
		{
			setMidiInput(midiInputs.indexOf(input));
			break;
		}
	}

	// if no enabled devices were found just use the first one in the list
	if (midiInputList.getSelectedId() == 0)
		setMidiInput(0);
}

BumbongSynthAudioProcessorEditor::~BumbongSynthAudioProcessorEditor()
{
	keyboardState.removeListener(this);
}

//==============================================================================

void BumbongSynthAudioProcessorEditor::setMidiInput(int index)
{
	auto list = MidiInput::getAvailableDevices();

	deviceManager.removeMidiInputDeviceCallback(list[lastInputIndex].identifier, this);

	auto newInput = list[index];

	if (!deviceManager.isMidiInputDeviceEnabled(newInput.identifier))
		deviceManager.setMidiInputDeviceEnabled(newInput.identifier, true);

	deviceManager.addMidiInputDeviceCallback(newInput.identifier, this);
	midiInputList.setSelectedId(index + 1, dontSendNotification);

	lastInputIndex = index;
}

void BumbongSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void BumbongSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	auto area = getLocalBounds();
	
	midiInputList.setBounds(area.removeFromTop(40).removeFromRight(700).reduced(10));
	keyboardComponent.setBounds(area.removeFromBottom(120).reduced(10));

	auto reverbGroupArea = area.removeFromRight(200).reduced(10);
	auto tubeGroupArea = area.removeFromTop(220).reduced(10);
	auto blowerGroupArea = area.removeFromBottom(220).reduced(10);

	auto margin = 20;
	tubeGroup.setBounds(tubeGroupArea);
	auto tubeGroupWidth = tubeGroupArea.getWidth();
	auto tubeGroupHeight = tubeGroupArea.getHeight();

	closedToOpenEndRatioSlider.setBounds(tubeGroupArea.removeFromLeft(tubeGroupWidth / 5).removeFromBottom(tubeGroupHeight - 20).reduced(margin));
	closedEndDispersionRatioSlider.setBounds(tubeGroupArea.removeFromLeft(tubeGroupWidth / 5).removeFromBottom(tubeGroupHeight - 20).reduced(margin));
	closedEndReflectionRatioSlider.setBounds(tubeGroupArea.removeFromLeft(tubeGroupWidth / 5).removeFromBottom(tubeGroupHeight - 20).reduced(margin));
	openEndDispersionRatioSlider.setBounds(tubeGroupArea.removeFromLeft(tubeGroupWidth / 5).removeFromBottom(tubeGroupHeight - 20).reduced(margin));
	openEndReflectionRatioSlider.setBounds(tubeGroupArea.removeFromLeft(tubeGroupWidth / 5).removeFromBottom(tubeGroupHeight - 20).reduced(margin));

	blowerGroup.setBounds(blowerGroupArea);
	auto blowerGroupWidth = blowerGroupArea.getWidth();
	auto blowerGroupHeight = blowerGroupArea.getHeight();

	blowCutoffSlider.setBounds(blowerGroupArea.removeFromLeft(blowerGroupWidth/6).removeFromBottom(blowerGroupHeight - 20).reduced(margin));
	blowPressureSlider.setBounds(blowerGroupArea.removeFromLeft(blowerGroupWidth/6).removeFromBottom(blowerGroupHeight - 20).reduced(margin));
	blowAttackSlider.setBounds(blowerGroupArea.removeFromLeft(blowerGroupWidth/6).removeFromBottom(blowerGroupHeight - 20).reduced(margin));
	blowReleaseSlider.setBounds(blowerGroupArea.removeFromLeft(blowerGroupWidth/6).removeFromBottom(blowerGroupHeight - 20).reduced(margin));
	blowVibratoFreqSlider.setBounds(blowerGroupArea.removeFromLeft(blowerGroupWidth/6).removeFromBottom(blowerGroupHeight - 20).reduced(margin));
	blowVibratoGainSlider.setBounds(blowerGroupArea.removeFromLeft(blowerGroupWidth/6).removeFromBottom(blowerGroupHeight - 20).reduced(margin));

	reverbGroup.setBounds(reverbGroupArea);
	auto reverbGroupWidth = reverbGroupArea.getWidth();
	auto reverbGroupHeight = reverbGroupArea.getHeight();

	wetMixLevelSlider.setBounds(reverbGroupArea.reduced(margin).removeFromTop(reverbGroupHeight / 2.5).reduced(margin));
	reverbLevelSlider.setBounds(reverbGroupArea.reduced(margin).removeFromBottom(reverbGroupHeight / 2.5).reduced(margin));
}

void BumbongSynthAudioProcessorEditor::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message)
{
}

void BumbongSynthAudioProcessorEditor::handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
	processor.keyOn(midiNoteNumber, int(127 * velocity));
}

void BumbongSynthAudioProcessorEditor::handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
	processor.keyOff(midiNoteNumber);
}