/*
  ==============================================================================

    Midi.cpp
    Created: 7 Mar 2017 9:49:31pm
    Author:  Anthony

  ==============================================================================
*/

#include "Midi.hh"
#include <iostream>
Midi::Midi()
{
}

Midi::Midi(const Midi & midi)
{
	_midi = midi.getMidiArray();
	_midiSize = midi.getMidiSize();
}

Midi::~Midi()
{
}

Midi & Midi::operator=(const Midi & midi)
{
	_midi = midi.getMidiArray();
	_midiSize = midi.getMidiSize();
	return (*this);
}

byteArray Midi::getMidiArray(void) const
{
	return (_midi);
}

void Midi::setMidiArray(const byteArray midi)
{
	_midi = midi;
}

size_t Midi::getMidiSize(void) const
{
	return (_midiSize);
}

void Midi::setMidiSize(const size_t size)
{
	_midiSize = size;
}
