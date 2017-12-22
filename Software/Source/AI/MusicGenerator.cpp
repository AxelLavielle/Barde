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
  /* PARAMETERS */
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
  /* PARAMETERS */

  /* INITIALISATION */
  ObjectMarkov						markovObj(SOURCEMARKOV + std::string("blues.json"), 1, parameters.getSeed());
  std::vector<std::pair<char, char> >			markovChords;
  std::vector<std::pair<char, char> >			markovTmp;
  StyleSettings						style;
  std::vector<std::pair<char, char> >			chord;
  Chords						allChords;
  /* INITIALISATION */

  /* CHORDS */
  markovObj.callLua();
  markovChords = markovObj.getVectorFromJson();
  style = markovObj.getStyleFromJson();
  Resolution::parsingMarkov(style, &markovChords);

  std::pair<char, char> noteA = markovChords[0];
  std::pair<char, char> noteB = std::make_pair(AI::searchNoteFromDist((markovChords[0].first / 8 * 8), 5) + markovChords[0].first % 8, 4);
  std::pair<char, char> noteC = std::make_pair(AI::searchNoteFromDist((markovChords[0].first / 8 * 8), 7) + markovChords[0].first % 8, 4);
  if (noteA.first > noteB.first)
	  noteB.second++;
  if (noteA.first > noteC.first)
	  noteC.second++;

  markovChords.push_back(noteA);
  markovChords.push_back(noteA);
  markovChords.push_back(noteA);
  markovChords.push_back(noteB);
  markovChords.push_back(noteB);
  markovChords.push_back(noteA);
  markovChords.push_back(noteA);
  markovChords.push_back(noteC);
  markovChords.push_back(noteB);
  markovChords.push_back(noteA);
  markovChords.push_back(noteC);

  Disposition::placeChords(parameters, markovChords);

  /* CHORDS */
  
  /* MARKOVIAN TREE GENERATION */		
  StyleSettings						proba;
  std::vector<char>					strong;
  std::vector<char>					medium;
  std::vector<char>					weak;
  chord = allChords.getChordPairFromName(markovChords[0].first);
  AI::classifyNotes(chord, &strong, &medium, &weak);
  AI::calculateProbaToNote(&proba, strong, PROBASTRONG);
  AI::calculateProbaToNote(&proba, medium, PROBAMEDIUM);
  AI::calculateProbaToNote(&proba, weak, PROBAWEAK);
  AI::calculateProbaToScaleFromNote(&proba, strong, medium, weak);
  /* MARKOVIAN TREE GENERATION */		

  /* ARPEGGIOS */
  int arpN = rand() % 3 + 4;
  Pattern					*markovPattern = new Pattern(chord);
  ObjectMarkov				       	markovObj2(proba, arpN++, parameters.getSeed());
  markovObj2.callLua();
  markovTmp = markovObj2.getVectorFromJson();
  Resolution::parsingMarkov(&markovTmp, strong, medium, weak);
  char						n;
  n = -1;
  while (++n != static_cast<char>(markovTmp.size()))
    markovPattern->addNote(std::make_pair(markovTmp[n].first, static_cast<char>(5)), n*3.0/arpN + 1, n*3.0/arpN, 0);
  std::vector<std::vector<t_note> >		arpeggios;
  std::vector<std::vector<t_note> >		tmparpeggios;
  n = -1;
  while (++n != static_cast<char>(markovChords.size()))
    {
      tmparpeggios = markovPattern->correlatePattern(*markovPattern, chord, allChords.getChordPairFromName(markovChords[n].first));
      arpeggios.insert(arpeggios.end(), tmparpeggios.begin(), tmparpeggios.end());
    }
  Disposition::placeArpeggios(parameters, arpeggios);
  /* ARPEGGIOS */

  /* END */
  parameters.setMidi(parameters._midiManager.createMidi(48));
  parameters._midiManager.writeToFile("./test.mid");
  return (Midi());
  /* ED*/
}
