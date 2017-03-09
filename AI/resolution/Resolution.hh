#ifndef		__RESOLUTION__
# define	__RESOLUTION__

#include	<iostream>
#include	<vector>
#include	<time.h>
#include	<stdlib.h>
#include	"StyleSettings.hh"

# define	NOT_ENOUGH_CHANCE	25

class		Resolution
{
public:
  Resolution(// MusicParameters &params, Disposition &disposition
	     );
  ~Resolution();
  void			setStyleSettings(StyleSettings style);
  std::vector<std::pair<char, char> >	parsingMarkov(std::vector<std::pair<char, char> > sequence);
  char			fixingMarkov(char prev, char next);
  void			addBridge();
  void			parsingDisposition();
  void			fixingDisposition();

private:
  StyleSettings		_style;
};

#endif //	__RESOLUTION__
