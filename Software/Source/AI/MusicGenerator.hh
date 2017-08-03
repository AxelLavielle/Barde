/*
  ==============================================================================

    MusicGenerator.h
    Created: 13 Mar 2017 1:46:35pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef MUSICGENERATOR_HH_INCLUDED
# define MUSICGENERATOR_HH_INCLUDED

/*!
 * \file MusicGenerator.hh
 * \brief File containing the class that connects all part of our artificial intelligence
 */

# include "Resolution.hh"
# include "../MidiManager/Midi.hh"
# include "../MusicParameters.hh"
# include "ObjectMarkov.hh"
# include "Disposition.hh"
# include "Chords.hh"
# include "Pattern.hh"
# include "AI.hh"

/*! \class MusicGenerator
 * \brief Generator handling all the creation process
 *
 *  This class allows to create music, connecting the different part of the artificial intelligence
 */

class			MusicGenerator
{
public:
  /*!
   *  \brief Constructor
   *
   *  Empty
   *
   */
  MusicGenerator();

  /*!
   *  \brief Destructor
   *
   *  Empty
   *
   */
  ~MusicGenerator();

  /*!
   *  \brief Launches and merges all the artificial intelligence part
   *
   *  This method connects all the different part of the artificial intelligence
   *
   *  \param Settings : Settings of the music as MusicParameters
   *  \return Midi file containing the music
   */
  Midi			createMusic(MusicParameters &parameters);

private:
};

#endif  // MUSICGENERATOR_HH_INCLUDED
