/*
  ==============================================================================

    Midi.cpp
    Created: 7 Mar 2017 9:49:31pm
    Author:  Anthony

  ==============================================================================
*/

#include "Midi.hh"

Midi::Midi()
{
	_midi = new char();

}

Midi::Midi(const Midi & midi)
{
	char * tmp = midi.getMidiArray();
	_midiSize = midi.getMidiSize();
	_midi = new char[_midiSize];
	for (size_t i = 0; i < _midiSize; i++)
		_midi[i] = tmp[i];
}

Midi::~Midi()
{
	delete (_midi);
}

Midi & Midi::operator=(const Midi & midi)
{
	delete(_midi);
	char * tmp = midi.getMidiArray();
	_midiSize = midi.getMidiSize();
	_midi = new char[_midiSize];
	for (size_t i = 0; i < _midiSize; i++)
		_midi[i] = tmp[i];
	return (*this);
}

byteArray Midi::getMidiArray(void) const
{
	return (_midi);
}

void Midi::setMidiArray(const byteArray midi)
{
	delete(_midi);
	_midi = new char[_midiSize];
	for (size_t i = 0; i < _midiSize; i++)
		_midi[i] = midi[i];
}

size_t Midi::getMidiSize(void) const
{
	return (_midiSize);
}

void Midi::setMidiSize(const size_t size)
{
	_midiSize = size;
}
