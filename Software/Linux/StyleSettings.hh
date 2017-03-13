#ifndef		__STYLESETTINGS__
# define	__STYLESETTINGS__

# include	<map>
# include	<list>

class		StyleSettings
{
public:
  StyleSettings();
  StyleSettings(const StyleSettings &old);
  ~StyleSettings();
  void		addNote(char noteName, int noteProba);
  void		addNoteFromNote(char baseNote, char noteName, int noteProba);
  void		addNote(std::pair<char, int> note);
  void		addNoteFromNote(char baseNote, std::pair<char, int> note);
  int		getProba(char note);
  int		getProbaFromNote(char baseNote, char note);
  StyleSettings	&operator=(const StyleSettings &old);
  std::map<char, std::pair<int, std::map<char, int> > >	getParam() const;

private:
  std::map<char, std::pair<int, std::map<char, int> > >	_param;
};

#endif	//	__STYLESETTINGS__
