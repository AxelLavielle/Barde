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
  void			calculateProbaToScaleFromNote(StyleSettings *proba, std::vector<char> strong, std::vector<char> medium, std::vector<char> weak);
  void			calculateProbaToNoteFromNote(char note, StyleSettings *proba, std::vector<char> listNote, char probaNote);
  void			calculateProbaToNote(StyleSettings *proba, std::vector<char> listNote, char probaNote);
  void			classifyNotes(std::vector<char> chord, std::vector<char> *strong, std::vector<char> *medium, std::vector<char> *weak);

  char			searchNoteFromDist(char note, char dist);
  char			calculateDist(char currNote, char testNote);
  char			calculateSumDist(char currNote, std::vector<char> listNote);
  char			calculateDistChords(std::vector<char> chord, char note);
};

#endif  // MUSICGENERATOR_HH_INCLUDED
