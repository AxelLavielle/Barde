/*
  ==============================================================================

    MidiManager.h
    Created: 7 Mar 2017 5:25:20pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef MIDIMANAGER_HH_INCLUDED
#define MIDIMANAGER_HH_INCLUDED

/*!
 * \file MidiManager.hh
 * \brief File containing the class MidiManager
 */

#include <cstring>
#include "JuceHeader.h"
#include "MidiManager/AMidiManager.hh"

/*! \class MidiManager
 * \brief MidiManager manage the midi data
 *
 *  This class allows to create midi data through midi events
 */
class MidiManager : public AMidiManager
{
public:
	/*!
 *  \brief Constructor
 *
 *  Empty
 *
 */
	MidiManager();
	/*!
 *  \brief Constructor
 *
 *  Empty
 *
 */
	virtual ~MidiManager();
	/*!
	*  \brief Create note on event in midi sequence
	*
	*  This method add a note on event in the midi sequence
	*
	*  \param channel : the channel number corresponding to the note
	*  \param noteNumber : the note number
	*  \param velocity : the velocity of the note
	*  \param time : the time of the note
	*  \return Insert note event in the midi sequence
	*/
	virtual void noteOn(const int channel, const int noteNumber, const float velocity, const double time) noexcept;
	/*!
	*  \brief Create note on event in midi sequence
	*
	*  This method add a note on event in the midi sequence
	*
	*  \param instrument : the intrument corresponding to the note on event
	*  \param noteNumber : the note number
	*  \param velocity : the velocity of the note
	*  \param time : the time of the note
	*  \return Insert note event in the midi sequence
	*/
	virtual void noteOn(const Instrument &instument, const int noteNumber, const float velocity, const double time) noexcept;
	/*!
	*  \brief Create note off event in midi sequence
	*
	*  This method add a note off event in the midi sequence
	*
	*  \param channel : the channel corresponding to the note on event
	*  \param noteNumber : the note number
	*  \param velocity : the velocity of the note
	*  \param time : the time of the note
	*  \return Insert note event in the midi sequence
	*/
	virtual void noteOff(const int channel, const int noteNumber, const float velocity, const double time) noexcept;
	/*!
	*  \brief Create note off event in midi sequence
	*
	*  This method add a note off event in the midi sequence
	*
	*  \param instrument : the instrument corresponding to the note on event
	*  \param noteNumber : the note number
	*  \param velocity : the velocity of the note
	*  \param time : the time of the note
	*  \return Insert note event in the midi sequence
	*/
	virtual void noteOff(const Instrument &instrument, const int noteNumber, const float velocity, const double time) noexcept;
	/*!
	*  \brief Create midi object from midi sequence
	*
	*  This method create midi object from midi sequence
	*
	*  \param time : the time corresponding to the end of the midi sequence
	*  \return Midi object caontaining all the midi sequence
	*/
	virtual Midi createMidi(const double time);
	/*!
	*  \brief Write a midi file with from the midi sequence
	*
	*  This method write a midi file caontaining all the midi event
	*
	*  \param filePath : the path where the fil will be written
	*  \return Create a file to the specified path
	*/
	virtual void writeToFile(const std::string &filePath);
	/*!
	*  \brief Change signature of the midi sequence
	*
	*  This method add a changing signature event to the midi sequence
	*
	*  \param numerator : numerator of the signature
	*  \param denominator : denominator of the signature
	*  \param time : time of the signature event
	*  \return Insert signature event in the midi sequence
	*/
	virtual void setSignature(const unsigned int numerator, const unsigned int denominator, const double time);
	/*!
	*  \brief Change the tempo of the midi sequence
	*
	*  This method add a changing tempo event to the midi sequence
	*
	*  \param bpm : beats per minute
	*  \param time : denominator of the signature
	*  \return Insert tempo event in the midi sequence
	*/
	virtual void setTempo(const unsigned int bpm, const double time = 0);
	/*!
	*  \brief Change the instrument associated whit the channel number
	*
	*  This method assign an instrument to a channel number
	*
	*  \param channel : channel number
	*  \param instrumentNb : instrument number
	*  \param time : time of the association
	*  \return Insert change instrument event in the midi sequence
	*/
	virtual void changeInstrument(const int channel, const int instrumentNb, const double time);
	/*!
	*  \brief Change the instrument associated whit the channel number
	*
	*  This method assign an instrument to his channel number
	*
	*  \param instrument : instrument need to be assign
	*  \param time : time of the association
	*  \return Insert change instrument event in the midi sequence
	*/
	virtual void changeInstrument(const Instrument &instrument, const double time);

private:
	/*!
	*  \brief Add event message to a string list
	*
	*  This method is only usefull for debug, it Add event message to a string list
	*
	*  \param message : message added to list
	*  \return Insert message event to a string list
	*/
	void addMessageToList(const MidiMessage& message);
	/*!
	*  \brief Get the description of a midi event
	*
	*  This method is only usefull for debug, it get the description of a midi event
	*
	*  \param message : midi message
	*  \return description of the message
	*/
	String getMidiMessageDescription(const MidiMessage & m);

	MidiMessageSequence		_midiSequence; /*!< object containing all the sequences of the midi data*/
	MidiFile				_midiBuff; /*!< Buffer caontaining all the Midi data*/
	MemoryOutputStream		_midiStream; /*!< Memory stream containing the midi data in raw format*/
	unsigned int		_bpm;
};

#endif  // MIDIMANAGER_HH_INCLUDED
