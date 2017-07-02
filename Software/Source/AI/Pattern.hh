/*
  ==============================================================================

    Pattern.h
    Created: 13 Mar 2017 1:46:35pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef PATTERN_HH_INCLUDED
# define PATTERN_HH_INCLUDED

/*!
 * \file Pattern.hh
 * \brief File containing the class that represents a pattern
 */

# include		<vector>
# include		"Chord.hh"

typedef struct		s_note
{
  std::pair<char, char>	note;
  float			position;
  float			duration;
}			t_note;

/*! \class Pattern
 * \brief  Representation of a pattern
 *
 *  This class allows to represent a pattern of notes for mutiples time
 */

class			Pattern
{
public:
  /*!
   *  \brief Constructor
   *
   *  Empty
   *
   */
  Pattern(const Chord &chord);

  /*!
   *  \brief Destructor
   *
   *  Empty
   *
   */
  ~Pattern();
  void			addNote(const std::pair<char, char> &note, const float position, const float duration, const char time);
  void			addNote(const t_note &newNote, const char time);
  std::vector<t_note>	getPatternTime(const char time) const;
  Chord			getChord() const;
  
private:
  std::vector<std::vector<t_note> >	_pattern(4);
  Chord					_chord;
};

#endif  // PATTERN_HH_INCLUDED
