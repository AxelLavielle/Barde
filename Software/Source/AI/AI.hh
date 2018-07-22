#ifndef __AI__
# define __AI__

/*!
 * \file AI.hh
 * \brief File containing the class for mathematics used in our artificial intelligence
 */

# include "Chords.hh"
# include "StyleSettings.hh"
# include "Resolution.hh"

/*! Get the value of a number wthout his sign. */
# define ABS(x) ((x) > 0 ? (x) : (-(x)))
/*! Define the impact of the distance between two notes. */
# define DISTIMPACT	4

/*! \class AI
 * \brief Mathematics for artificial intelligence
 *
 *  This class is here as a static class, all methods are statics in order to be called without an object creation
 *  This class allows to do complexes mathematicals algorithms with a few calls and the algorithm are specific for a music project
 */

class			AI
{
public:

  /*!
   *  \brief Calculates the probability to scale from note
   *
   *  This method calculates the probability of a whole scale (12 notes) to happen from a note
   *
   *  \param StyleSettings : Probability tree
   *  \param Strong : Vector of strong notes
   *  \param Medium : Vector of medium notes
   *  \param Weak : Vector of weak notes
   *  \return Insert the probabilites directly in the StyleSettings that you must provide as parameters
   */
  static void		calculateProbaToScaleFromNote(StyleSettings *proba, const std::vector<char> &strong, const std::vector<char> &medium, const std::vector<char> &weak);

  /*!
   *  \brief Calculates the probability to note from note
   *
   *  This method calculates the probability of a note's list to happen from another note
   *
   *  \param Note : Current Markov save
   *  \param StyleSettings : Probability tree
   *  \param NoteList : Note's list you want to test the probability to happen from Note
   *  \param Proba : Probability that one of the element of the list happen
   *  \return Insert the probabilites directly in the StyleSettings that you must provide as parameters
   */
  static void		calculateProbaToNoteFromNote(const char note, StyleSettings *proba, const std::vector<char> &listNote, const char probaNote);

  /*!
   *  \brief Calculates the probability of a note to happen when at the root of the markov tree
    *
   *  This method calculates the probability of a note to happen from the root of the markov tree
   *
   *  \param StyleSettings : Probability tree
   *  \param NoteList : Note's list you want to test the probability to happen from Note
   *  \param Proba : Probability that one of the element of the list happen
   *  \return Insert the probabilites directly in the StyleSettings that you must provide as parameters
   */
  static void		calculateProbaToNote(StyleSettings *proba, const std::vector<char> &listNote, const char probaNote);

  /*!
   *  \brief Classifies the notes of a scale as strong, medium or weak from a chord
   *
   *  This method classifies the notes of a scale as strong, medium or weak from a chord
   *
   *  \param Chord : Vector of notes from the chord
   *  \param Strong : Vector of strong notes
   *  \param Medium : Vector of medium notes
   *  \param Weak : Vector of weak notes
   *  \return Insert the notes directly in the correct vector that you must provide as parameters
   */
  static void		classifyNotes(const std::vector<std::pair<char, char> > &chord, std::vector<char> *strong, std::vector<char> *medium, std::vector<char> *weak);

  /*!
   *  \brief Searches the note name from a distance and a note
   *
   *  This method searches and returns the note from a distance and a note
   *
   *  \param Note : Note you start from
   *  \param Distance : Distance you want to access the note
   *  \return The found note
   */
  static char		searchNoteFromDist(char note, char dist);

  /*!
   *  \brief Calculates the distance between two notes
   *
   *  This method calculates the distance between two notes, not taking care of the direction you're searching
   *
   *  \param Note1 : Note one
   *  \param Note2 : Note two
   *  \return The distance between the two notes
   */
  static char		calculateDist(const char currNote, const char testNote);

  /*!
   *  \brief Calculates the sum of distance between the note and every note of the list
   *
   *  This method calculates the sum of distance between the note and every note of the list, not taking care of the direction you're searching
   *
   *  \param Note : Note one
   *  \param NoteList : Vector of note
   *  \return The sum of distance between the note and every note of the list
   */
  static char		calculateSumDist(const char currNote, const std::vector<char> &listNote);

  /*!
   *  \brief Calculates the minimum distance between the note and every note of a chord
   *
   *  This method calculates the minimum distance between the note and every note of the chord, not taking care of the direction you're searching
   *
   *  \param Note : Note one
   *  \param Chord : Vector of note
   *  \return The minimum of distance between the note and every note of the list
   */
  static char		calculateDistChords(const std::vector<std::pair<char, char> > chord, const char note);
private:
};

#endif  // __AI__
