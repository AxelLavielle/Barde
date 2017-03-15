/*
  ==============================================================================

    MusicGenerator.cpp
    Created: 13 Mar 2017 1:46:35pm
    Author:  Anthony

  ==============================================================================
*/

#include "MusicGenerator.hh"

MusicGenerator::MusicGenerator()
{
  
}

MusicGenerator::~MusicGenerator()
{

}

Midi			MusicGenerator::createMusic()
{
	ObjectMarkov	markovObj("blues.json", 1, std::time(nullptr));

   //_resolution.setStyleSettings(_musicParameter);
   //_resolution.parsingMarkov(_musicParameter);
  // Disposition
  // _resolution.parsingDisposition();
  // _resolution.addBridge();
	return (Midi());
}
