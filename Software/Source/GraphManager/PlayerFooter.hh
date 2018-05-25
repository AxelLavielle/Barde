/*
  ==============================================================================

    PlayerFooter.h
    Created: 24 May 2018 5:18:02pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "MusicStyleButton.h"
#include "../MusicParameters.hh"
#include "FlexGroup.hh"
#include "../Factories/GuiFactory.hh"

class PlayerFooter : public Component, private Button::Listener, private Slider::Listener
{
public:
	PlayerFooter(Player & player, MusicParameters &musicParameters);
	~PlayerFooter();

private:
	void paint(Graphics& g) override;
	void resized() override;
	void buttonClicked(Button * button) override;
	void sliderValueChanged(Slider *slider) override;
	void initFlexBox();

	Player					&_player;
	MusicParameters			&_musicParameters;

	FlexBox					_flexBox;
	FlexGroup				_controlGroup;
	MusicStyleButton		*_playButton;
	MusicStyleButton		*_stopButton;
	Slider					_volumeSlider;
	Theme					_currentTheme; /*!< Theme defining the colors of the elements*/

};