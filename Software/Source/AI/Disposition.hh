#ifndef DISPOSITION_HH
# define DISPOSITION_HH_

#include <vector>
#include "Chords.hh"
#include "../MusicParameters.hh"
#include "../MidiManager/MidiManager.hh"

#define TIME_PER_TS 4

class Disposition {
  public:
    Disposition();
    ~Disposition();

  static void	placeChords(MusicParameters &parameters, std::vector<std::pair<char, char> > chordsGrid);
  static void	placeArpeggios(MusicParameters &parameters, std::vector<std::pair<char, char> > notesList);
};

#endif // DISPOSITION_HH_
