/*
  ==============================================================================

    Player.cpp
    Created: 13 Mar 2017 1:44:54pm
    Author:  Anthony

  ==============================================================================
*/

#include "Player.hh"

Player::Player()
{
	_soundManager = new SoundManager();
}

Player::~Player()
{
	delete _soundManager;
}

void Player::setMusicparameters(MusicParameters params)
{
	_musicParameters = params;
}

void Player::Play()
{
	MusicGenerator gen;

	gen.createMusic(_musicParameters);
	_soundManager->play(_musicParameters.getMidi());
}
