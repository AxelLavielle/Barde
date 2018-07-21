/*
  ==============================================================================

    SynthesizerInstrument.h
    Created: 15 Jan 2018 8:52:13pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef SYNTHESIZERINSTRUMENT_HH
#define SYNTHESIZERINSTRUMENT_HH

#include "JuceHeader.h"

class SynthesizerInstrument : public SamplerSound
{
public:
	SynthesizerInstrument(const String &name, AudioFormatReader &reader, const BigInteger & midiNotes, int midiNoteForNormalPitch,
		double attackTimeSecs, double releasTimeSecs, double maxSampleLengthSeconds, int midiChannel);

	bool appliesToNote(int midiNoteNumber) override;
	bool appliesToChannel(int midiChannel) override;
	void setChannel(int midiChannel);
	virtual ~SynthesizerInstrument();

private:
	int									_channel;
};

#endif /*SYNTHESIZERINSTRUMENT_HH*/