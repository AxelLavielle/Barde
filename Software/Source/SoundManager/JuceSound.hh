/*
  ==============================================================================

    JuceSound.h
    Created: 13 Mar 2017 1:42:58pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef JUCESOUND_HH_INCLUDED
#define JUCESOUND_HH_INCLUDED

/*!
* \file JuceSound.hh
* \brief This file contain the class that manage the playing of sound
*/


#include "JuceHeader.h"
#include "ASoundManager.hh"
#include "../Tools.hh"

/*! \class SoundManager
 * \brief SoundManager manage the playing of sound
 *
 *  This class allows to play midi data, stop playing, pause playing and set the volume
 */
class SoundManager : public ASoundManager
{
public:
	/*!
 *  \brief Constructor
 *
 *  Set the Midi deive who play sound
 *
 */
	SoundManager();
	/*!
   *  \brief Destructor
   *
   *  Empty
   *
   */
	virtual ~SoundManager();
	/*!
	*  \brief Play all the notes contained in the midi data
	*
	*  This method send all the notes events contained in the midi data to the midi device
	*
	*  \param midi : midi data send to the midi device
	*  \return true in case of success playing and false in the others case
	*/
	virtual bool play(const Midi &midi);
	/*!
	*  \brief Stop the song who is being played
	*
	*  This method stop all the event send to the midi device and provoke the stop of the playing
	*
	*  \param midi : midi object need to stop
	*  \return true in case of success playing and false in the others case
	*/
	virtual bool stop(const Midi &midi) const;
	/*!
	*  \brief Pause the song who is being played
	*
	*  This method pause all the event send to the midi device and provoke the pause of the playing
	*
	*  \param midi : midi object need to pause
	*  \return true in case of success playing and false in the others case
	*/
	virtual bool pause(const Midi &midi) const;
	/*!
	*  \brief Stop all the songs who is being played
	*
	*  This method stop all the event send to the midi device and provoke the stop of the playing
	*
	*
	*  \return true in case of success playing and false in the others case
	*/
	virtual bool stopAll() const;
	/*!
	*  \brief Set the volume of the sonud
	*
	*  This method allow to set the volume of the midi device
	*
	*  \param volume : the value of the volume
	*  \return true in case of success playing and false in the others case
	*/
	virtual bool setVolume(const int volume);
	virtual bool setVolume(const Midi &midi) const;

private:
	int									volume = 0;
	MidiOutput					*_midiOutput;
	MidiFile						_midiBuff;
	AudioDeviceManager	_audioManager;

	const MidiMessageSequence		*MidiToMessageSequence(const Midi &midi);
};



#endif  // JUCESOUND_HH_INCLUDED
