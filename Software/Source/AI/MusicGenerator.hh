/*
  ==============================================================================

    MusicGenerator.h
    Created: 13 Mar 2017 1:46:35pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef MUSICGENERATOR_HH_INCLUDED
# define MUSICGENERATOR_HH_INCLUDED

# define ABS(x) ((x) > 0 ? (x) : (-(x)))
# define DISTIMPACT	1

# include "Resolution.hh"
# include "../MidiManager/Midi.hh"
# include "../MusicParameters.hh"
# include "ObjectMarkov.hh"
# include "Disposition.hh"
# include "Chords.hh"

class			MusicGenerator
{
public:
  MusicGenerator();
  ~MusicGenerator();
  Midi			createMusic(MusicParameters &parameters);

private:
  void			calculateProbaToScaleFromNote(StyleSettings *proba, const std::vector<char> &strong, const std::vector<char> &medium, const std::vector<char> &weak);
  void			calculateProbaToNoteFromNote(const char note, StyleSettings *proba, const std::vector<char> &listNote, const char probaNote);
  void			calculateProbaToNote(StyleSettings *proba, const std::vector<char> &listNote, const char probaNote);
  void			classifyNotes(const std::vector<char> &chord, std::vector<char> *strong, std::vector<char> *medium, std::vector<char> *weak);

  char			searchNoteFromDist(char note, char dist);
  char			calculateDist(const char currNote, const char testNote);
  char			calculateSumDist(const char currNote, const std::vector<char> &listNote);
  char			calculateDistChords(const std::vector<char> chord, const char note);
};

#endif  // MUSICGENERATOR_HH_INCLUDED
