/*
  ==============================================================================

    Instrument.h
    Created: 15 Mar 2017 3:31:53pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef INSTRUMENT_HH_INCLUDED
#define INSTRUMENT_HH_INCLUDED

/*!
 * \file Instrument.hh
 * \brief File containing the Instrument class
 */

#include <string>
#include "MidiManager/Instruments.hh"

/*! \class Instrument
 * \brief Instrument class contain instrument data
 *
 *  Instrument class contain instrument data needed for the sound library
 */
class Instrument
{
public:
	std::string		name;  /*!< Name of the instrument */
	NbInstrument	nb;  /*!< Instrument number */
	int				channel;  /*!< Channel corresponding to the instrument */
	float			velocity;  /*!< Default velocity of the instrument */
};

#endif  // INSTRUMENT_HH_INCLUDED
