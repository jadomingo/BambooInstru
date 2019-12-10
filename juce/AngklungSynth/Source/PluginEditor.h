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
class AngklungSynthAudioProcessorEditor  : 
	public AudioProcessorEditor,
	private MidiInputCallback,
	private MidiKeyboardStateListener
{
	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
public:
    AngklungSynthAudioProcessorEditor (AngklungSynthAudioProcessor&, AudioProcessorValueTreeState&);
    ~AngklungSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AngklungSynthAudioProcessor& processor;
	AudioProcessorValueTreeState& valueTreeState;
	AudioDeviceManager deviceManager;

	void setMidiInput(int index);
	void handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
	void handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) override;
	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;

	MidiKeyboardState keyboardState;
	MidiKeyboardComponent keyboardComponent;

	GroupComponent controlsGroup;
	GroupComponent reverbGroup;

	Slider shakeFrequencySlider;
	Slider reverbLevelSlider;
	Slider wetMixLevelSlider;

	std::unique_ptr<SliderAttachment> shakeFrequencyAttachment;
	std::unique_ptr<SliderAttachment> reverbLevelAttachment;
	std::unique_ptr<SliderAttachment> wetMixLevelAttachment;

	Label shakeFrequencyLabel;
	Label reverbLevelLabel;
	Label wetMixLevelLabel;

	Label midiInputListLabel;
	ComboBox midiInputList;

	int lastInputIndex = 0;
	bool isAddingFromMidiInput = false;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AngklungSynthAudioProcessorEditor)
};
