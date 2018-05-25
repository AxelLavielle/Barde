/*
  ==============================================================================

    LeftPanel.h
    Created: 24 May 2018 6:37:24pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "AComponent.hh"
#include "../Factories/GuiFactory.hh"

#define LOGO_WIDTH 231
#define LOGO_HEIGHT 256

class LeftPanel : public AComponent
{
public:
	LeftPanel();

private:
	void paint(Graphics & g) override;
	void resized() override;

	FlexBox				_flexBox;
	ImageComponent		_logoImage;
};