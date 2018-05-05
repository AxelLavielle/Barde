/*
  ==============================================================================

    PatternGenerator.cpp
    Created: 13 Mar 2017 1:46:35pm
    Author:  Anthony

  ==============================================================================
*/

#include "PatternGenerator.hh"

PatternGenerator::PatternGenerator(const std::vector<std::pair<char, char> > &chord)
{
  _patternNumber = 0;
  _noteNumber = 0;
  _chord = chord;
}

PatternGenerator::~PatternGenerator()
{
  
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
/*	  note = Pattern::correlateNote(time[n], newPattern.getChord(), _chord);
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
	  count++;*/
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
    ret.addNote(vec[n], _position[(4 * n) / vec.size()], _duration[(4 * n) / vec.size()], static_cast<char>((4 * n) / vec.size())); /* DURATION ET POSITION A AMELIORER */
  return (ret);
}
