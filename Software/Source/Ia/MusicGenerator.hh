/*
  ==============================================================================

    MusicGenerator.h
    Created: 13 Mar 2017 1:46:35pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef MUSICGENERATOR_HH_INCLUDED
# define MUSICGENERATOR_HH_INCLUDED

#include "Resolution.hh"
#include "../MidiManager/Midi.hh"
// #include "Disposition.hh"
// #include "MusicParameters"

class			MusicGenerator
{
public:
  MusicGenerator();
  ~MusicGenerator();
  Midi			createMusic();

private:
  Resolution		_resolution;
  // Disposition	_disposition;
  // MusicParameters	_parameters;
};

#endif  // MUSICGENERATOR_HH_INCLUDED
