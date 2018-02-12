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
	WavAudioFormat	wavFormat;
	std::vector<std::string> files;
	std::vector<std::string>::iterator it;
	std::cout << "Directory = " << FileManager::getCurrentDirectory() + "/../../../../Samples/" << std::endl;
	FileManager::getFilesList(FileManager::getCurrentDirectory() +  "/../../../../Samples/", ".wav", files);
	BigInteger allNotes;
	allNotes.setRange(0, 128, true);
	_audioFormatManager.registerBasicFormats();
	_synth.clearSounds();

	it = files.begin();
	while (it != files.end())
	{
		std::cout << "File = " << *it << std::endl;
		std::cout << "FileName = " << FileManager::getFileName(*it) << std::endl;
		File* file = new File(*it);
		ScopedPointer<AudioFormatReader> reader = _audioFormatManager.createReaderFor(*file);
		try
		{
			SynthesizerInstrument::Ptr instrument(new SynthesizerInstrument(FileManager::getFileName(*it), *reader, allNotes, 60, 0, 1, 1.0, instrumentList.at(FileManager::getFileName(*it))));
			_synth.addSound(instrument);
		}
		catch (const std::exception & e)
		{
			std::cerr << "WARNING : Can not find instrument from the samples : " << FileManager::getFileName(*it) << std::endl;
		}
		++it;
	}
}

void Synthesizer::loadSamples()
{

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
