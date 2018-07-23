/*
  ==============================================================================

    LeftPanel.cpp
    Created: 24 May 2018 6:37:24pm
    Author:  Anthony

  ==============================================================================
*/

#include "LeftPanel.hh"

LeftPanel::LeftPanel()// : _reportButton("Bug_report", DrawableButton::ButtonStyle::ImageAboveTextLabel)
{
   Image logo = ImageCache::getFromMemory (BinaryData::logo_png,    
										      BinaryData::logo_pngSize);
   _logoImage.setImage(logo);
   addAndMakeVisible(_logoImage);

   _homeButton.setButtonText("Generation");
   _homeButton.setName("Home");
   _homeButton.addListener(this);
   addAndMakeVisible(_homeButton);

   _userButton.setButtonText("Not connected");
   _userButton.setName("User");
   _userButton.addListener(this);
   addAndMakeVisible(_userButton);

   Image logo2 = ImageCache::getFromMemory(icons::baselinebug_report24px_svg,
	   icons::baselinebug_report24px_svgSize);

   DrawableImage convert;

   convert.setImage(logo2);

   //_reportButton.setImages(&convert);

   _reportButton.setButtonText("Report a bug / Write a comment");
   _reportButton.setName("Report");
   _reportButton.addListener(this);
   addAndMakeVisible(_reportButton);

   _disconnectButton.setButtonText("Logout");
   _disconnectButton.setName("Logout");
   _disconnectButton.addListener(this);
   addAndMakeVisible(_disconnectButton);


   _homeButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
   _homeButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
   _homeButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));

   _userButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
   _userButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
   _userButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));

   _reportButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
   _reportButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
   _reportButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));

   _disconnectButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
   _disconnectButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
   _disconnectButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));


   _flexBox = GuiFactory::createFlexBox(FlexBox::JustifyContent::flexStart, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::Direction::column,
	   { GuiFactory::createFlexItem(_logoImage, LOGO_WIDTH + 50, LOGO_HEIGHT, 0, 0, FlexItem::AlignSelf::stretch, 1), GuiFactory::createFlexItem(_homeButton, 80, 20), GuiFactory::createFlexItem(_userButton, 80, 20), GuiFactory::createFlexItem(_reportButton, 80, 20), GuiFactory::createFlexItem(_disconnectButton, 80, 20) });
}

void LeftPanel::setUser(const User & user)
{
	//TODO FIX THIS
	_user = user;
	//_userButton.setButtonText(_user.getFirstName() + " " + _user.getLastName());
	_userButton.setButtonText("Edit user info");
}

void LeftPanel::paint(Graphics & g)
{
	//g.fillAll(Colours::grey);
	g.fillAll(Colour(0xFF6C7A89));
}

void LeftPanel::buttonClicked(Button * button)
{
	if (button->getName() == "User")
		changeView("UserParams");
	else if (button->getName() == "Report")
		changeView("Report");
	else if (button->getName() == "Home")
		changeView("Player");
	else if (button->getName() == "Logout")
		changeView("Logout");
}

void LeftPanel::refresh()
{

}