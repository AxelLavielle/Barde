/*
  ==============================================================================

    PlayerPanel.h
    Created: 24 May 2018 6:08:41pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "AComponent.hh"
#include "../Factories/GuiFactory.hh"
#include "FlexGroup.hh"
#include "../MusicParameters.hh"

class PlayerPanel : public AComponent, private Slider::Listener
{
public:
	PlayerPanel(MusicParameters & musicParameters);

private:
	void paint(Graphics & g) override;
	void resized() override;
	void sliderValueChanged(Slider *slider) override;

	MusicParameters			&_musicParameters;

	Slider					_bpmSlider;
	Label					_titleLabel;
	Label					_bpmLabel;
	FlexGroup				_bpmGroup;
	FlexBox					_flexBox;
};