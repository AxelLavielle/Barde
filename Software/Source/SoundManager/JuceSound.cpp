/*
  ==============================================================================

    JuceSound.cpp
    Created: 13 Mar 2017 1:42:58pm
    Author:  Anthony

  ==============================================================================
*/

#include "JuceSound.hh"

SoundManager::SoundManager()
{
	
	_midiOutput = MidiOutput::openDevice(0);
}

SoundManager::~SoundManager()
{

}

const MidiMessageSequence		*SoundManager::MidiToMessageSequence(const Midi &midi)
{
	MemoryInputStream	stream(midi.getMidiArray(), midi.getMidiSize(), true);

	//std::cout << "midi == " << midi.getMidiSize() << std::endl;
	_midiBuff.readFrom(stream);
	if (_midiBuff.getNumTracks() > 0)
		return (_midiBuff.getTrack(0));
	return (NULL);
}

bool					SoundManager::play(const Midi &midi)
{
	MidiMessage			tmp;
	const MidiMessageSequence	*midiSequence;
	double				temps = (1.0 / (80.0 / 60.0)) * 1000;

	if ((midiSequence = MidiToMessageSequence(midi)) == NULL)
	{
		std::cerr << "ERROR: Can not convert Midi Buffer" << std::endl;
		return false;
	}
	//std::cout << "nb of event : " << midiSequence->getNumEvents() << std::endl;
	for (int i = 0; i < midiSequence->getNumEvents(); i++)
	{
		tmp = midiSequence->getEventPointer(i)->message;
		//std::cout << "tmp = " << tmp.getDescription() << std::endl;

		if (tmp.isNoteOn())
		{
			_midiOutput->sendMessageNow((const MidiMessage &)tmp);
			
			Tools::sleep(temps);
		}
	}
	return true;
}

bool					SoundManager::stop(const Midi &midi)
{
	return true;
}

bool					SoundManager::pause(const Midi &midi)
{
	return true;
}

bool					SoundManager::setVolume(const Midi &midi)
{
	return true;
}

bool					SoundManager::stopAll()
{
	return true;
}

bool SoundManager::setVolume(const int volume)
{
	return true;
}
