/*
  ==============================================================================

    UserSettings.h
    Created: 28 May 2017 6:10:55pm
    Author:  Oreo

  ==============================================================================
*/

#ifndef USERSETTINGS_H_INCLUDED
#define USERSETTINGS_H_INCLUDED

#include "./GraphManager/Theme.h"
#include <vector>
#include "MusicParameters.hh"

/*! Language of the software */
enum Language {
	EN, /*!< English */
	FR /*!< French */
};


/*! \class UserSettings
* \brief class used for the differents user settings
*
*  Used to define the user preferences on :
*  - Volume
*  - BPM
*  - Mute the sound
*  - Language of the software
*/
class UserSettings
{
public:
	/*!
	*  \brief Constructor
	*
	*  Default construtor
	*
	*/
	UserSettings();

	/*!
	*  \brief Constructor
	*
	*  Constructor with only volume and BPM parameters
	*
	*  \param volume : volume of the software (pourcentage between 0 and 100)
	*  \param BPM : BRM of the sound.
	*/
	UserSettings(int volume);

	/*!
	*  \brief Constructor
	*
	*  Complete Constructor
	*
	*  \param mute : boolean to define if the sound needs to be muted.
	*  \param language : langage of the software.
	*  \param volume : volume of the software (pourcentage between 0 and 100)
	*  \param BPM : BRM of the sound.
	*/
	UserSettings(bool mute, Language language, int volume);


	UserSettings(MusicParameters *musicParameters);


	/*!
	*  \brief Destructor
	*
	*  UserSettings Destructor
	*
	*/
	~UserSettings();

	/*!
	*  \brief volume getter
	*
	*  gets the volume of the user has set
	*
	*  \return the volume (percentage between 0 and 100)
	*/
	int getVolume();


	/*!
	*  \brief BPM getter
	*
	*  gets the BPM of the user has set
	*
	*  \return the BPM (between 20 and 220)
	*/
	int getBPM();

	/*!
	*  \brief Mute getter
	*
	*  gets if the sound needs to be mute or not
	*
	*  \return true or false
	*/
	bool isMute();

	/*!
	*  \brief Language getter
	*
	*  gets the language of the user
	*
	*  \return Language see enum
	*/
	Language getLanguage();

	/*!
	*  \brief Volume Setter
	*
	*  sets the volume of the music
	*
	*  \param volume : volume of the software (pourcentage between 0 and 100)
	*/
	void setVolume(int volume);

	/*!
	*  \brief BPM setter
	*
	*  sets the BPM
	*
	*  \param BPM : BRM of the sound.
	*/
	void setBPM(int BPM);

	/*!
	*  \brief set Mute
	*
	*  Mute or UnMute the sound
	*
	*  \param mute : boolean to define if the sound needs to be muted.
	*/
	void setMute(bool mute);

	/*!
	*  \brief set Language
	*
	*  set the language of the user and the software
	*
	*  \param language : langage of the software.
	*/
	void setLanguage(Language language);

	/*!
	*  \brief set Theme
	*
	*  set the theme of the the software
	*
	*  \param theme : theme to set.
	*/
	void setTheme(Theme theme);


	MusicParameters getMusicParameter();


private:
	Language _language; /*!< language of the user */
	int _volume; /*!< volume in percentage */
	bool _mute; /*!< if the sound is muted or not */
	Theme _theme; /*!< theme used by the software */
	std::vector<Theme> _themelist; /*!< all existing theme to choose from */
	MusicParameters _musicParameters;
};




#endif  // USERSETTINGS_H_INCLUDED
