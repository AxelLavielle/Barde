/*
  ==============================================================================

    LeftPanel.cpp
    Created: 24 May 2018 6:37:24pm
    Author:  Anthony

  ==============================================================================
*/

#include "LeftPanel.hh"

LeftPanel::LeftPanel()
{
   Image logo = ImageCache::getFromMemory (BinaryData::logo_png,    
										      BinaryData::logo_pngSize);
   _logoImage.setImage(logo);
   addAndMakeVisible(_logoImage);

   //Need CmdManager
   _userButton.setButtonText("Unknow");
   _userButton.setName("User");
   _userButton.addListener(this);
   addAndMakeVisible(_userButton);

   _reportButton.setButtonText("Report a bug / Write a comment");
   _reportButton.setName("Report");
   _reportButton.addListener(this);
   addAndMakeVisible(_reportButton);

   _homeButton.setButtonText("Home");
   _homeButton.setName("Home");
   _homeButton.addListener(this);
   addAndMakeVisible(_homeButton);


   _flexBox = GuiFactory::createFlexBox(FlexBox::JustifyContent::flexStart, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::Direction::column,
	   { GuiFactory::createFlexItem(_logoImage, LOGO_WIDTH, LOGO_HEIGHT, 0, 0, FlexItem::AlignSelf::autoAlign, 1), GuiFactory::createFlexItem(_homeButton, 80, 20), GuiFactory::createFlexItem(_userButton, 80, 20), GuiFactory::createFlexItem(_reportButton, 80, 20) });
}

void LeftPanel::setUser(const User & user)
{
	_user = user;
	_userButton.setButtonText(_user.getFirstName() + " " + _user.getLastName());
}

void LeftPanel::paint(Graphics & g)
{
	g.fillAll(Colours::grey);
}

void LeftPanel::buttonClicked(Button * button)
{
	if (button->getName() == "User")
		changeView("UserParams");
	else if (button->getName() == "Report")
		changeView("Report");
	else if (button->getName() == "Home")
		changeView("Player");
}
