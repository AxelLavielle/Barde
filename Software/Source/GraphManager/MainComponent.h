/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MusicStyleButton.h"


#define LOGO_WIDTH 1024 / 2
#define LOGO_HEIGHT 927 / 2
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

class MainContentComponent   : public Component
{
public:
    //==============================================================================
	MusicStyleButton *blues;  /*!< button for generating blues*/

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

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
