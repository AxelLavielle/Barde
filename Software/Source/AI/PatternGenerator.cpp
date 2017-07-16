/*
  ==============================================================================

    PatternGenerator.cpp
    Created: 13 Mar 2017 1:46:35pm
    Author:  Anthony

  ==============================================================================
*/

#include "PatternGenerator.hh"

PatternGenerator::PatternGenerator(const std::vector<char> &chord)
{
  _patternNumber = 0;
  _noteNumber = 0;
  _chord = chord;
}

PatternGenerator::~PatternGenerator()
{
  
}

t_note	PatternGenerator::correlateNote(const t_note &note, const std::vector<char> &prev, const std::vector<char> &next)
{
  t_note		ret;
  std::vector<char>	strong;
  std::vector<char>	medium;
  std::vector<char>	weak;
  std::vector<char>	strong2;
  std::vector<char>	medium2;
  std::vector<char>	weak2;
  char			i;

  ret.position = note.position;
  ret.duration = note.duration;
  AI::classifyNotes(prev, &strong, &medium, &weak);
  AI::classifyNotes(next, &strong2, &medium2, &weak2);
  
  // Normalize
  while (strong2.size() < strong.size())
    strong2.push_back(medium2.back());
  while (medium2.size() < medium.size())
    medium2.push_back(weak2.back());
  while (weak2.size() < weak.size())
    weak2.push_back(medium2[0]);

  // Search
  i = -1;
  while (static_cast<unsigned int>(++i) < strong.size())
    if (strong[i] == note.note.first)
      ret.note = std::make_pair(strong2[i], 3);
  i = -1;
  while (static_cast<unsigned int>(++i) < medium.size())
    if (medium[i] == note.note.first)
      ret.note = std::make_pair(medium2[i], 3);
  i = -1;
  while (static_cast<unsigned int>(++i) < weak.size())
    if (weak[i] == note.note.first)
      ret.note = std::make_pair(weak2[i], 3);
  return (ret);
}

void	PatternGenerator::addPattern(const Pattern &newPattern)
{
  char			n;
  t_note		note;
  t_note		oldNote;
  std::vector<t_note>	time;
  char			i;
  char			count;
  
  _patternNumber++;
  i = -1;
  count = 0;
  while ((time = newPattern.getPatternTime(++i)).size() > 0)
    {
      n = -1;
      while (static_cast<unsigned int>(++n) < time.size())
	{
	  note = correlateNote(time[n], newPattern.getChord(), _chord);
	  if (n == 0)
	    _tree.addNote(note.note.first, _tree.getProba(note.note.first) + 1);
	  else
	    _tree.addNoteFromNote(oldNote.note.first, note.note.first, _tree.getProbaFromNote(oldNote.note.first, note.note.first) + 1);
	  oldNote = note;

	  if (static_cast<unsigned int>(n) < _duration.size())
	    _duration[n] = (_duration[n] * ((_noteNumber + count) / 4) + note.duration) / ((_noteNumber + count) / 4 + 1);
	  else
	    _duration.push_back(note.duration);
	  if (static_cast<unsigned int>(n) < _position.size())
	    _position[n] = (_position[n] * ((_noteNumber + count) / 4) + note.position) / ((_noteNumber + count) / 4 + 1);
	  else
	    _position.push_back(note.position);
	  count++;
	}
    }
  _noteNumber = (_noteNumber * (_patternNumber - 1) + count) / _patternNumber;
}

Pattern		PatternGenerator::getPattern() const
{
  StyleSettings		toMarkov(_tree);
  std::vector<std::pair<char, char> > vec;
  int			n;
  Pattern		ret(_chord);

  toMarkov.normalize();
  ObjectMarkov markov(toMarkov, static_cast<int>(_noteNumber)); /* NOTE NUMBER A AMELIORER */
  markov.callLua();
  vec = markov.getVectorFromJson();

  n = -1;
  while (static_cast<unsigned int>(++n) != vec.size())
    ret.addNote(vec[n], _position[(4 * n) / vec.size()], _duration[(4 * n) / vec.size()], (4 * n) / vec.size()); /* DURATION ET POSITION A AMELIORER */
  return (ret);
}
