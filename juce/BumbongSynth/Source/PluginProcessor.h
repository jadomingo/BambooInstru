/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DspFaust.h"

//==============================================================================
/**
*/
class BumbongSynthAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    BumbongSynthAudioProcessor();
    ~BumbongSynthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
	AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	void keyOn(int pitch, int  velocity);
	void keyOff(int pitch);
	
	//	Audio engine parameters
	//void setReverbLevel(float reverbLevel);
	//void setWetMixLevel(float wetMixLevel);
	
	void setBlowCutoff(float blowCutoff);
	void setBlowPressure(float blowPressure);
	void setBlowAttack(float blowAttack);
	void setBlowRelease(float blowRelease);
	void setBlowVibratoFreq(float blowVibratoFreq);
	void setBlowVibratoGain(float blowVibratoGain);

	void setClosedToOpenEndRatio(float closedToOpenEndRatio);
	void setClosedEndDispersionRatio(float closedEndDispersionRatio);
	void setClosedEndReflectionRatio(float closedEndReflectionRatio);
	void setOpenEndDispersionRatio(float openEndDispersionRatio);
	void setOpenEndReflectionRatio(float openEndReflectionRatio);

	void setWetMixLevel(float WetMixLevel);
	void setReverbLevel(float ReverbLevel);

private:
	DspFaust dspFaust;
	MidiBuffer midiBuffer;

	AudioProcessorValueTreeState parameters;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BumbongSynthAudioProcessor)
};
