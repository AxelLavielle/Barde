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
#ifdef __linux__

  _deviceManager = new AudioDeviceManager();

  _deviceManager->initialise (2, 2, nullptr, true, String(), nullptr);


  _audioSourcePlayer.setSource (&_synthAudioSource);

  _deviceManager->addAudioCallback (&_audioSourcePlayer);

#endif

//  MidiOutput::getDefaultDeviceIndex()
  //_midiOutput = MidiOutput::createNewDevice("TEST");
  // _audioManager.initialise(128, 128, NULL, true);
	// _audioManager.setMidiOutput(_midiOutput);
  // std::cout << _midiOutput->getName() << std::endl;
  std::cout << "------" << "MidiOutput List" << "-------" << std::endl;
  int i = 0;
	int j = 0;
  StringArray test = _midiOutput->getDevices();
  while (i < test.size())
  {
		if (test[i][0] == 'F' && test[i][1] == 'L') {
			j = i;
			break;
		}
    std::cout << test[i] << std::endl;
    i++;
  }
	_midiOutput = MidiOutput::openDevice(j);
  std::cout << "------" << "END MidiOutput List" << "-------" << std::endl;
  // _audioManager.playTestSound();
  // std::cout << _audioManager.getDefaultMidiOutputName() << std::endl;
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

		if (tmp.getTimeStamp() == 0)
		{
			tmp.setTimeStamp(1);
		}

		if (tmp.isNoteOn())
		{
#ifdef __linux__
			_synthAudioSource.midiCollector.addMessageToQueue(tmp);
#else
			_midiOutput->sendMessageNow((const MidiMessage &)tmp);
#endif
			if (tmp.getTimeStamp() != k)
			{
				Tools::sleep(temps);
			}
			k = tmp.getTimeStamp();
		}
		else
		{
			_midiOutput->sendMessageNow((const MidiMessage &)tmp);
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
