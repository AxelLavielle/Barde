#ifndef DISPOSITION_HH
# define DISPOSITION_HH_

#include <vector>
#include "Chords.hh"
#include "Pattern.hh"
#include "../MusicParameters.hh"
#include "../MidiManager/MidiManager.hh"

/*!
 * \file Disposition.hh
 * \brief File containing the class designed to do harmonic disposition
 */

/*! Defines the amount of times per bar */
#define TIMES_PER_BAR 4

/*! \class Disposition
 * \brief Harmonic disposition
 *
 *  This class is here as a static class, all methods are statics in order to be called without an object creation
 *  This class is used after harmonic resolution and places chords and arpeggios on a musicsheet in order to create a song
 *
 */
class Disposition {
  public:
    /*!
     *  \brief Constructor
     *
     *  Empty
     *
     */
    Disposition();

    /*!
     *  \brief Destructor
     *
     *  Empty
     *
     */
    ~Disposition();

   /*!
     *  \brief Places chords into a MidiManager object stored into a MusicParameters object
     *
     *  This method directly modifies a MidiParameters object by placing chords into its MidiManager object
     *
     *  \param parameters : Parameters of the song to create
     *  \param chordsGrid : Chords to play
     *  \return Modifies the MidiManager contained into the MusicParameters object
     */
   static void	placeChords(MidiManager	&_midiManager, const MusicParameters &parameters, std::vector<std::pair<char, char> > chordsGrid);

   /*!
     *  \brief Places chords into a MidiManager object stored into a MusicParameters object
     *
     *  This method directly modifies a MidiParameters object by placing chords into its MidiManager object
     *
     *  \param parameters : Parameters of the song to create
     *  \param pattern : Chords pattern to play
     *  \return Modifies the MidiManager contained into the MusicParameters object
     */
   static void	placeChords(MidiManager	&_midiManager, const MusicParameters &parameters, std::vector<std::vector<t_note> > pattern);

   /*!
     *  \brief Places arpeggios into a MidiManager object stored into a MusicParameters object
     *
     *  This method directly modifies a MidiParameters object by placing arpeggios into its MidiManager object
     *
     *  \param parameters : Parameters of the song to create
     *  \param notesList : Arpeggios to play
     *  \return Modifies the MidiManager contained into the MusicParameters object
     */
   static void	placeArpeggios(MidiManager &_midiManager, const MusicParameters &parameters, std::vector<std::pair<char, char> > notesList);

   /*!
     *  \brief Places arpeggios into a MidiManager object stored into a MusicParameters object
     *
     *  This method directly modifies a MidiParameters object by placing arpeggios into its MidiManager object
     *
     *  \param parameters : Parameters of the song to create
     *  \param pattern : Arpeggios pattern to play
     *  \return Modifies the MidiManager contained into the MusicParameters object
     */
   static void	placeArpeggios(MidiManager &_midiManager, const MusicParameters &parameters, std::vector<std::vector<t_note> > pattern);

   /*!
     *  \brief Places drums into a MidiManager object stored into a MusicParameters object
     *
     *  This method directly modifies a MidiParameters object by placing drums into its MidiManager object
     *
     *  \param parameters : Parameters of the song to create
     *  \param pattern : Drums pattern to play
     *  \return Modifies the MidiManager contained into the MusicParameters object
     */
   static void	placeDrums(MidiManager &_midiManager, const MusicParameters &parameters, std::vector<std::vector<t_note>> pattern, std::vector<Instrument> drumInstruments);
};

#endif // DISPOSITION_HH_
