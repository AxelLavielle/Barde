#include		"AI.hh"

char			AI::calculateDist(const char currNote, const char testNote)
{
  char			a;

  a = ABS(testNote / 8 - currNote / 8);
  return (a < 6 ? a : (12 - a));
}

char			AI::calculateDistChords(const std::vector<std::pair<char, char> > chord, const char note)
{
  unsigned char		i;
  char			save;

  i = 255;
  save = 6;
  while (++i != chord.size())
    if (calculateDist(note, chord[i].first) < save)
      save = calculateDist(note, chord[i].first);
  return (save);
}

char			AI::calculateSumDist(const char currNote, const std::vector<char> &listNote)
{
  unsigned char		i;
  char			save;

  save = 0;
  i = 255;
  while (++i != listNote.size())
    save += calculateDist(listNote[i], currNote);
  return (save);
}

void			AI::calculateProbaToNoteFromNote(const char note, StyleSettings *proba, const std::vector<char> &listNote, const char probaNote)
{
  unsigned char		i;
  char			sumDist;
  unsigned int	nbNote;
  char			sumProba;

  i = 255;
  sumDist = calculateSumDist(i, listNote);
  nbNote = listNote.size();
  while (++i != listNote.size())
    if (note == listNote[i])
      nbNote--;
  i = 255;
  sumProba = 0;
  while (++i != listNote.size())
    {
      if (note == listNote[i])
	proba->addNoteFromNote(note, listNote[i], static_cast<char>(static_cast<float>(probaNote) / listNote.size()));
      else
	proba->addNoteFromNote(note, listNote[i], static_cast<char>((static_cast<float>(probaNote) / listNote.size()) * (((static_cast<float>(calculateDist(i, listNote[i])) / (static_cast<float>(sumDist) / nbNote)) + DISTIMPACT) / (DISTIMPACT + 1))));
      sumProba += static_cast<char>(proba->getProbaFromNote(note, listNote[i]));
    }
  while (sumProba != probaNote)
    {
      i = 255;
      while (sumProba != probaNote && ++i != listNote.size())
	{
	  proba->addNoteFromNote(note, listNote[i], proba->getProbaFromNote(note, listNote[i]) + 1);
	  sumProba++;
	}
    }
}

void			AI::calculateProbaToScaleFromNote(StyleSettings *proba, const std::vector<char> &strong, const std::vector<char> &medium, const std::vector<char> &weak)
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

void			AI::calculateProbaToNote(StyleSettings *proba, const std::vector<char> &listNote, const char probaNote)
{
  unsigned char		i;
  char			sumProba;

  i = 255;
  sumProba = 0;
  while (++i != listNote.size())
    {
      proba->addNote(listNote[i], probaNote / listNote.size());
      sumProba += static_cast<char>(probaNote / listNote.size());
    }
  while (sumProba != probaNote)
    {
      i = 255;
      while (sumProba != probaNote && ++i != listNote.size())
  	{
  	  proba->addNote(listNote[i], proba->getProba(listNote[i]) + 1);
  	  sumProba++;
  	}
    }
}

void			AI::classifyNotes(const std::vector<std::pair<char, char> > &chord, std::vector<char> *strong, std::vector<char> *medium, std::vector<char> *weak)
{
  unsigned char		i;
  char			save;

  save = -1;
  i = chord[0].first;
  while (save == -1 || i != chord[0].first)
    {
      save = calculateDistChords(chord, i);
      if (!save)
	strong->push_back(i);
      else if (save != 1)
	medium->push_back(i);
      else
	weak->push_back(i);
      i += 8;
      if (i == END)
	i = C;
    }
}

char			AI::searchNoteFromDist(char note, char dist)
{
  int noteret = note + dist * 8;
  if (noteret >= END)
    noteret -= END;
  return ((char)noteret);
}
