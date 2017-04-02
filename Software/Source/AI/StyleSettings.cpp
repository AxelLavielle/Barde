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

void		StyleSettings::addNote(const std::pair<char, int> &note)
{
  std::map<char, int>			tmp;

  if (_param.find(note.first) == _param.end())
    _param.insert(std::make_pair(note.first, std::make_pair(note.second, tmp)));
  else
    _param[note.first].first = note.second;
}

void		StyleSettings::addNote(const char noteName, const int noteProba)
{
  std::map<char, int>	tmp;

  if (_param.find(noteName) == _param.end())
    _param.insert(std::make_pair(noteName, std::make_pair(noteProba, tmp)));
  else
    _param[noteName].first = noteProba;
}

void		StyleSettings::addNoteFromNote(const char baseNote, const std::pair<char, int> &note)
{ 
  if (_param[baseNote].second.find(note.first) == _param[baseNote].second.end())
    _param[baseNote].second.insert(note);
  else
    _param[baseNote].second[note.first] = note.second;
}

void		StyleSettings::addNoteFromNote(const char baseNote, const char noteName, const int noteProba)
{
  if (_param[baseNote].second.find(noteName) == _param[baseNote].second.end())
    _param[baseNote].second.insert(std::make_pair(noteName, noteProba));
  else
    _param[baseNote].second[noteName] = noteProba;
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

std::map<char, std::pair<int, std::map<char, int> > >	StyleSettings::getParam() const
{
  return (_param);
}

StyleSettings	&StyleSettings::operator=(const StyleSettings &old)
{
  _param = old.getParam();
  return (*this);
}
