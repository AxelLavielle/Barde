/*
  ==============================================================================

    PlayingCtrlButton.h
    Created: 22 Jul 2018 12:31:41am
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Theme.h"

enum BUTTON_PLAYING_TYPE
{
	PLAY,
	PAUSE,
	STOP
};

class PlayingCtrlButton : public Button
{
public:
	PlayingCtrlButton(const String &buttonName, BUTTON_PLAYING_TYPE buttonType);
	~PlayingCtrlButton();

private:
	void paintButton(Graphics& g, const bool isMouseOverButton, const bool isButtonDown) override;

	BUTTON_PLAYING_TYPE		_type;
};