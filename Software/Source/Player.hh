/*
  ==============================================================================

    Player.h
    Created: 13 Mar 2017 1:44:54pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef PLAYER_HH_INCLUDED
#define PLAYER_HH_INCLUDED

/*!
 * \file Player.hh
 * \brief File containing the Player class
 */

#include "AI/MusicGenerator.hh"
#include "SoundManager/JuceSound.hh"

/*! \class SoundManager
 * \brief Player manage the playing of music provided by the IA
 *
 *  Player manage the communication between the IA and the sound library in order to play music
 */
class Player
{
public:
	/*!
 *  \brief Constructor
 *
 *  Create Sound Manager pointer
 *
 */
Player();
/*!
 *  \brief Destructor
 *
 *  Destruct Sound Manager pointer
 *
 */
~Player();
/*!
*  \brief Start the playing of music
*
*   Start the playing of music provided by the IA
*
*  \return play music
*/
void Play();

private:
	ISoundManager		*_soundManager; /*!< Pointer to the sound manager*/
};

#endif  // PLAYER_HH_INCLUDED
