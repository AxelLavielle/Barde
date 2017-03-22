/*
  ==============================================================================

    Player.h
    Created: 13 Mar 2017 1:44:54pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef PLAYER_HH_INCLUDED
#define PLAYER_HH_INCLUDED

#include "AI/MusicGenerator.hh"
#include "SoundManager/JuceSound.hh"

class Player
{
public:
	Player();
	~Player();
	void Play();

private:
	ISoundManager		*_soundManager;
};

#endif  // PLAYER_HH_INCLUDED
