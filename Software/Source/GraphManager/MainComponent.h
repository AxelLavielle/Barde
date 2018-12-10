/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MusicStyleButton.h"
#include "../UserSettings.h"
#include "../MusicParameters.hh"
#include "../Instrument.hh"
#include "AComponent.hh"
#include "PlayerFooter.hh"
#include "CenterPanel.hh"
#include "LoginPanel.hh"
#include "PlayListComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

/*! \class MainContentComponent
* \brief class representing the main component of the client
*
* The class is containing all the component needed for the client
*/

class MainContentComponent : public AComponent
{
public:
    //==============================================================================

	/*!
	*  \brief Constructor
	*
	*  MainContentComponent class constructor
	*
	*/
	MainContentComponent();

	/*!
	*  \brief Destructor
	*
	*  MusicContentComponent class destructor
	*/
    ~MainContentComponent();

	/*!
	*  \brief Display
	*
	* Fonction called for the displey of the MainContentComponent
	*/
    void paint (Graphics&) override;

	/*!
	*  \brief Resized
	*
	* Fonction called when the window is resized
	*/
    void resized() override;

	void refresh() override;

	void changeViewCallback(std::string viewName);

private:

    //=============================================================================
	CmdManager				& _cmdManager;
	Player					_player; /*!< player >*/

	MusicParameters			_musicParameters;
	std::vector<AView * >	_currentsPanel;

	PlayerFooter			_playerFooter;
	CenterPanel				_centerPanel;
	LoginPanel				_loginPanel;
	//PlayListComponent		_playLists;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
