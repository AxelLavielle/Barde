/*
  ==============================================================================

    SynthesizerInstrument.cpp
    Created: 15 Jan 2018 8:51:48pm
    Author:  Anthony

  ==============================================================================
*/

#include "SynthesizerInstrument.hh"

SynthesizerInstrument::SynthesizerInstrument(const String &name, AudioFormatReader &reader, const BigInteger & midiNotes, int midiNoteForNormalPitch,
	double attackTimeSecs, double releasTimeSecs, double maxSampleLengthSeconds, int midiChannel = 0)
	: SamplerSound(name, reader, midiNotes, midiNoteForNormalPitch, attackTimeSecs, releasTimeSecs, maxSampleLengthSeconds)
{
	_channel = midiChannel;
}

SynthesizerInstrument::~SynthesizerInstrument()
{
}

bool SynthesizerInstrument::appliesToNote(int midiNoteNumber)
{
	(void)midiNoteNumber;
	return (true);
}

bool SynthesizerInstrument::appliesToChannel(int midiChannel)
{
	if (midiChannel == _channel)
	{
		return (true);
	}
	return (false);
}

void SynthesizerInstrument::setChannel(int midiChannel)
{
	_channel = midiChannel;
}
