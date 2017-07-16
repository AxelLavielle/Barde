/*
  ==============================================================================

    Pattern.cpp
    Created: 13 Mar 2017 1:46:35pm
    Author:  Anthony

  ==============================================================================
*/

#include "Pattern.hh"

Pattern::Pattern(const std::vector<char> &chord)
{
  _chord = chord;
}

Pattern::~Pattern()
{
}

void	Pattern::addNote(const std::pair<char, char> &note, const float position, const float duration, const char time)
{
  t_note newNote;

  newNote.note = note;
  newNote.position = position;
  newNote.duration = duration;
  _pattern[time].push_back(newNote);
}

void	Pattern::addNote(const t_note &newNote, const char time)
{
  _pattern[time].push_back(newNote);
}

std::vector<t_note>	Pattern::getPatternTime(const char time) const
{
  if (time < _pattern.size())
    return (_pattern[time]);
  return (NULL);
}

std::vector<char>	Pattern::getChord() const
{
  return (_chord);
}
