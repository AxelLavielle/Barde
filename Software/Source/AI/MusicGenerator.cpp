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
	int seed = 10;
	srand(seed);
	ObjectMarkov						markovObj("blues.json", 1, seed);
	std::vector<std::pair<char, char> >	markov;
	StyleSettings						style;

	markov = markovObj.getVectorFromJson();
	style = markovObj.getStyleFromJson();
	Resolution::parsingMarkov(style, markov);
  // Disposition
  // _resolution.parsingDisposition();
  // _resolution.addBridge();
	return (Midi());
}
