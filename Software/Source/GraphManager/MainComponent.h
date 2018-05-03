/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include <thread>
#include <mutex>
#include "../JuceLibraryCode/JuceHeader.h"
#include "MusicStyleButton.h"
#include "../UserSettings.h"
#include "../MusicParameters.hh"
#include "AComponent.hh"

#ifndef  LOGO_WIDTH
#define LOGO_WIDTH 1024 / 2
#endif
#ifndef  LOGO_HEIGHT
#define LOGO_HEIGHT 927 / 2
#endif
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

class MainContentComponent : public Component, public SliderListener, public Button::Listener, public AComponent
{
public:
    //==============================================================================
	MusicStyleButton * blues;  /*!< button for generating blues*/
	MusicStyleButton *params;  /*!< button for generating blues THIS IS FOR TEST !!!! */
	Theme currentTheme; /*!< Theme defining the colors of the elements*/
	UserSettings us;
	Slider frequencySlider;
	Label frequencyLabel;
	std::thread _threadPlayer; /*!< thread player*/
	Player _player; /*!< player THIS NEED TO BE CHANGED*/

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
	void buttonClicked(Button * button);
	void sliderValueChanged(Slider *slider) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
