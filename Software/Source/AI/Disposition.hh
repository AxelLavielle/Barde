#include <vector>
#include "../MusicParameters.hh"

class Disposition {
  public:
    Disposition();
    ~Disposition();

  static void	placeChords(MusicParameters &parameters);
  static void	placeArpeggios(MusicParameters &parameters);
};
