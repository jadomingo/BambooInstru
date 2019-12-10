/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AngklungSynthAudioProcessorEditor::AngklungSynthAudioProcessorEditor (AngklungSynthAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), keyboardComponent(keyboardState, MidiKeyboardComponent::horizontalKeyboard), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(600, 400);

	//	UI Elements

	addAndMakeVisible(keyboardComponent);
	keyboardState.addListener(this);
	keyboardComponent.setOctaveForMiddleC(4);
	//keyboardComponent.setAvailableRange(0, 127);

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

	addAndMakeVisible(shakeFrequencySlider);
	shakeFrequencyAttachment.reset(new SliderAttachment(valueTreeState, "shakeFrequency", shakeFrequencySlider));
	shakeFrequencySlider.setSliderStyle(Slider::Rotary);
	shakeFrequencySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
	shakeFrequencySlider.onValueChange = [this] {
		processor.setShakeFrequency(shakeFrequencySlider.getValue());
	};

	addAndMakeVisible(shakeFrequencyLabel);
	shakeFrequencyLabel.setJustificationType(Justification::centred);
	shakeFrequencyLabel.attachToComponent(&shakeFrequencySlider, false);
	shakeFrequencyLabel.setText("Shake Frequency", dontSendNotification);

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

	//	here to add a frame
	controlsGroup.setText("Angklung Controls");
	controlsGroup.setTextLabelPosition(Justification::centredLeft);
	addAndMakeVisible(controlsGroup);
	
	reverbGroup.setText("Reverb Controls");
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

AngklungSynthAudioProcessorEditor::~AngklungSynthAudioProcessorEditor()
{
	keyboardState.removeListener(this);
}

//==============================================================================

void AngklungSynthAudioProcessorEditor::setMidiInput(int index)
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

void AngklungSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void AngklungSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	auto area = getLocalBounds();
	
	midiInputList.setBounds(area.removeFromTop(40).removeFromRight(400).reduced(10));
	keyboardComponent.setBounds(area.removeFromBottom(120).reduced(10));

	auto middleArea = area.removeFromTop(240);

	controlsGroup.setBounds(middleArea.removeFromLeft(200).reduced(10));
	auto controlGroupArea = controlsGroup.getBounds();
	reverbGroup.setBounds(middleArea.removeFromRight(400).reduced(10));
	auto reverbGroupArea = reverbGroup.getBounds();

	shakeFrequencySlider.setBounds(controlGroupArea.removeFromBottom(controlGroupArea.getHeight() - 30).reduced(20));

	auto reverbGroupWidth = reverbGroupArea.getWidth();
	auto reverbGroupHeight = reverbGroupArea.getHeight();
	wetMixLevelSlider.setBounds(reverbGroupArea.removeFromLeft(reverbGroupWidth / 2).removeFromBottom(reverbGroupHeight - 30).reduced(20));
	reverbLevelSlider.setBounds(reverbGroupArea.removeFromRight(reverbGroupWidth / 2).removeFromBottom(reverbGroupHeight - 30).reduced(20));
}

void AngklungSynthAudioProcessorEditor::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message)
{
}

void AngklungSynthAudioProcessorEditor::handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
	processor.keyOn(midiNoteNumber, int(127 * velocity));
}

void AngklungSynthAudioProcessorEditor::handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
	processor.keyOff(midiNoteNumber);
}