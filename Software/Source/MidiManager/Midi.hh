/*
  ==============================================================================

    Midi.h
    Created: 7 Mar 2017 9:49:31pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef MIDI_HH_INCLUDED
#define MIDI_HH_INCLUDED

#include <cstddef>

typedef char* byteArray;

class Midi
{
public:
	Midi();
	Midi(const Midi &midi);
	~Midi();
	Midi &operator=(const Midi &midi);

	byteArray	getMidiArray(void) const;
	void		setMidiArray(const byteArray midi);
    size_t	    getMidiSize(void) const;
	void		setMidiSize(const size_t size);

private:
	byteArray	_midi;
	size_t   	_midiSize;
};

#endif  // MIDI_HH_INCLUDED
