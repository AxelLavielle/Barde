#include	"StyleSettings.hh"

StyleSettings::StyleSettings()
{

}

StyleSettings::StyleSettings(const StyleSettings &old)
{
  _param = old.getParam();
}

StyleSettings::~StyleSettings()
{

}

void		StyleSettings::addNote(std::pair<char, int> note)
{
  std::map<char, int>			tmp;
  _param.insert(std::pair<int, std::pair<int, std::map<char, int> > >(note.first, std::pair<int, std::map<char, int> >(note.second, tmp)));
}

void		StyleSettings::addNote(char noteName, int noteProba)
{
  std::map<char, int>	tmp;
  _param.insert(std::pair<char, std::pair<int, std::map<char, int> > >(noteName, std::pair<int, std::map<char, int> >(noteProba, tmp)));
}

void		StyleSettings::addNoteFromNote(char baseNote, std::pair<char, int> note)
{
  _param[baseNote].second.insert(note);
}

void		StyleSettings::addNoteFromNote(char baseNote, char noteName, int noteProba)
{
  _param[baseNote].second.insert(std::pair<char, int>(noteName, noteProba));
}

int		StyleSettings::getProba(char note)
{
  return (_param.find(note) == _param.end() ? 0 : _param[note].first);
}

int		StyleSettings::getProbaFromNote(char baseNote, char note)
{
  return ((_param.find(baseNote) == _param.end() ||
	   _param[baseNote].second.find(note) == _param[baseNote].second.end()) ?
	  0 : _param[baseNote].second[note]);
}

std::map<char, std::pair<int, std::map<char, int> > >	StyleSettings::getParam() const
{
  return (_param);
}

StyleSettings	&StyleSettings::operator=(const StyleSettings &old)
{
  _param = old.getParam();
  return (*this);
}
