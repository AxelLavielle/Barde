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

char			MusicGenerator::calculateDist(const char currNote, const char testNote)
{
  char			a;

  a = ABS(testNote / 8 - currNote / 8);
  return (a < 6 ? a : (12 - a));
}

char			MusicGenerator::calculateDistChords(const std::vector<char> chord, const char note)
{
  unsigned char		i;
  char			save;

  i = -1;
  save = 6;
  while (++i != chord.size())
    if (calculateDist(note, chord[i]) < save)
      save = calculateDist(note, chord[i]);
  return (save);
}

char			MusicGenerator::calculateSumDist(const char currNote, const std::vector<char> &listNote)
{
  unsigned char		i;
  char			save;

  save = 0;
  i = -1;
  while (++i != listNote.size())
    save += calculateDist(listNote[i], currNote);
  return (save);
}

void			MusicGenerator::calculateProbaToNoteFromNote(const char note, StyleSettings *proba, const std::vector<char> &listNote, const char probaNote)
{
  unsigned char		i;
  char			sumDist;
  char			nbNote;
  char			sumProba;

  i = -1;
  sumDist = calculateSumDist(i, listNote);
  nbNote = listNote.size();
  while (++i != listNote.size())
    if (note == listNote[i])
      nbNote--;
  i = -1;
  sumProba = 0;
  while (++i != listNote.size())
    {
      if (note == listNote[i])
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
	  proba->addNoteFromNote(note, listNote[i], proba->getProbaFromNote(note, listNote[i]) + 1);
	  sumProba++;
	}
    }
}

void			MusicGenerator::calculateProbaToScaleFromNote(StyleSettings *proba, const std::vector<char> &strong, const std::vector<char> &medium, const std::vector<char> &weak)
{
  unsigned char		i;

  i = C;
  while (i != END)
    {
      calculateProbaToNoteFromNote(i, proba, strong, PROBASTRONG);
      calculateProbaToNoteFromNote(i, proba, medium, PROBAMEDIUM);
      calculateProbaToNoteFromNote(i, proba, weak, PROBAWEAK);
      i += 8;
    }
}

void			MusicGenerator::calculateProbaToNote(StyleSettings *proba, const std::vector<char> &listNote, const char probaNote)
{
  unsigned char		i;
  char			sumProba;

  i = -1;
  sumProba = 0;
  while (++i != listNote.size())
    {
      proba->addNote(listNote[i], probaNote / listNote.size());
      sumProba += probaNote / listNote.size();
    }
  while (sumProba != probaNote)
    {
      i = -1;
      while (sumProba != probaNote && ++i != listNote.size())
  	{
  	  proba->addNote(listNote[i], proba->getProba(listNote[i]) + 1);
  	  sumProba++;
  	}
    }
}

void			MusicGenerator::classifyNotes(const std::vector<char> &chord, std::vector<char> *strong, std::vector<char> *medium, std::vector<char> *weak)
{
  unsigned char		i;
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
  instru.velocity = 100; //Need change
  parameters.addInstrument(instru);
  parameters.setStyleName("Blues");

  srand(parameters.getSeed());
  #ifdef _WIN32
  ObjectMarkov						markovObj("../Source/markovSource/blues.json", 1, parameters.getSeed());
  #else
  ObjectMarkov						markovObj("../../Source/markovSource/blues.json", 1, parameters.getSeed());
  #endif

  unsigned char						i;
  std::vector<std::pair<char, char> >			markovChords;
  std::vector<std::pair<char, char> >			markovTmp;
  std::vector<std::pair<char, char> >			markovArpeggio;
  StyleSettings						style;
  std::vector<char>					chord;
  Chords						allChords;

  markovObj.callLua();
  markovChords = markovObj.getVectorFromJson();

  style = markovObj.getStyleFromJson();

  Resolution::parsingMarkov(style, &markovChords);

  markovChords.push_back(markovChords[0]);
  markovChords.push_back(markovChords[0]);
  markovChords.push_back(markovChords[0]);

  markovChords.push_back(std::make_pair(searchNoteFromDist((markovChords[0].first / 8 * 8), 3) + markovChords[0].first % 8, 4));
  markovChords.push_back(std::make_pair(searchNoteFromDist((markovChords[0].first / 8 * 8), 3) + markovChords[0].first % 8, 4));
  markovChords.push_back(markovChords[0]);
  markovChords.push_back(markovChords[0]);

  markovChords.push_back(std::make_pair(searchNoteFromDist((markovChords[0].first / 8 * 8), 4) + markovChords[0].first % 8, 4));
  markovChords.push_back(std::make_pair(searchNoteFromDist((markovChords[0].first / 8 * 8), 3) + markovChords[0].first % 8, 4));
  markovChords.push_back(markovChords[0]);
  markovChords.push_back(std::make_pair(searchNoteFromDist((markovChords[0].first / 8 * 8), 4) + markovChords[0].first % 8, 4));

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
      calculateProbaToScaleFromNote(&proba, strong, medium, weak);

      ObjectMarkov				       	markovObj(proba, 3, parameters.getSeed());
      markovObj.callLua();

      markovTmp = markovObj.getVectorFromJson();
      Resolution::parsingMarkov(&markovTmp, strong, medium, weak);
      if (!markovArpeggio.size())
	markovArpeggio = markovTmp;
      else
	markovArpeggio.insert(markovArpeggio.end(), markovTmp.begin(), markovTmp.end());
      i++;
    }

  Disposition::placeArpeggios(parameters, markovArpeggio);

  parameters.setMidi(parameters._midiManager.createMidi(48));
  parameters._midiManager.writeToFile("./test.mid");

  return (Midi());
}
