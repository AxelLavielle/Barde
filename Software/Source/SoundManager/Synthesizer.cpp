/*
  ==============================================================================

    Synthesizer.cpp
    Created: 20 Dec 2017 11:25:33am
    Author:  Anthony

  ==============================================================================
*/

#include "Synthesizer.hh"

Synthesizer::Synthesizer()
{
	for (int i = 4; --i >= 0;)
	{
		_synth.addVoice(new SamplerVoice());
	}
	setUsingSampledSound();
}

void Synthesizer::setUsingSampledSound()
{
	WavAudioFormat wavFormat;
	File* file = new File("./file.wav");
	BigInteger allNotes;

	_audioFormatManager.registerBasicFormats();
	ScopedPointer<AudioFormatReader> reader = _audioFormatManager.createReaderFor(*file);
	allNotes.setRange(0, 128, true);
	_synth.clearSounds();
	_synth.addSound(new SamplerSound("default", *reader, allNotes, 60, 0, 1, 1.0));
}

void Synthesizer::prepareToPlay(int /*samplesPerBlockExpected*/, double sampleRate)
{
	_midiCollector.reset(sampleRate);

	std::cout << sampleRate << std::endl;
	_synth.setCurrentPlaybackSampleRate(sampleRate);
}

void Synthesizer::releaseResources()
{
}

void Synthesizer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
	MidiBuffer incomingMidi;

	bufferToFill.clearActiveBufferRegion();
	_midiCollector.removeNextBlockOfMessages(incomingMidi, bufferToFill.numSamples);
	_synth.renderNextBlock(*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
}

void Synthesizer::addMessage(MidiMessage const & msg)
{
	_midiCollector.addMessageToQueue(msg);
}
