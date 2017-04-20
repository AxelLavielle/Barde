#ifndef __AI__
# define __AI__

# include "Chords.hh"
# include "StyleSettings.hh"
# include "Resolution.hh"

# define ABS(x) ((x) > 0 ? (x) : (-(x)))
# define DISTIMPACT	1

class			AI
{
public:
  static void		calculateProbaToScaleFromNote(StyleSettings *proba, const std::vector<char> &strong, const std::vector<char> &medium, const std::vector<char> &weak);
  static void		calculateProbaToNoteFromNote(const char note, StyleSettings *proba, const std::vector<char> &listNote, const char probaNote);
  static void		calculateProbaToNote(StyleSettings *proba, const std::vector<char> &listNote, const char probaNote);
  static void		classifyNotes(const std::vector<char> &chord, std::vector<char> *strong, std::vector<char> *medium, std::vector<char> *weak);
  static char		searchNoteFromDist(char note, char dist);
  static char		calculateDist(const char currNote, const char testNote);
  static char		calculateSumDist(const char currNote, const std::vector<char> &listNote);
  static char		calculateDistChords(const std::vector<char> chord, const char note);
private:
};

#endif  // __AI__
