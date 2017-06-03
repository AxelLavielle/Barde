/*
  ==============================================================================

    Midi.h
    Created: 7 Mar 2017 9:49:31pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef MIDI_HH_INCLUDED
#define MIDI_HH_INCLUDED

/*!
 * \file Midi.hh
 * \brief File containing the Midi class and the typedef of byteArray
 */

#include <cstddef>
#include <cstring>

typedef char* byteArray;

/*! \class SoundManager
 * \brief Midi contain all the midi data
 *
 *  This class allows us to store all the midi data in a byteArray
 */
class Midi
{
public:
	/*!
 *  \brief Constructor
 *
 *  Empty
 *
 */
	Midi();
	/*!
 *  \brief Constructor
 *
 *  Copy constructor
 *
 */
	Midi(const Midi &midi);
	/*!
	 *  \brief Destructor
	 *
	 *  Empty
	 *
	 */
	~Midi();
	/*!
	*  \brief Operator overloard for canonical format
	*
	*  Operator overloard for canonical format
	*
	*  \param midi : midi object need to be copied
	*  \return this class
	*/
	Midi &operator=(const Midi &midi);

	/*!
	*  \brief Get the midi array containing all the midi data in raw format
	*
	*  Operator overloard for canonical format
	*
	*  \param midi : midi object need to be copied
	*  \return this class
	*/
	byteArray	getMidiArray(void) const;
	/*!
	*  \brief Set the Midi array with raw data
	*
	*  Set the Midi array with raw data given as parameter
	*
	*  \param midi : byteArray containing raw midi data
	*  \return set the midiarray
	*/
	void		setMidiArray(const byteArray midi);
	/*!
	*  \brief Get the size of the midi array
	*
	*   Get the size of the midi data containing in the midi array
	*
	*  \return midi array size in byte
	*/
  size_t	    getMidiSize(void) const;
	/*!
	*  \brief Set the size of the midi array
	*
	*  Set the size of the midi array containing the raw midi data
	*
	*  \param midi : size of the midi array
	*  \return set the size of the midi array
	*/
	void		setMidiSize(const size_t size);

private:
	byteArray	_midi; /*!< array containing the raw midi data*/
	size_t   	_midiSize; /*!< size of the midi array*/
};

#endif  // MIDI_HH_INCLUDED
