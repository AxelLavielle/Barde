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
  while (i != END)
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
  while (i != END)
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

char			MusicGenerator::searchNoteFromDist(char note, char dist)
{
  while (dist != 0)
    {
      if (note != B && note != E)
	note += 16;
      else
	note += 8;
      if (note == END)
	note = C;
      dist--;
    }
  return (note);
}

Midi			MusicGenerator::createMusic(MusicParameters &parameters)
{
  parameters.setSeed(std::time(NULL));
  parameters.setBpm(80); 
  Instrument instru;
  instru.name = "Piano";
  instru.nb = ACOUSTICGRANDPIANO;
  instru.channel = 1;
  instru.velocity = 1;
  parameters.addInstrument(instru);
  parameters.setStyleName("Blues");

  srand(parameters.getSeed());
  ObjectMarkov						markovObj("../../Source/markovSource/blues.json", 1, parameters.getSeed());
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

  markovChords.push_back(markovChords[0]);
  markovChords.push_back(markovChords[0]);
  markovChords.push_back(markovChords[0]);

  markovChords.push_back(std::make_pair(searchNoteFromDist(markovChords[0].first, 3), 3));
  markovChords.push_back(std::make_pair(searchNoteFromDist(markovChords[0].first, 3), 3));
  markovChords.push_back(markovChords[0]);
  markovChords.push_back(markovChords[0]);

  markovChords.push_back(std::make_pair(searchNoteFromDist(markovChords[0].first, 4), 3));
  markovChords.push_back(std::make_pair(searchNoteFromDist(markovChords[0].first, 3), 3));
  markovChords.push_back(markovChords[0]);
  markovChords.push_back(std::make_pair(searchNoteFromDist(markovChords[0].first, 4), 3));

  Resolution::parsingMarkov(style, &markovChords);

  std::cout << markovChords[0].first << std::endl;
  std::cout << markovChords.size() << std::endl;
  Disposition::placeChords(parameters, markovChords);

  i = 0;
  std::cout << "-----------------------------------------------" << std::endl;
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
