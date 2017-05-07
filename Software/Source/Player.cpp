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

void Player::Play()
{
	MusicGenerator gen;
	MusicParameters param;

	gen.createMusic(param);
	_soundManager->play(param.getMidi());
}
