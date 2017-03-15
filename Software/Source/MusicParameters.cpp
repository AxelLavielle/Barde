/*
  ==============================================================================

    MusicParameters.cpp
    Created: 13 Mar 2017 1:47:13pm
    Author:  Anthony

  ==============================================================================
*/

#include "MusicParameters.hh"

MusicParameter::MusicParameter()
{
}

MusicParameter::~MusicParameter()
{
}

int MusicParameter::getBpm() const
{
	return (_bpm);
}

void MusicParameter::setBpm(const int bpm)
{
	_bpm = bpm;
}

int MusicParameter::getSeed() const
{
	return (_seed);
}

void MusicParameter::setSeed(const int seed)
{
	_seed = seed;
}
