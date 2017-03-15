/*
  ==============================================================================

    Instrument.h
    Created: 15 Mar 2017 3:31:53pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef INSTRUMENT_HH_INCLUDED
#define INSTRUMENT_HH_INCLUDED

#include <string>
#include "MidiManager/Instruments.hh"

class Instrument
{
public:
	std::string		name;
	NbInstrument	nb;
};

#endif  // INSTRUMENT_HH_INCLUDED
