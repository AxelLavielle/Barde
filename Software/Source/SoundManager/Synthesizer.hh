/*
  ==============================================================================

    Synthesizer.h
    Created: 20 Dec 2017 11:25:49am
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include <stdio.h>
#include "JuceHeader.h"
#include "ASoundManager.hh"
#include "../Tools.hh"
#include "../Instrument.hh"
#include "../FileManager.hh"
#include "SynthesizerInstrument.hh"

struct Synthesizer : public AudioSource
{

public:
	Synthesizer();
	void setUsingSampledSound();

	void prepareToPlay(int /*samplesPerBlockExpected*/, double sampleRate) override;
	void releaseResources() override;
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
	void addMessage(const MidiMessage &msg);
	void loadSamples();

private:
	MidiMessageCollector _midiCollector;
	Synthesiser _synth;
	AudioFormatManager _audioFormatManager;
	std::map<NbInstrument, SynthesizerInstrument*>	_instruments;
};
