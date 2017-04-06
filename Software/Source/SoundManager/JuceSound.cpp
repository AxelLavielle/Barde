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
	_midiOutput = MidiOutput::openDevice(MidiOutput::getDefaultDeviceIndex());
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

bool							SoundManager::play(const Midi &midi)
{
	MidiMessage					tmp;
	const MidiMessageSequence	*midiSequence;
	unsigned int		       	temps = (1.0 / (80.0 / 60.0)) * 1000;
	int							k;

	if ((midiSequence = MidiToMessageSequence(midi)) == NULL)
	{
		std::cerr << "ERROR: Can not convert Midi Buffer" << std::endl;
		return false;
	}
	tmp = midiSequence->getEventPointer(0)->message;
	k = tmp.getTimeStamp();
	for (int i = 0; i < midiSequence->getNumEvents(); i++)
	{

		tmp = midiSequence->getEventPointer(i)->message;

		if (tmp.isNoteOn())
		{
			_midiOutput->sendMessageNow((const MidiMessage &)tmp);
			if (tmp.getTimeStamp() != k)
			{
				Tools::sleep(temps);
			}
			k = tmp.getTimeStamp();
		}
	}
	//_midiOutput->clearAllPendingMessages();
	return true;
}

bool					SoundManager::stop(const Midi &) const
{
	//Not implemented
	return true;
}

bool					SoundManager::pause(const Midi &) const
{
	//Not implemented
	return true;
}

bool					SoundManager::setVolume(const Midi &) const
{
	//Not implemented
	return true;
}

bool					SoundManager::stopAll() const
{
	//Not implemented
	return true;
}

bool SoundManager::setVolume(const int)
{
	//Not implemented
	return true;
}
