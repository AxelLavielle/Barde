/*
  ==============================================================================

    UserSettings.cpp
    Created: 28 May 2017 6:10:55pm
    Author:  Oreo

  ==============================================================================
*/

#include "UserSettings.h"

UserSettings::UserSettings()
{
	_mute = false;
	_language = EN;
	_volume = 50;
	_BPM = 120; 
}

UserSettings::UserSettings(bool mute, Language language, int volume, int BPM)
{
	_mute = mute;
	_language = language;
	_volume = volume;
	_BPM = BPM;
}

UserSettings::UserSettings(int volume, int BPM)
{
	_mute = false;
	_language = EN;
	_volume = volume;
	_BPM = BPM;
}

UserSettings::~UserSettings()
{

}

int UserSettings::getVolume()
{
	return (_volume);
}

int UserSettings::getBPM()
{
	return (_BPM);
}

bool UserSettings::isMute()
{
	return (_mute);
}

Language UserSettings::getLanguage()
{
	return (_language);
}

void UserSettings::setVolume(int volume)
{
	if (volume >= 0 && volume <= 100)
	{
		_volume = volume;
	}
}

void UserSettings::setBPM(int BPM)
{
	_BPM = BPM;
}

void UserSettings::setMute(bool mute)
{
	_mute = mute;
}

void UserSettings::setLanguage(Language language)
{
	_language = language;
}

