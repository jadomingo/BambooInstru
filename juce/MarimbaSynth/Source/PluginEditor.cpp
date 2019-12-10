/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MarimbaSynthAudioProcessorEditor::MarimbaSynthAudioProcessorEditor (MarimbaSynthAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), keyboardComponent(keyboardState, MidiKeyboardComponent::horizontalKeyboard), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(400, 400);

	keyboardComponent.setOctaveForMiddleC(4);
	addAndMakeVisible(keyboardComponent);
	keyboardState.addListener(this);

	addAndMakeVisible(reverbLevelSlider);
	reverbLevelAttachment.reset(new SliderAttachment(valueTreeState, "reverbLevel", reverbLevelSlider));
	reverbLevelSlider.setSliderStyle(Slider::Rotary);
	reverbLevelSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 60, 20);
	reverbLevelSlider.onValueChange = [this] {
		processor.setReverbLevel(Decibels::gainToDecibels(reverbLevelSlider.getValue()));
	};
	
	addAndMakeVisible(reverbLevelLabel);
	reverbLevelLabel.setText("Reverb Level", dontSendNotification);
	reverbLevelLabel.attachToComponent(&reverbLevelSlider, false);

	addAndMakeVisible(wetMixLevelSlider);
	wetMixLevelAttachment.reset(new SliderAttachment(valueTreeState, "wetMixLevel", wetMixLevelSlider));
	wetMixLevelSlider.setSliderStyle(Slider::Rotary);
	wetMixLevelSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 60, 20);
	wetMixLevelSlider.onValueChange = [this] {
		processor.setWetMixLevel(wetMixLevelSlider.getValue());
	};
	
	addAndMakeVisible(wetMixLevelLabel);
	wetMixLevelLabel.setText("Wet/Dry Mix Level", dontSendNotification);
	wetMixLevelLabel.attachToComponent(&wetMixLevelSlider, false);

	//	Select Midi Input

	addAndMakeVisible(midiInputListLabel);
	midiInputListLabel.setText("MIDI Input:", dontSendNotification);
	midiInputListLabel.attachToComponent(&midiInputList, true);

	addAndMakeVisible(midiInputList);
	midiInputList.setTextWhenNoChoicesAvailable("No MIDI Inputs Enabled");
	auto midiInputs = MidiInput::getAvailableDevices();

	//	add frames

	reverbGroup.setText("Marimba Controls");
	reverbGroup.setTextLabelPosition(Justification::centredLeft);
	addAndMakeVisible(reverbGroup);

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

MarimbaSynthAudioProcessorEditor::~MarimbaSynthAudioProcessorEditor()
{
	keyboardState.removeListener(this);
}

//==============================================================================

void MarimbaSynthAudioProcessorEditor::setMidiInput(int index)
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

void MarimbaSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MarimbaSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	auto area = getLocalBounds();


	midiInputList.setBounds(area.removeFromTop(40).removeFromRight(400).reduced(10));
	keyboardComponent.setBounds(area.removeFromBottom(120).reduced(10));

	auto middleArea = area.removeFromTop(240);

	reverbGroup.setBounds(middleArea.reduced(10));

	auto reverbGroupWidth = middleArea.getWidth();
	auto reverbGroupHeight = middleArea.getHeight();
	wetMixLevelSlider.setBounds(middleArea.removeFromLeft(reverbGroupWidth / 2).removeFromBottom(reverbGroupHeight - 30).reduced(30));
	reverbLevelSlider.setBounds(middleArea.removeFromRight(reverbGroupWidth / 2).removeFromBottom(reverbGroupHeight - 30).reduced(30));

}

void MarimbaSynthAudioProcessorEditor::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message)
{
}

void MarimbaSynthAudioProcessorEditor::handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
	processor.keyOn(midiNoteNumber, int(127 * velocity));
}

void MarimbaSynthAudioProcessorEditor::handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/)
{
	processor.keyOff(midiNoteNumber);
}