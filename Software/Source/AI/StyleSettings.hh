#ifndef		__STYLESETTINGS__
# define	__STYLESETTINGS__

# include	<map>
# include	<list>

class		StyleSettings
{
public:
  StyleSettings();
  StyleSettings(StyleSettings &old);
  ~StyleSettings();
  void		addNote(const char noteName, const int noteProba);
  void		addNoteFromNote(const char baseNote, const char noteName, const int noteProba);
  void		addNote(const std::pair<char, int> &note);
  void		addNoteFromNote(const char baseNote, const std::pair<char, int> &note);
  int		getProba(const char note);
  int		getProbaFromNote(const char baseNote, const char note);
  StyleSettings	&operator=(const StyleSettings &old);
  std::map<char, std::pair<int, std::map<char, int> > >	getParam() const;

private:
  std::map<char, std::pair<int, std::map<char, int> > >	_param;
};

#endif	//	__STYLESETTINGS__
