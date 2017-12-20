/*
  ==============================================================================

    Synthesizer.h
    Created: 20 Dec 2017 11:25:49am
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "ASoundManager.hh"
#include "../Tools.hh"

struct Synthesizer : public AudioSource
{

public:
	Synthesizer();
	void setUsingSampledSound();

	void prepareToPlay(int /*samplesPerBlockExpected*/, double sampleRate) override;
	void releaseResources() override;
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
	void addMessage(MidiMessage const &msg);

private:
	MidiMessageCollector _midiCollector;
	Synthesiser _synth;
	AudioFormatManager _audioFormatManager;
};
