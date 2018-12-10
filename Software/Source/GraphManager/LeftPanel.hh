/*
  ==============================================================================

    LeftPanel.h
    Created: 24 May 2018 6:37:24pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "../ViewManager/FlexView.hh"
#include "../Factories/GuiFactory.hh"
#include "../User.hh"
#include "../icons.h"

#define LOGO_WIDTH 231
#define LOGO_HEIGHT 256

class LeftPanel : public FlexView, private Button::Listener
{
public:
	LeftPanel();
	void setUser(const User & user);
	void refresh() override;

private:
	void paint(Graphics & g) override;
	void buttonClicked(Button * button) override;

	ImageComponent		_logoImage;
	
	//DrawableButton		_reportButton;

	TextButton			_homeButton;
	TextButton			_userButton;
	TextButton			_reportButton;
	TextButton			_tutorialButton;
	TextButton			_disconnectButton;

	User				_user;
};