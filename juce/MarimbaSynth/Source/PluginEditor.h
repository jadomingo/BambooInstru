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
class MarimbaSynthAudioProcessorEditor  : 
	public AudioProcessorEditor,
	private MidiInputCallback,
	private MidiKeyboardStateListener
{
	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
public:
    MarimbaSynthAudioProcessorEditor (MarimbaSynthAudioProcessor&, AudioProcessorValueTreeState&);
    ~MarimbaSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MarimbaSynthAudioProcessor& processor; 

	void setMidiInput(int index);
	void handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
	void handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) override;
	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;

	MidiKeyboardState keyboardState;
	MidiKeyboardComponent keyboardComponent;

	Slider reverbLevelSlider;
	Slider wetMixLevelSlider;
	Label wetMixLevelLabel;
	Label reverbLevelLabel;

	std::unique_ptr<SliderAttachment> reverbLevelAttachment;
	std::unique_ptr<SliderAttachment> wetMixLevelAttachment;

	GroupComponent reverbGroup;

	Label midiInputListLabel;
	ComboBox midiInputList;

	AudioDeviceManager deviceManager;

	int lastInputIndex = 0;
	bool isAddingFromMidiInput = false;

	AudioProcessorValueTreeState& valueTreeState;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MarimbaSynthAudioProcessorEditor)
};
