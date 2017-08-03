/*
  ==============================================================================

    PatternGenerator.h
    Created: 13 Mar 2017 1:46:35pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef PATTERNGENERATOR_HH_INCLUDED
# define PATTERNGENERATOR_HH_INCLUDED

/*!
 * \file PatternGenerator.hh
 * \brief File containing the class that creates pattern using synthesis of other patterns
 */

# include		"Pattern.hh"
# include		"ObjectMarkov.hh"

/*! \class PatternGenerator
 * \brief Generator handling all the creation process of pattern
 *
 *  This class allows to create patterns of music, synthesizing differents patterns and then using Markov Chains
 */

class			PatternGenerator
{
public:
  /*!
   *  \brief Constructor
   *
   *  Empty
   *
   */
  PatternGenerator();
  PatternGenerator(const std::vector<std::pair<char, char> > &chord);

  /*!
   *  \brief Destructor
   *
   *  Empty
   *
   */
  ~PatternGenerator();
  void	addPattern(const Pattern &newPattern);
  Pattern	getPattern() const;
private:
  t_note	correlateNote(const t_note &note, const std::vector<std::pair<char, char> > &prev, const std::vector<std::pair<char, char> > &next);
  char		_patternNumber;
  StyleSettings	_tree;
  std::vector<std::pair<char, char> >	_chord;
  std::vector<float> _position;
  std::vector<float> _duration;
  float		_noteNumber;
};

#endif  // PATTERNGENERATOR_HH_INCLUDED
