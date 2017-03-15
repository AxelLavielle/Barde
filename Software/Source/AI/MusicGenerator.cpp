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

Midi			MusicGenerator::createMusic(MusicParameters &parameters)
{
  parameters.setSeed(std::time(NULL));
  srand(parameters.getSeed());
  ObjectMarkov						markovObj("blues.json", 1, parameters.getSeed());
  std::vector<std::pair<char, char> >	markov;
  StyleSettings						style;
  std::cout << "-----------------------------------------------" << std::endl;
  
  markovObj.callLuaMarkov();
  markov = markovObj.getVectorFromJson();
  style = markovObj.getStyleFromJson();
  Resolution::parsingMarkov(style, markov);

  std::cout << "-----------------------------------------------" << std::endl;
  return (Midi());
}
