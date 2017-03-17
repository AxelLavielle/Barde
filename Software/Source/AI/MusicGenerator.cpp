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

  a = ABS(testNote / 8 - currNote / 8);
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

void			MusicGenerator::calculateProbaToNoteFromNote(char note, StyleSettings *proba, std::vector<char> listNote, char probaNote)
{
  char			i;
  char			sumDist;
  char			nbNote;
  char			sumProba;

  i = -1;
  sumDist = calculateSumDist(i, listNote);
  nbNote = listNote.size();
  while (++i != listNote.size())
    if (i == listNote[i])
      nbNote--;
  i = -1;
  sumProba = 0;
  while (++i != listNote.size())
    {
      if (i == listNote[i])
	proba->addNoteFromNote(note, listNote[i], (static_cast<float>(probaNote) / listNote.size()));
      else
	proba->addNoteFromNote(note, listNote[i], (static_cast<float>(probaNote) / listNote.size()) * (((static_cast<float>(calculateDist(i, listNote[i])) / (static_cast<float>(sumDist) / nbNote)) + DISTIMPACT) / (DISTIMPACT + 1)));
      sumProba += proba->getProbaFromNote(note, listNote[i]);
    }
  while (sumProba != probaNote)
    {
      i = -1;
      while (sumProba != probaNote && ++i != listNote.size())
	{
	  listNote[i] += 1;
	  sumProba++;
	}
    }
}

void			MusicGenerator::calculateProbaToScaleFromNote(StyleSettings *proba, std::vector<char> chord, std::vector<char> strong, std::vector<char> medium, std::vector<char> weak)
{
  char			i;
  char			j;

  i = C;
  while (i != END)
    {
      calculateProbaToNoteFromNote(i, proba, strong, PROBASTRONG);
      calculateProbaToNoteFromNote(i, proba, medium, PROBAMEDIUM);
      calculateProbaToNoteFromNote(i, proba, weak, PROBAWEAK);
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
	strong->push_back(i);
      else if (save != 1)
	medium->push_back(i);
      else
	weak->push_back(i);
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

  markovObj.callLua();
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

  Disposition::placeChords(parameters, markovChords);

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
      
      ObjectMarkov				       	markovObj(proba, 1, parameters.getSeed());
      
      markovChords = markovObj.getVectorFromJson();
      if (!markovArpeggio.size())
	markovArpeggio = markovChords;
      else
	markovArpeggio.insert(markovArpeggio.end(), markovChords.begin(), markovChords.end());
      i++;
    }

  // Disposition::placeArpeggios(parameters, markovArpeggio);

  return (Midi());
}
