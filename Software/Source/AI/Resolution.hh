#ifndef		__RESOLUTION__
# define	__RESOLUTION__

#include	"StyleSettings.hh"
#include	"Chords.hh"

# define	NOT_ENOUGH_CHANCE	5
# define	PROBASTRONG		50
# define	PROBAMEDIUM		33
# define	PROBAWEAK		17

class		Resolution
{
public:
  Resolution();
  ~Resolution();
  static void	parsingMarkov(StyleSettings &style, std::vector<std::pair<char, char> > *sequence);
  static void	parsingMarkov(std::vector<std::pair<char, char> > *sequence, const std::vector<char> &strong, const std::vector<char> &medium, const std::vector<char> &weak);
private:
  static char	fixingMarkov(StyleSettings &style, const char prev, const char next);
  static char	which_state(const char note, const std::vector<char> &strong, const std::vector<char> &medium);
  static char	fixingMarkov(const char state, const std::vector<char> &strong, const std::vector<char> &medium, const std::vector<char> &weak);
};

#endif //	__RESOLUTION__
