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

  GetMidiOutputDevice();
}

SoundManager::~SoundManager()
{
}

const MidiMessageSequence		*SoundManager::MidiToMessageSequence(const Midi &midi)
{
	MemoryInputStream	stream(midi.getMidiArray(), midi.getMidiSize(), true);

	_midiBuff.readFrom(stream);
	if (_midiBuff.getNumTracks() > 0)
		return (_midiBuff.getTrack(0));
	return (NULL);
}

bool							SoundManager::play(const Midi &midi)
{
	MidiMessage					msg;
	const MidiMessageSequence	*midiSequence;
	const float	    			time = (60.0 / 80.0);
	unsigned int				currentTime;
	unsigned int				msgTime;


	if ((midiSequence = MidiToMessageSequence(midi)) == NULL)
	{
		std::cerr << "ERROR: Can not convert Midi Buffer" << std::endl;
		return false;
	}

	currentTime = 0;
	for (int i = 0; i < midiSequence->getNumEvents(); i++)
	{
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

//bool							SoundManager::play(const Midi &midi)
//{
//	MidiMessage					tmp;
//	const MidiMessageSequence	*midiSequence;
//	const unsigned int	    	temps = (1.0 / (80.0 / 60.0)) * 1000;
//	double						k;
//	double						resTime;
//	double						currentTemp;
//
//	if ((midiSequence = MidiToMessageSequence(midi)) == NULL)
//	{
//		std::cerr << "ERROR: Can not convert Midi Buffer" << std::endl;
//		return false;
//	}
//	tmp = midiSequence->getEventPointer(0)->message;
//	k = tmp.getTimeStamp();
//	currentTemp = 0;
//	resTime = 0;
//	for (int i = 0; i < midiSequence->getNumEvents(); i++)
//	{
//		tmp = midiSequence->getEventPointer(i)->message;
//
//		if (tmp.isNoteOn())
//		{
//
//			if (resTime && tmp.getTimeStamp() != k)
//			{
//				unsigned int tmpTime = static_cast<unsigned int>(tmp.getTimeStamp() / 1000);
//				double timeToSleep = temps - temps * ((tmp.getTimeStamp() / 1000) - tmpTime);
//
//				std::cout << "------------------------------------------" << std::endl;
//				std::cout << "Temps actuel : " << currentTemp / temps << std::endl;
//				if (tmpTime <= currentTemp / temps && resTime >= timeToSleep)
//				{
//					std::cout << "Je Sleep pour (resTime1) " << resTime - timeToSleep << std::endl;
//					std::cout << "resTime " << resTime << std::endl;
//					std::cout << "timeToSleep " << timeToSleep << std::endl;
//					//Tools::sleep(resTime - timeToSleep);
//					Tools::sleepActive(resTime - timeToSleep);
//					currentTemp += resTime - timeToSleep;
//					resTime = temps - (resTime + timeToSleep);
//					if (resTime < 0)
//						resTime = 0;
//				}
//				else
//				{
//					std::cout << "Je Sleep pour (resTime2) " << resTime << std::endl;
//					//Tools::sleep(resTime);
//					Tools::sleepActive(resTime);
//					currentTemp += resTime;
//					resTime = 0;
//				}
//				std::cout << "------------------------------------------" << std::endl;
//			}
//
//			if (resTime)
//			{
//				std::cout << "Je Sleep pour (resTime3) " << resTime << std::endl;
//				//Tools::sleep(resTime);
//				Tools::sleepActive(resTime);
//				currentTemp += resTime;
//				resTime = 0;
//			}
//			else if (tmp.getTimeStamp() != k)
//			{
//				unsigned int tmpTime = static_cast<unsigned int>(tmp.getTimeStamp() / 1000);
//				double timeToSleep = temps * ((tmp.getTimeStamp() / 1000) - tmpTime);
//
//				std::cout << "------------------------------------------" << std::endl;
//				std::cout << "Temps de la prochaine note " << tmp.getTimeStamp() / 1000 << std::endl;
//				resTime = temps - ((timeToSleep) ? (timeToSleep) : (temps));
//
//				if (tmp.getTimeStamp() / 1000 - currentTemp / temps > 0.01)
//				{
//					std::cout << "Temps actuel : " << currentTemp / temps << std::endl;
//					std::cout << "Je Sleep pour : " << ((timeToSleep) ? (timeToSleep) : (temps)) << std::endl;
//					std::cout << "------------------------------------------" << std::endl;
//					currentTemp += ((timeToSleep) ? (timeToSleep) : (temps));
//					//Tools::sleep((timeToSleep) ? (timeToSleep) : (temps));
//					Tools::sleepActive((timeToSleep) ? (timeToSleep) : (temps));
//				}
//			}
//
////#ifdef __linux__
//			std::cout << "Je joue la note qui a le temps : " << tmp.getTimeStamp() / 1000 << std::endl;
//			std::cout << "Channel =  : " << tmp.getChannel() << std::endl;
//			tmp.setTimeStamp(Time::getMillisecondCounterHiRes());
//			_synthAudioSource.addMessage(tmp);
////#else
////			std::cout << "Je joue la note qui a le temps : " << tmp.getTimeStamp() / 1000 << std::endl;
////			tmp.setTimeStamp(Time::getMillisecondCounterHiRes());
////			_midiOutput->sendMessageNow(tmp);
////#endif
//
//
//			k = tmp.getTimeStamp();
//		}
//		else
//		{
//			tmp.setTimeStamp(Time::getMillisecondCounterHiRes());
//			_synthAudioSource.addMessage(tmp);
////			_midiOutput->sendMessageNow((const MidiMessage &)tmp);
//		}
//	}
//	//_midiOutput->clearAllPendingMessages();
//	return true;
//}

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
