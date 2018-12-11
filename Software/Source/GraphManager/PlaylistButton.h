/*
==============================================================================

PlayListButton.h
Created: 14 Mar 2017 3:21:14pm
Author:  Oreo

==============================================================================
*/

#ifndef PlayListBUTTON_H_INCLUDED
#define PlayListBUTTON_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Player.hh"
#include "Theme.h"
#include "../UserSettings.h"

/*! \class PlayListButton
* \brief classe representing a button for a specific music style
*
*  This class generates a music style button
*/

class PlayListButton : public Button
{
public:
	/*!
	*  \brief Constructor
	*
	*  PlayListButton class constructor
	*
	*  \param buttonName : name of the button / Text to display
	*  \param w : Button width
	*  \param h : Button height
	*  \param theme : Theme
	*/
	PlayListButton(const String &buttonName, const int w, const int h);
	/*!
	*  \brief Destructor
	*
	*  PlayListButton class destructor
	*/
	~PlayListButton();

private:
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


	int _width; /*!< Button width*/
	int _height; /*!< Button height*/


};

#endif  // PlayListBUTTON_H_INCLUDED