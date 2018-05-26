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
//#ifdef __linux__

  _deviceManager = new AudioDeviceManager();
  _deviceManager->initialise (2, 2, nullptr, true, String(), nullptr);
  _audioSourcePlayer.setSource (&_synthAudioSource);
  _deviceManager->addAudioCallback (&_audioSourcePlayer);

//#endif
  _stop = false;

  GetMidiOutputDevice();
}

SoundManager::~SoundManager()
{
	delete _deviceManager;
	delete _midiOutput;
}

const MidiMessageSequence		*SoundManager::MidiToMessageSequence(const Midi &midi)
{
	MemoryInputStream	stream(midi.getMidiArray(), midi.getMidiSize(), true);

	_midiBuff.readFrom(stream);
	if (_midiBuff.getNumTracks() > 0)
		return (_midiBuff.getTrack(0));
	return (NULL);
}

void SoundManager::launch(std::vector<std::pair<Midi, int> > &_gen2playQ, std::mutex &_gen2playM, bool &stop, CondVariable &cond)
{
	Midi m;
	int bpm = 0;

	while (!stop)
	{
		std::cout << "==A" << std::endl;
		bool b = false;
		_gen2playM.lock();
		std::cout << "==B" << std::endl;
		if (_gen2playQ.size() > 0)
		{
			std::cout << "==C" << std::endl;
			m = _gen2playQ[0].first;
			std::cout << "==D" << std::endl;
			bpm = _gen2playQ[0].second;
			std::cout << "==E" << std::endl;
			b = true;
			std::cout << "==F" << std::endl;
			_gen2playQ.erase(_gen2playQ.begin());
			std::cout << "==G" << std::endl;
		}
		else
			b = false;
		std::cout << "==H" << std::endl;
		_gen2playM.unlock();
		std::cout << "==I" << std::endl;
		if (b)
			play(m, bpm, stop);
		else
			Tools::sleepActive(100);
		std::cout << "==J" << std::endl;
		if (_stop)
		{
			std::cout << "==K" << std::endl;
			cond.wait();
			std::cout << "==L" << std::endl;
			_stop = !_stop;
			std::cout << "==M" << std::endl;
		}
		std::cout << "==N" << std::endl;
	}
}

bool							SoundManager::play(const Midi &midi, int bpm, bool &stop)
{
	MidiMessage					msg;
	const MidiMessageSequence	*midiSequence;
	const float	    			time = (60.0f / static_cast<float>(bpm));
	unsigned int				currentTime;
	unsigned int				msgTime;

	if ((midiSequence = MidiToMessageSequence(midi)) == NULL)
	{
		std::cerr << "ERROR: Can not convert Midi Buffer" << std::endl;
		return false;
	}

	currentTime = 0;
	for (int i = 0; i < midiSequence->getNumEvents() && !stop && !_stop; i++)
	{
		std::cout << i << std::endl;
		msg = midiSequence->getEventPointer(i)->message;

		if (msg.isNoteOn())
		{
			msgTime = static_cast<unsigned int>(msg.getTimeStamp());
			if (msgTime > currentTime)
			{
				std::cout << "msgtime : " << msgTime << std::endl;
				std::cout << "currentTime : " << currentTime << std::endl;
				std::cout << "time : " << time << std::endl;
				std::cout << "Je sleep pour : " << (msgTime - currentTime) * time  << std::endl;
				Tools::sleepActive(static_cast<unsigned int>((msgTime - currentTime) * time));
				currentTime = msgTime;
			}
			std::cout << "Je joue la note qui a le temps : " << msgTime << std::endl;
			msg.setTimeStamp(Time::getMillisecondCounterHiRes());
			_synthAudioSource.addMessage(msg);
		}
		else
		{
			msg.setTimeStamp(Time::getMillisecondCounterHiRes());
			_synthAudioSource.addMessage(msg);
		}
 	}
	return true;
}

void SoundManager::GetMidiOutputDevice()
{
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

bool					SoundManager::stop()
{
	_stop = true;
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
