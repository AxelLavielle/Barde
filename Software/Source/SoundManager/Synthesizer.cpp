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

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void Synthesizer::setUsingSampledSound()
{
	WavAudioFormat	wavFormat;
	std::vector<std::wstring> files;
	std::vector<std::wstring>::iterator it;
	int channel;
	#ifdef __linux__
		std::wcout << "Directory = " << FileManager::getCurrentDirectory() + "/../../Samples/" << std::endl;
		FileManager::getFilesList(FileManager::getCurrentDirectory() +  "/../../Samples/", ".wav", files);
	#else
	std::wcout << "Directory = " << FileManager::getCurrentDirectory() + s2ws("/../../../../Samples/") << std::endl;
	FileManager::getFilesList(FileManager::getCurrentDirectory() + s2ws("/../../../../Samples/"), s2ws(".wav"), files);
#endif // __linux__
	BigInteger allNotes;
	allNotes.setRange(0, 128, true);
	_audioFormatManager.registerBasicFormats();
	_synth.clearSounds();

	it = files.begin();
	channel = 1;
	while (it != files.end())
	{
		std::wcout << "File = " << *it << std::endl;
		std::wcout << "FileName = " << FileManager::getFileName(*it) << std::endl;
		File* file = new File((*it).c_str());
		ScopedPointer<AudioFormatReader> reader = _audioFormatManager.createReaderFor(*file);
		if (reader)
		{
			try
			{
				SynthesizerInstrument::Ptr instrument(new SynthesizerInstrument(FileManager::getFileName(*it), *reader, allNotes, 72, 0, 1, 1.0, channel));
				_synth.addSound(instrument);
			}
			catch (const std::exception & e)
			{
				std::wcerr << "WARNING : Can not find instrument from the samples : " << FileManager::getFileName(*it) << std::endl;
			}
		}
		else
			std::wcerr << "WARNING : Can not find instrument from the samples : " << FileManager::getFileName(*it) << std::endl;
		++it;
		channel++;
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
