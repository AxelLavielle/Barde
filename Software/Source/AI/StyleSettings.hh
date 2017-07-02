#ifndef		__STYLESETTINGS__
# define	__STYLESETTINGS__

/*!
 * \file StyleSettings.hh
 * \brief File containing the class and enum to simplify the access of all possible datas in the probability tree
 */

# include	<map>
# include	<list>

/*! Sum of the probabilities of all the strong notes */
# define	PROBASTRONG		50
/*! Sum of the probabilities of all the medium notes */
# define	PROBAMEDIUM		33
/*! Sum of the probabilities of all the weak notes */
# define	PROBAWEAK		17

/*! \class StyleSettings
 * \brief Simplify the access to a probability tree
 *
 *  This class is here to allow a simple access to a probability tree
 */

class		StyleSettings
{
public:
  /*!
   *  \brief Constructor
   *
   *  Empty
   *
   */
  StyleSettings();

  /*!
   *  \brief Constructor
   *
   *  Copy Constructor
   *
   */
  StyleSettings(const StyleSettings &old);

  /*!
   *  \brief Destructor
   *
   *  Empty
   *
   */
  ~StyleSettings();

  /*!
   *  \brief Adds a note to the roots of the probability tree
   *
   *  This method adds a note to the roots of the probability tree
   *
   *  \param Name : Name of the note
   *  \param Proba : Probability of the note
   *  \return Directly modify self->param
   */
  void		addNote(const char noteName, const int noteProba);

  /*!
   *  \brief Adds a note to the branch of the probability tree from a note
   *
   *  This method adds a note to the branch of the probability tree from a note
   *
   *  \param Parent : Name of the parent note
   *  \param Name : Name of the note
   *  \param Proba : Probability of the note
   *  \return Directly modify self->param
   */
  void		addNoteFromNote(const char baseNote, const char noteName, const int noteProba);

  /*!
   *  \brief Adds a note to the roots of the probability tree as pair
   *
   *  This method adds a note to the roots of the probability tree as pair
   *
   *  \param NameProba : Pair of Name of the note and Probability of the note
   *  \return Directly modify self->param
   */
  void		addNote(const std::pair<char, int> &note);

  /*!
   *  \brief Adds a note to the branch of the probability tree as pair from a note
   *
   *  This method adds a note to the branch of the probability tree as pair from a note
   *
   *  \param Parent : Name of the parent note
   *  \param NameProba : Pair of Name of the note and Probability of the note
   *  \return Directly modify self->param
   */
  void		addNoteFromNote(const char baseNote, const std::pair<char, int> &note);

  /*!
   *  \brief Returns the probability of the root note
   *
   *  This method returns the probability of the root note
   *
   *  \param Note : Name of the note
   *  \return The probability of the note
   */
  char		getProba(const char note);

  /*!
   *  \brief Returns the sum probability of the root notes
   *
   *  This method returns the sum of all the probability of the root notes
   *
   *  \param Note : Name of the note
   *  \return The probability of the note
   */
  char		getSumProba();

  /*!
   *  \brief Returns the probability of a note from another
   *
   *  This method returns the probability of the note
   *
   *  \param Parent : Name of the parent note
   *  \param Note : Name of the note
   *  \return The probability of the note
   */
  char		getProbaFromNote(const char baseNote, const char note);

  /*!
   *  \brief Returns the sum probability of notes from another
   *
   *  This method returns the sum of all the probability from a note
   *
   *  \param Note : Name of the note
   *  \return The probability of the note
   */
  char		getSumProbaFromNote(const char baseNote);

  /*!
   *  \brief Copies the object with overload
   *
   *  This method copies the object and transfer the probability tree
   *
   *  \param Old : old probability tree
   *  \return The new probability tree
   */
  StyleSettings	&operator=(const StyleSettings &old);

  /*!
   *  \brief Normalize the probabilites
   *
   *  This method normalize all the probabilites of the tree
   *
   *  \return None
   */
  void		normalize();

  /*!
   *  \brief Returns the probability tree as raw data
   *
   *  This method returns the probability tree as raw data
   *
   *  \return The probability tree as raw data
   */
  std::map<char, std::pair<int, std::map<char, int> > >	getParam() const;

private:
  std::map<char, std::pair<int, std::map<char, int> > >	_param; /*!< Probability tree */
};

#endif	//	__STYLESETTINGS__
