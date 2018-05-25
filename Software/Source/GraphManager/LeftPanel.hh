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
#include "../User.hh"

#define LOGO_WIDTH 231
#define LOGO_HEIGHT 256

class LeftPanel : public AComponent, private Button::Listener
{
public:
	LeftPanel();
	void setUser(const User & user);

private:
	void paint(Graphics & g) override;
	void resized() override;
	void buttonClicked(Button * button) override;

	FlexBox				_flexBox;
	ImageComponent		_logoImage;
	TextButton			_userButton;

	User				_user;
};