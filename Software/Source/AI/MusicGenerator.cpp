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
  parameters.setBpm(80);
  Instrument instru;
  instru.name = "Piano";
  instru.nb = ACOUSTICGRANDPIANO;
  instru.channel = 1;
  instru.velocity = 100; //Need change
  parameters.addInstrument(instru);
  parameters.setStyleName("Blues");

  srand(parameters.getSeed());
  ObjectMarkov						markovObj(SOURCEMARKOV + std::string("blues.json"), 1, parameters.getSeed());

  unsigned char						i;
  std::vector<std::pair<char, char> >			markovChords;
  std::vector<std::pair<char, char> >			markovTmp;
  std::vector<std::pair<char, char> >			markovArpeggio2; // will be removed
  std::vector<Pattern *>				markovArpeggio;
  StyleSettings						style;
  std::vector<std::pair<char, char> >			chord;
  Chords						allChords;

  markovObj.callLua();
  markovChords = markovObj.getVectorFromJson();

  style = markovObj.getStyleFromJson();

  Resolution::parsingMarkov(style, &markovChords);

  markovChords.push_back(markovChords[0]);
  markovChords.push_back(markovChords[0]);
  markovChords.push_back(markovChords[0]);

  markovChords.push_back(std::make_pair(AI::searchNoteFromDistWhite((markovChords[0].first / 8 * 8), 3) + markovChords[0].first % 8, 4));
  markovChords.push_back(std::make_pair(AI::searchNoteFromDistWhite((markovChords[0].first / 8 * 8), 3) + markovChords[0].first % 8, 4));
  markovChords.push_back(markovChords[0]);
  markovChords.push_back(markovChords[0]);

  markovChords.push_back(std::make_pair(AI::searchNoteFromDistWhite((markovChords[0].first / 8 * 8), 4) + markovChords[0].first % 8, 4));
  markovChords.push_back(std::make_pair(AI::searchNoteFromDistWhite((markovChords[0].first / 8 * 8), 3) + markovChords[0].first % 8, 4));
  markovChords.push_back(markovChords[0]);
  markovChords.push_back(std::make_pair(AI::searchNoteFromDistWhite((markovChords[0].first / 8 * 8), 4) + markovChords[0].first % 8, 4));

  Disposition::placeChords(parameters, markovChords);

  i = 0;
  while (i != markovChords.size())
    {
      if (i == 0 || markovChords[i].first != markovChords[i - 1].first)
	{
	  StyleSettings					proba;
	  std::vector<char>					strong;
	  std::vector<char>					medium;
	  std::vector<char>					weak;

	  chord = allChords.getChordPairFromName(markovChords[i].first);
	  AI::classifyNotes(chord, &strong, &medium, &weak);
	  AI::calculateProbaToNote(&proba, strong, PROBASTRONG);
	  AI::calculateProbaToNote(&proba, medium, PROBAMEDIUM);
	  AI::calculateProbaToNote(&proba, weak, PROBAWEAK);
	  AI::calculateProbaToScaleFromNote(&proba, strong, medium, weak);

	  ObjectMarkov				       	markovObj(proba, 3, parameters.getSeed());
	  markovObj.callLua();

	  markovTmp = markovObj.getVectorFromJson();
	  Resolution::parsingMarkov(&markovTmp, strong, medium, weak);
	  char						n;
	  Pattern					*tmpPattern= new Pattern(chord);

	  n = -1;
	  while (++n != static_cast<char>(markovTmp.size()))
	    tmpPattern->addNote(markovTmp[n], n, 1, i);
	  markovArpeggio.push_back(tmpPattern);
	}
      if (!markovArpeggio2.size())
	markovArpeggio2 = markovTmp;
      else
	markovArpeggio2.insert(markovArpeggio2.end(), markovTmp.begin(), markovTmp.end());
      i++;
    }

  Disposition::placeArpeggios(parameters, markovArpeggio2);

  parameters.setMidi(parameters._midiManager.createMidi(48));
  parameters._midiManager.writeToFile("./test.mid");

  return (Midi());
}
