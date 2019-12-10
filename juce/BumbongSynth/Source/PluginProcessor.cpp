/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BumbongSynthAudioProcessor::BumbongSynthAudioProcessor()
	#ifndef JucePlugin_PreferredChannelConfigurations
		 : AudioProcessor (BusesProperties()
						 #if ! JucePlugin_IsMidiEffect
						  #if ! JucePlugin_IsSynth
						   .withInput  ("Input",  AudioChannelSet::stereo(), true)
						  #endif
						   .withOutput ("Output", AudioChannelSet::stereo(), true)
						 #endif
						   ),
	parameters(*this, nullptr, Identifier("BUMBONG"),
		{
			std::make_unique<AudioParameterFloat>("blowCutoff", "Blow Cutoff", 20.0f, 20000.0f, 3000.0f),
			std::make_unique<AudioParameterFloat>("blowPressure", "Blow Pressure", 0.0f, 1.0f, 0.18f),
			std::make_unique<AudioParameterFloat>("blowAttack", "Blow Attack", 0.0f, 3.0f, 0.1f),
			std::make_unique<AudioParameterFloat>("blowRelease", "Blow Release", 0.0f, 3.0f, 0.7f),
			std::make_unique<AudioParameterFloat>("blowVibratoGain", "Vibrato Gain", 0.0f, 1.0f, 0.0f),
			std::make_unique<AudioParameterFloat>("blowVibratoFreq", "Vibrato Frequency", 0.1f, 10.0f, 0.0f),
			std::make_unique<AudioParameterFloat>("closedToOpenEndRatio", "Mouthpiece Position", 0.0f, 1.0f, 1.0f),
			std::make_unique<AudioParameterFloat>("closedEndDispersionRatio", "Closed End Dispersion", 0.0f, 1.0f, 0.28f),
			std::make_unique<AudioParameterFloat>("closedEndReflectionRatio", "Closed End Reflection", 0.0f, 1.0f, 0.96f),
			std::make_unique<AudioParameterFloat>("openEndDispersionRatio", "Open End Dispersion", 0.0f, 1.0f, 0.2f),
			std::make_unique<AudioParameterFloat>("openEndReflectionRatio", "Open End Reflection", 0.0f, 1.0f, 1.0f),
			std::make_unique<AudioParameterFloat>("wetMixLevel", "Wet / Dry Mix Level", 0.0f, 1.0f, 1.0f),
			std::make_unique<AudioParameterFloat>("reverbLevel", "Reverb Level", 0.0f, 1.0f, 0.5f)
		}
	)
#else
	: parameters(*this, nullptr, Identifier("BUMBONG"),
		{
			std::make_unique<AudioParameterFloat>("blowCutoff", "Blow Cutoff", 20.0f, 20000.0f, 3000.0f),
			std::make_unique<AudioParameterFloat>("blowPressure", "Blow Pressure", 0.0f, 1.0f, 0.18f),
			std::make_unique<AudioParameterFloat>("blowAttack", "Blow Attack", 0.0f, 3.0f, 0.1f),
			std::make_unique<AudioParameterFloat>("blowRelease", "Blow Release", 0.0f, 3.0f, 0.7f),
			std::make_unique<AudioParameterFloat>("blowVibratoGain", "Vibrato Gain", 0.0f, 1.0f, 0.0f),
			std::make_unique<AudioParameterFloat>("blowVibratoFreq", "Vibrato Frequency", 0.1f, 10.0f, 0.0f),
			std::make_unique<AudioParameterFloat>("closedToOpenEndRatio", "Mouthpiece Position", 0.0f, 1.0f, 1.0f),
			std::make_unique<AudioParameterFloat>("closedEndDispersionRatio", "Closed End Dispersion", 0.0f, 1.0f, 0.28f),
			std::make_unique<AudioParameterFloat>("closedEndReflectionRatio", "Closed End Reflection", 0.0f, 1.0f, 0.96f),
			std::make_unique<AudioParameterFloat>("openEndDispersionRatio", "Open End Dispersion", 0.0f, 1.0f, 0.2f),
			std::make_unique<AudioParameterFloat>("openEndReflectionRatio", "Open End Reflection", 0.0f, 1.0f, 1.0f),
			std::make_unique<AudioParameterFloat>("wetMixLevel", "Wet / Dry Mix Level", 0.0f, 1.0f, 1.0f),
			std::make_unique<AudioParameterFloat>("reverbLevel", "Reverb Level", 0.0f, 1.0f, 0.5f)
		}
	)
	#endif
{
	dspFaust.start();
}

BumbongSynthAudioProcessor::~BumbongSynthAudioProcessor()
{
	dspFaust.stop();
}

