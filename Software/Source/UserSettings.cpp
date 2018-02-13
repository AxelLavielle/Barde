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
}

UserSettings::UserSettings(MusicParameters *musicParameters)
{
	_mute = false;
	_language = EN;
	_volume = 50;
	_musicParameters = musicParameters;
	std::cout << "Created FroM here" << std::endl;
}


UserSettings::UserSettings(bool mute, Language language, int volume)
{
	_mute = mute;
	_language = language;
	_volume = volume;
}

UserSettings::UserSettings(int volume)
{
	_mute = false;
	_language = EN;
	_volume = volume;
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
	int returnBpm;

	returnBpm = _musicParameters->getBpm();
	return (returnBpm);
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
	_musicParameters->setBpm(BPM);
}

void UserSettings::setMute(bool mute)
{
	_mute = mute;
}

void UserSettings::setLanguage(Language language)
{
	_language = language;
}

