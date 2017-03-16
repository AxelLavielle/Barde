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

char			MusicGenerator::calculateDist(char currNote, char testNote)
{
  char			a;

  a = ABS(testNote / 8 - currNote / 8 - 1);
  return (a < 6 ? a : (12 - a));
}

char			MusicGenerator::calculateDistChords(std::vector<char> chord, char note)
{
  char			i;
  char			save;

  i = -1;
  save = 6;
  while (++i != chord.size())
    if (calculateDist(note, chord[i]) < save)
      save = calculateDist(note, chord[i]);
  return (save);
}

char			MusicGenerator::calculateSumDist(char currNote, std::vector<char> listNote)
{
  int			i;
  char			save;

  save = 0;
  i = -1;
  while (++i != listNote.size())
    save += calculateDist(listNote[i], currNote);
  return (save);
}

void			MusicGenerator::calculateProbaToNoteFromNote(StyleSettings *proba, std::vector<char> listNote, char probaNote)
{
  char			i;
  char			sumDist;

  i = -1;
  sumDist = calculateSumDist(i, listNote);
  while (++i != listNote.size())
    {
      proba->addNoteFromNote(i, listNote[i], (probaNote / listNote.size()) * ((((1 - (calculateDist(i, listNote[i]) / sumDist)) + 1) + DISTIMPACT) / (DISTIMPACT + 1)));
    }
}

void			MusicGenerator::calculateProbaToScaleFromNote(StyleSettings *proba, std::vector<char> chord, std::vector<char> strong, std::vector<char> medium, std::vector<char> weak)
{
  int			i;

  i = C;
  while (i + 1 != END)
    {
      //Gérer les strong / medium / weak en fonction de la note courrante
      calculateProbaToNoteFromNote(proba, strong, PROBASTRONG);
      calculateProbaToNoteFromNote(proba, medium, PROBAMEDIUM);
      calculateProbaToNoteFromNote(proba, weak, PROBAWEAK);
      i += 8;
    }
}

void			MusicGenerator::calculateProbaToNote(StyleSettings *proba, std::vector<char> listNote, char probaNote)
{
  int			i;

  i = -1;
  while (++i != listNote.size())
    proba->addNote(listNote[i], probaNote / listNote.size());
}

void			MusicGenerator::classifyNotes(std::vector<char> chord, std::vector<char> *strong, std::vector<char> *medium, std::vector<char> *weak)
{
  char			i;
  char			save;

  i = C;
  while (i + 1 != END)
    {
      save = calculateDistChords(chord, i);
      if (!save)
	strong->push_back(chord[i]);
      else if (save != 1)
	medium->push_back(chord[i]);
      else
	weak->push_back(chord[i]);
      i += 8;
    }
}

Midi			MusicGenerator::createMusic(MusicParameters &parameters)
{
  parameters.setSeed(std::time(NULL));
  srand(parameters.getSeed());
  ObjectMarkov						markovObj("blues.json", 1, parameters.getSeed());
  int							i;
  std::vector<std::pair<char, char> >			markovChords;
  std::vector<std::pair<char, char> >			markovArpeggio;
  StyleSettings						style;
  std::vector<char>					chord;
  Chords						allChords;

  std::cout << "-----------------------------------------------" << std::endl;
  
  markovObj.callLuaFromFile();
  markovChords = markovObj.getVectorFromJson();
  style = markovObj.getStyleFromJson();
  Resolution::parsingMarkov(style, markovChords);

  //Disposition::placeChords(parameters);

  i = 0;
  while (i != markovChords.size())
    {
      StyleSettings					proba;
      std::vector<char>					strong;
      std::vector<char>					medium;
      std::vector<char>					weak;

      chord = allChords.getChordFromName(markovChords[i].first);
      classifyNotes(chord, &strong, &medium, &weak);
      calculateProbaToNote(&proba, strong, PROBASTRONG);
      calculateProbaToNote(&proba, medium, PROBAMEDIUM);
      calculateProbaToNote(&proba, weak, PROBAWEAK);
      calculateProbaToScaleFromNote(&proba, chord, strong, medium, weak);

      //lua
      //cat les vectors
      i++;
    }

  //Disposition::placeArpeggios(parameters);
  
  std::cout << "-----------------------------------------------" << std::endl;

  return (Midi());
}
