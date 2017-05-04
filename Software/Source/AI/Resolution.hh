#ifndef		__RESOLUTION__
# define	__RESOLUTION__

/*!
 * \file Resolution.hh
 * \brief File containing the class that resolve the markov chains
 */

#include	"StyleSettings.hh"
#include	"Chords.hh"

/*! Defines the minimum of probability to be resolved MUST be between 1 and 100 */
# define	NOT_ENOUGH_CHANCE	5

/*! \class Resolution
 * \brief Harmonic resolution for markov chains
 *
 *  This class is here as a static class, all methods are statics in order to be called without an object creation
 *  This class allows to verify and resolve the markov chains in order to regule the aleatory factors deeming they can be bad
 */

class		Resolution
{
public:
  /*!
   *  \brief Parses and modifies if necessary the markov chain from a probability tree
   *
   *  This method returns the markov chain resolved from a probability tree
   *
   *  \param StyleSettings : Probability Tree
   *  \param Sequence : Markov chain
   *  \return Modify directly the Sequence parameter if necessary
   */
  static void	parsingMarkov(StyleSettings &style, std::vector<std::pair<char, char> > *sequence);

  /*!
   *  \brief Parses and modifies if necessary the markov chain from strengthness of notes
   *
   *  This method modifies the markov chain resolved from strengthness of notes
   *
   *  \param StyleSettings : Probability Tree
   *  \param Sequence : Markov chain
   *  \return Modify directly the Sequence parameter if necessary
   */
  static void	parsingMarkov(std::vector<std::pair<char, char> > *sequence, const std::vector<char> &strong, const std::vector<char> &medium, const std::vector<char> &weak);

private:
  /*!
   *  \brief Modifies the markov chain from a probability tree
   *
   *  This method modifies the markov chain resolved from a probability tree
   *
   *  \param StyleSettings : Probability Tree
   *  \param Note1 : Previous note
   *  \param Note2 : Current note (to modify)
   *  \return The recalculated note from the probability tree
   */
  static char	fixingMarkov(StyleSettings &style, const char prev, const char next);

  /*!
   *  \brief Modifies the markov chain from strengthness of notes
   *
   *  This method modifies the markov chain resolved from strengthness of notes
   *
   *  \param State : state of the note you need to search
   *  \param Strong : Vector of strong notes
   *  \param Medium : Vector of medium notes
   *  \param Strong : Vector of weak notes
   *  \return The recalculated note from the vectors
   */
  static char	fixingMarkov(const char state, const std::vector<char> &strong, const std::vector<char> &medium, const std::vector<char> &weak);

  /*!
   *  \brief Returns the strengthness of the note
   *
   *  This method returns the strengthness of the note according to the list it is part of
   *
   *  \param Note : Note
   *  \param Strong : Vector of strong notes
   *  \param Medium : Vector of medium notes
   *  \return The state of the note
   */
  static char	which_state(const char note, const std::vector<char> &strong, const std::vector<char> &medium);
};

#endif //	__RESOLUTION__
