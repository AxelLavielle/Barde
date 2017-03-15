#ifndef		__RESOLUTION__
# define	__RESOLUTION__

#include	"StyleSettings.hh"
#include	"Chords.hh"

# define	NOT_ENOUGH_CHANCE	25

class		Resolution
{
public:
  Resolution();
  ~Resolution();
  static std::vector<std::pair<char, char> >	Resolution::parsingMarkov(const StyleSettings &style, std::vector<std::pair<char, char> > &sequence);
private:
  char			fixingMarkov(const char prev, const char next);
};

#endif //	__RESOLUTION__
