#include	"StyleSettings.hh"

StyleSettings::StyleSettings()
{

}

StyleSettings::StyleSettings(StyleSettings &old)
{
  _param = old.getParam();
}

StyleSettings::~StyleSettings()
{

}

void		StyleSettings::addNote(const std::pair<char, int> &note)
{
  std::map<char, int>			tmp;
  _param.insert(std::make_pair(note.first, std::make_pair(note.second, tmp)));
}

void		StyleSettings::addNote(const char noteName, const int noteProba)
{
  std::map<char, int>	tmp;
  _param.insert(std::make_pair(noteName, std::make_pair(noteProba, tmp)));
}

void		StyleSettings::addNoteFromNote(const char baseNote, const std::pair<char, int> &note)
{
  _param[baseNote].second.insert(note);
}

void		StyleSettings::addNoteFromNote(const char baseNote, const char noteName, const int noteProba)
{
  _param[baseNote].second.insert(std::make_pair(noteName, noteProba));
}

int		StyleSettings::getProba(const char note)
{
  return (_param.find(note) == _param.end() ? 0 : _param[note].first);
}

int		StyleSettings::getProbaFromNote(const char baseNote, const char note)
{
  return ((_param.find(baseNote) == _param.end() ||
	   _param[baseNote].second.find(note) == _param[baseNote].second.end()) ?
	  0 : _param[baseNote].second[note]);
}

std::map<char, std::pair<int, std::map<char, int> > >	StyleSettings::getParam()
{
  return (_param);
}

StyleSettings	&StyleSettings::operator=(StyleSettings &old)
{
  _param = old.getParam();
  return (*this);
}
