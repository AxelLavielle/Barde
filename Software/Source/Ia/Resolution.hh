#ifndef		__RESOLUTION__
# define	__RESOLUTION__

#include	<time.h>
#include	<stdlib.h>
#include	"StyleSettings.hh"
#include	"Chords.hh"

# define	NOT_ENOUGH_CHANCE	25

class		Resolution
{
public:
  Resolution();
  ~Resolution();
  void			setStyleSettings(const StyleSettings &style);
  std::vector<std::pair<char, char> >	parsingMarkov(std::vector<std::pair<char, char> > sequence);
  char			fixingMarkov(const char prev, const char next);
  void			addBridge();
  void			parsingDisposition();
  void			fixingDisposition();

private:
  StyleSettings		_style;
};

#endif //	__RESOLUTION__
