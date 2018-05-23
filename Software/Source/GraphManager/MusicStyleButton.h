/*
  ==============================================================================

    MusicStyleButton.h
    Created: 14 Mar 2017 3:21:14pm
    Author:  Oreo

  ==============================================================================
*/

#ifndef MUSICSTYLEBUTTON_H_INCLUDED
#define MUSICSTYLEBUTTON_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Player.hh"
#include "Theme.h"
#include "../UserSettings.h"

/*! \class MusicStyleButton
* \brief classe representing a button for a specific music style
*
*  This class generates a music style button
*/

class MusicStyleButton : public Button
{
public:
	int _width; /*!< Button width*/
	int _height; /*!< Button height*/
	Theme _theme; /*!< Theme of the app*/

	/*!
	*  \brief Constructor
	*
	*  MusicStyleButton class constructor
	*
	*  \param buttonName : name of the button / Text to display
	*  \param w : Button width
	*  \param h : Button height
	*  \param theme : Theme
	*/
	MusicStyleButton(const String &buttonName, const int w, const int h, Theme theme);
	/*!
	*  \brief Destructor
	*
	*  MusicStyleButton class destructor
	*/
	~MusicStyleButton();
	
	/*!
	*  \brief Diplay of the button
	*
	*  Function that diplays the button and change with some events
	*
	*  \param g : graphic where the button is diplayed
	*  \param isMouseOverButton : boolean corresponding to the mouse over button event
	*  \param isButtonDown :boolean corresponding to the button down event
	*/
	void paintButton(Graphics& g, const bool isMouseOverButton, const bool isButtonDown) override;
};

#endif  // MUSICSTYLEBUTTON_H_INCLUDED
