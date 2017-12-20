/*
  ==============================================================================

    Pattern.cpp
    Created: 13 Mar 2017 1:46:35pm
    Author:  Anthony

  ==============================================================================
*/

#include "Pattern.hh"

Pattern::Pattern(const std::vector<std::pair<char, char> > &chord)
{
  _chord = chord;
}

Pattern::~Pattern()
{
}

t_note	Pattern::correlateNote(const t_note &note, const std::vector<std::pair<char, char> > &prev, const std::vector<std::pair<char, char> > &next,
								const std::vector<char> &strong, const std::vector<char> &medium, const std::vector<char> &weak,
								const std::vector<char> &strong2, const std::vector<char> &medium2, const std::vector<char> &weak2)
{
  t_note		ret;
  char			i;

  ret.position = note.position;
  ret.duration = note.duration;

  // Search
  i = -1;
  while (static_cast<unsigned int>(++i) < strong.size())
    if (strong[i] == note.note.first)
      ret.note = std::make_pair(strong2[i], (next[0].first <= strong2[i]) ? (note.note.second) : (note.note.second + 1));
  i = -1;
  while (static_cast<unsigned int>(++i) < medium.size())
    if (medium[i] == note.note.first)
      ret.note = std::make_pair(medium2[i], (next[0].first <= medium2[i]) ? (note.note.second) : (note.note.second + 1));
  i = -1;
  while (static_cast<unsigned int>(++i) < weak.size())
    if (weak[i] == note.note.first)
      ret.note = std::make_pair(weak2[i], (next[0].first <= weak2[i]) ? (note.note.second) : (note.note.second + 1));
  return (ret);
}

std::vector<std::vector<t_note> >	Pattern::correlatePattern(const Pattern pattern, const std::vector<std::pair<char, char> > &prev, const std::vector<std::pair<char, char> > &next)
{
  std::vector<std::vector<t_note> >	_pattern = pattern.getPattern();
  unsigned int						i;
  unsigned int						j;
  std::vector<char>					strong;
  std::vector<char>					medium;
  std::vector<char>					weak;
  std::vector<char>					strong2;
  std::vector<char>					medium2;
  std::vector<char>					weak2;

  AI::classifyNotes(prev, &strong, &medium, &weak);
  AI::classifyNotes(next, &strong2, &medium2, &weak2);

  // Normalize
  while (strong2.size() < strong.size())
	  strong2.push_back(medium2.back());
  while (medium2.size() < medium.size())
	  medium2.push_back(weak2.back());
  while (weak2.size() < weak.size())
	  weak2.push_back(medium2[0]);

  //prints
  std::cout << "### STARTING DEBUG FOR CORRELATE PATTERN ###" << std::endl;

  std::cout << "Chord 1:" << std::endl;
  std::cout << "Strong: ";
  i = -1;
  while (static_cast<unsigned int>(++i) < strong.size())
	  std::cout << strong[i] << " ";
  std::cout << std::endl << "Medium: ";
  i = -1;
  while (static_cast<unsigned int>(++i) < medium.size())
	  std::cout << medium[i] << " ";
  std::cout << std::endl << "Weak: ";
  i = -1;
  while (static_cast<unsigned int>(++i) < weak.size())
	  std::cout << weak[i] << " ";

  std::cout << "Chord 2:" << std::endl;
  std::cout << "Strong: ";
  i = -1;
  while (static_cast<unsigned int>(++i) < strong2.size())
	  std::cout << strong2[i] << " ";
  std::cout << std::endl << "Medium: ";
  i = -1;
  while (static_cast<unsigned int>(++i) < medium2.size())
	  std::cout << medium2[i] << " ";
  std::cout << std::endl << "Weak: ";
  i = -1;
  while (static_cast<unsigned int>(++i) < weak2.size())
	  std::cout << weak2[i] << " ";

  std::cout << "### ENDING DEBUG FOR CORRELATE PATTERN ###" << std::endl;
  i = -1;
  while (++i != _pattern.size())
    {
      j = -1;
      while (++j != _pattern[i].size())
    	  _pattern[i][j] = correlateNote(_pattern[i][j], prev, next, strong, medium, weak, strong2, medium2, weak2);
    }
//  exit(1);
  return (_pattern);
}

void	Pattern::addNote(const std::pair<char, char> &note, const float position, const float duration, const char time)
{
  t_note newNote;
  std::vector<t_note>	tmp;
  
  newNote.note = note;
  newNote.position = position;
  newNote.duration = duration;
  while (time >= static_cast<char>(_pattern.size()))
    _pattern.push_back(tmp);
  _pattern[time].push_back(newNote);
}

void	Pattern::addNote(const t_note &newNote, const char time)
{
  _pattern[time].push_back(newNote);
}

std::vector<t_note>	Pattern::getPatternTime(const char time) const
{
  std::vector<t_note>	empty;

  if (static_cast<unsigned int>(time) < _pattern.size())
    return (_pattern[time]);
  return (empty);
}

std::vector<std::vector<t_note> >	Pattern::getPattern() const
{
  return (_pattern);
}

std::vector<std::pair<char, char> >	Pattern::getChord() const
{
  return (_chord);
}
