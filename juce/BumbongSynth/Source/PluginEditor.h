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
class BumbongSynthAudioProcessorEditor  : 
	public AudioProcessorEditor,
	private MidiInputCallback,
	private MidiKeyboardStateListener
{
	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
public:
    BumbongSynthAudioProcessorEditor (BumbongSynthAudioProcessor&, AudioProcessorValueTreeState&);
    ~BumbongSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BumbongSynthAudioProcessor& processor;
	AudioProcessorValueTreeState& valueTreeState;
	AudioDeviceManager deviceManager;

	void setMidiInput(int index);
	void handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
	void handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) override;
	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;

	MidiKeyboardState keyboardState;
	MidiKeyboardComponent keyboardComponent;

	GroupComponent tubeGroup;
	GroupComponent blowerGroup;
	GroupComponent reverbGroup;

	Slider blowCutoffSlider;
	Slider blowPressureSlider;
	Slider blowAttackSlider;
	Slider blowReleaseSlider;
	Slider blowVibratoFreqSlider;
	Slider blowVibratoGainSlider;

	Slider closedToOpenEndRatioSlider;
	Slider closedEndDispersionRatioSlider;
	Slider closedEndReflectionRatioSlider;
	Slider openEndDispersionRatioSlider;
	Slider openEndReflectionRatioSlider;

	Slider reverbLevelSlider;
	Slider wetMixLevelSlider;

	std::unique_ptr<SliderAttachment> blowCutoffAttachment;
	std::unique_ptr<SliderAttachment> blowPressureAttachment;
	std::unique_ptr<SliderAttachment> blowAttackAttachment;
	std::unique_ptr<SliderAttachment> blowReleaseAttachment;
	std::unique_ptr<SliderAttachment> blowVibratoFreqAttachment;
	std::unique_ptr<SliderAttachment> blowVibratoGainAttachment;

	std::unique_ptr<SliderAttachment> closedToOpenEndRatioAttachment;
	std::unique_ptr<SliderAttachment> closedEndDispersionRatioAttachment;
	std::unique_ptr<SliderAttachment> closedEndReflectionRatioAttachment;
	std::unique_ptr<SliderAttachment> openEndDispersionRatioAttachment;
	std::unique_ptr<SliderAttachment> openEndReflectionRatioAttachment;

	std::unique_ptr<SliderAttachment> reverbLevelAttachment;
	std::unique_ptr<SliderAttachment> wetMixLevelAttachment;

	Label blowCutoffLabel;
	Label blowPressureLabel;
	Label blowAttackLabel;
	Label blowReleaseLabel;
	Label blowVibratoFreqLabel;
	Label blowVibratoGainLabel;
	Label closedToOpenEndRatioLabel;
	Label closedEndDispersionRatioLabel;
	Label closedEndReflectionRatioLabel;
	Label openEndDispersionRatioLabel;
	Label openEndReflectionRatioLabel;

	Label reverbLevelLabel;
	Label wetMixLevelLabel;

	Label midiInputListLabel;
	ComboBox midiInputList;

	int lastInputIndex = 0;
	bool isAddingFromMidiInput = false;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BumbongSynthAudioProcessorEditor)
};
