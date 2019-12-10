/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MarimbaSynthAudioProcessor::MarimbaSynthAudioProcessor()
	#ifndef JucePlugin_PreferredChannelConfigurations
		 : AudioProcessor (BusesProperties()
						 #if ! JucePlugin_IsMidiEffect
						  #if ! JucePlugin_IsSynth
						   .withInput  ("Input",  AudioChannelSet::stereo(), true)
						  #endif
						   .withOutput ("Output", AudioChannelSet::stereo(), true)
						 #endif
						   ),
	parameters(*this, nullptr, Identifier("MARIMBA"),
		{
			std::make_unique<AudioParameterFloat>("reverbLevel",            // parameterID
												   "Reverb level",            // parameter name
												   0.0f,              // minimum value
												   2.0f,              // maximum value
												   1.0f),             // default value
			std::make_unique<AudioParameterFloat>("wetMixLevel",            // parameterID
												   "Wet / Mix Level",            // parameter name
												   0.0f,              // minimum value
												   1.0f,              // maximum value
												   1.0f),             // default value
		}
	)
#else
	: parameters(*this, nullptr, Identifier("MARIMBA"),
		{
			std::make_unique<AudioParameterFloat>("reverbLevel",            // parameterID
												   "Reverb level",            // parameter name
												   0.0f,              // minimum value
												   1.0f,              // maximum value
												   0.5f),             // default value
			std::make_unique<AudioParameterFloat>("wetMixLevel",            // parameterID
												   "Wet / Mix Level",            // parameter name
												   0.0f,              // minimum value
												   1.0f,              // maximum value
												   0.5f),             // default value
		}
	)
	#endif
{
	dspFaust.start();
}

MarimbaSynthAudioProcessor::~MarimbaSynthAudioProcessor()
{
	dspFaust.stop();
}

//==============================================================================
const String MarimbaSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MarimbaSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MarimbaSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MarimbaSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MarimbaSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MarimbaSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MarimbaSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MarimbaSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String MarimbaSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void MarimbaSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MarimbaSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MarimbaSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MarimbaSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MarimbaSynthAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
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
bool MarimbaSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MarimbaSynthAudioProcessor::createEditor()
{
	return new MarimbaSynthAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void MarimbaSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

	auto state = parameters.copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void MarimbaSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new MarimbaSynthAudioProcessor();
}

void MarimbaSynthAudioProcessor::keyOn(int pitch, int velocity)
{
	dspFaust.keyOn(pitch, velocity);
}

void MarimbaSynthAudioProcessor::keyOff(int pitch)
{
	dspFaust.keyOff(pitch);
}

void MarimbaSynthAudioProcessor::setReverbLevel(float reverbLevel)
{
	dspFaust.setParamValue("/Sequencer/DSP2/Zita_Light/Level", reverbLevel);
}

void MarimbaSynthAudioProcessor::setWetMixLevel(float wetMixLevel)
{
	dspFaust.setParamValue("/Sequencer/DSP2/Zita_Light/Dry/Wet_Mix", wetMixLevel);
}