//==============================================================================
const String BumbongSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BumbongSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BumbongSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BumbongSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BumbongSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BumbongSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BumbongSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BumbongSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String BumbongSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void BumbongSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BumbongSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void BumbongSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BumbongSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BumbongSynthAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	// This is here to avoid people getting screaming feedback
	// when they first compile a plugin, but obviously you don't need to keep
	// this code if your algorithm always overwrites all the output channels.
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	// This is the place where you'd normally do the guts of your plugin's
	// audio processing...
	// Make sure to reset the state if your inner loop is processing
	// the samples and the outer loop is handling the channels.
	// Alternatively, you can process the samples with the channels
	// interleaved by keeping the same state.
	//for (int channel = 0; channel < totalNumInputChannels; ++channel)
	//{
	//	auto* channelData = buffer.getWritePointer(channel);

	//	// ..do something to the data...
	//}
	
	midiMessages.swapWith(midiBuffer);

	MidiBuffer::Iterator iterator(midiBuffer);
	MidiMessage message;
	int sampleNumber;

	while (iterator.getNextEvent(message,sampleNumber))
	{
		if (auto* bytes = message.getRawData())
		{
			int count = jmax(1, message.getRawDataSize());
			count = jmin(count, 3);

			int type = bytes[0];
			int data1 = count < 2 ? NULL : bytes[1];
			int data2 = count < 3 ? NULL : bytes[2];

			auto time = message.getTimeStamp();
			auto channel = message.getChannel();

			dspFaust.propagateMidi(count, time, type, channel, data1, data2);
		}
	}
}

//==============================================================================
bool BumbongSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BumbongSynthAudioProcessor::createEditor()
{
	return new BumbongSynthAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void BumbongSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

	auto state = parameters.copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void BumbongSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(parameters.state.getType()))
			parameters.replaceState(ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BumbongSynthAudioProcessor();
}

void BumbongSynthAudioProcessor::keyOn(int pitch, int velocity)
{
	dspFaust.keyOn(pitch, velocity);
}

void BumbongSynthAudioProcessor::keyOff(int pitch)
{
	dspFaust.keyOff(pitch);
}

void BumbongSynthAudioProcessor::setBlowCutoff(float blowCutoff)
{
	dspFaust.setParamValue("/Sequencer/DSP1/Polyphonic/Voices/bumbong/blowCutoff", blowCutoff);
}

void BumbongSynthAudioProcessor::setBlowPressure(float blowPressure)
{
	dspFaust.setParamValue("/Sequencer/DSP1/Polyphonic/Voices/bumbong/blowPressure", blowPressure);
}

void BumbongSynthAudioProcessor::setBlowAttack(float blowAttack)
{
	dspFaust.setParamValue("/Sequencer/DSP1/Polyphonic/Voices/bumbong/attack", blowAttack);
}

void BumbongSynthAudioProcessor::setBlowRelease(float blowRelease)
{
	dspFaust.setParamValue("/Sequencer/DSP1/Polyphonic/Voices/bumbong/release", blowRelease);
}

void BumbongSynthAudioProcessor::setBlowVibratoFreq(float blowVibratoFreq)
{
	dspFaust.setParamValue("/Sequencer/DSP1/Polyphonic/Voices/bumbong/VibratoFreq", blowVibratoFreq);
}

void BumbongSynthAudioProcessor::setBlowVibratoGain(float blowVibratoGain)
{
	dspFaust.setParamValue("/Sequencer/DSP1/Polyphonic/Voices/bumbong/VibratoGain", blowVibratoGain);
}

void BumbongSynthAudioProcessor::setClosedToOpenEndRatio(float closedToOpenEndRatio)
{
	dspFaust.setParamValue("/Sequencer/DSP1/Polyphonic/Voices/bumbong/closedToOpenEndRatio", closedToOpenEndRatio);
}

void BumbongSynthAudioProcessor::setClosedEndDispersionRatio(float closedEndDispersionRatio)
{
	dspFaust.setParamValue("/Sequencer/DSP1/Polyphonic/Voices/bumbong/closedEndDispersionRatio", closedEndDispersionRatio);
}

void BumbongSynthAudioProcessor::setClosedEndReflectionRatio(float closedEndReflectionRatio)
{
	dspFaust.setParamValue("/Sequencer/DSP1/Polyphonic/Voices/bumbong/closedEndReflectionRatio", closedEndReflectionRatio);
}

void BumbongSynthAudioProcessor::setOpenEndDispersionRatio(float openEndDispersionRatio)
{
	dspFaust.setParamValue("/Sequencer/DSP1/Polyphonic/Voices/bumbong/openEndDispersionRatio", openEndDispersionRatio);
}

void BumbongSynthAudioProcessor::setOpenEndReflectionRatio(float openEndReflectionRatio)
{
	dspFaust.setParamValue("/Sequencer/DSP1/Polyphonic/Voices/bumbong/openEndReflectionRatio", openEndReflectionRatio);
}

void BumbongSynthAudioProcessor::setReverbLevel(float reverbLevel)
{
	dspFaust.setParamValue("/Sequencer/DSP2/Zita_Light/Level", reverbLevel);
}

void BumbongSynthAudioProcessor::setWetMixLevel(float wetMixLevel)
{
	dspFaust.setParamValue("/Sequencer/DSP2/Zita_Light/Dry/Wet_Mix", wetMixLevel);
}