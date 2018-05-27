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
	for (int i = 127; --i >= 0;)
	{
		_synth.addVoice(new SamplerVoice());
	}
	setUsingSampledSound();
}

std::wstring s2ws(const std::string& s)
{
	int slength = (int)s.length() + 1;
	#ifdef __linux__
	wchar_t* buf = new wchar_t[slength];
	mbtowc(buf, s.c_str(), slength);
	#else
	int len;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	#endif
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void Synthesizer::setUsingSampledSound()
{
	WavAudioFormat	wavFormat;
	std::vector<std::wstring> files;
	std::vector<std::wstring>::iterator it;
	#ifdef __linux__
	//std::wcout << "Directory = " << FileManager::getCurrentDirectory() << s2ws("/../../Samples/Drums/") << std::endl;
	FileManager::getFilesList(FileManager::getCurrentDirectory() + s2ws("/../../Samples/Drums/"), s2ws(".wav"), files);
	FileManager::getFilesList(FileManager::getCurrentDirectory() + s2ws("/../../Samples/"), s2ws(".wav"), files);
	#else
	std::wstring test = FileManager::getCurrentDirectory();
	//std::wcout << "Directory = " << FileManager::getCurrentDirectory() + s2ws("/../../../../Samples/Drums/") << std::endl;
	FileManager::getFilesList(FileManager::getCurrentDirectory() + s2ws("/../Samples/Drums/"), s2ws(".wav"), files);
	FileManager::getFilesList(FileManager::getCurrentDirectory() + s2ws("/../Samples/"), s2ws(".wav"), files);
#endif // __linux__
	BigInteger allNotes;
	allNotes.setRange(0, 128, true);
	_audioFormatManager.registerBasicFormats();
	_synth.clearSounds();

	it = files.begin();
	while (it != files.end())
	{
		//std::wcout << "File = " << *it << std::endl;
		//std::wcout << "FileName = " << FileManager::getFileName(*it) << std::endl;
		File* file = new File((*it).c_str());
		std::shared_ptr<AudioFormatReader> reader = std::shared_ptr<AudioFormatReader>(_audioFormatManager.createReaderFor(*file));
		if (reader)
		{
			try
			{
				_instruments.insert(std::make_pair(instrumentList.at(FileManager::getFileName(*it)), new SynthesizerInstrument(FileManager::getFileName(*it), *reader, allNotes, 72, 0, 1, 1.0, instrumentList.at(FileManager::getFileName(*it)))));
			}
			catch (const std::exception & e)
			{
				(void)e;
				std::wcerr << "WARNING : Can not find instrument from the samples : " << FileManager::getFileName(*it) << std::endl;
			}
		}
		else
			std::wcerr << "WARNING : Can not find instrument from the samples : " << FileManager::getFileName(*it) << std::endl;
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
	//Need to release _instruments
}

void Synthesizer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
	MidiBuffer				incomingMidi;
	MidiMessage				midiEvent;
	int						samplePos;
	int						programNb;
	SynthesizerInstrument	*instrument;


	bufferToFill.clearActiveBufferRegion();
	_midiCollector.removeNextBlockOfMessages(incomingMidi, bufferToFill.numSamples);

	MidiBuffer::Iterator it(incomingMidi);
	while (it.getNextEvent(midiEvent, samplePos))
	{
		if (midiEvent.isProgramChange())
		{
			programNb = midiEvent.getProgramChangeNumber();
			try
			{
				std::cout << "ChangeInstrument, channel : " << midiEvent.getChannel() << std::endl;
				//_synth.removeSound(midiEvent.getChannel()); do not decomment this line !!
				instrument = _instruments.at(static_cast<NbInstrument>(programNb));
				instrument->setChannel(midiEvent.getChannel());
				_synth.addSound(instrument);
				std::cout << "ChangeInstrument, programNb : " << programNb << std::endl;
			}
			catch (const std::exception e)
			{
				std::wcerr << "WARNING : Can not load instrument number : " << programNb << std::endl;
			}
		}
	}
	_synth.renderNextBlock(*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
}

void Synthesizer::addMessage(MidiMessage const & msg)
{
	_midiCollector.addMessageToQueue(msg);
}
