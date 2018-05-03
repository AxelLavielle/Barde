/*
  ==============================================================================

    MusicStyleButton.cpp
    Created: 14 Mar 2017 3:34:30pm
    Author:  Oreo

  ==============================================================================
*/

#include "MusicStyleButton.h"
#include "../JuceLibraryCode/JuceHeader.h"

MusicStyleButton::MusicStyleButton(const String & buttonName, const int width, const int height, Theme theme) : Button(buttonName)
{
	this->width = width;
	this->height = height;
	this->theme = theme;
}

MusicStyleButton::~MusicStyleButton()
{

}

void MusicStyleButton::paintButton(Graphics& g, const bool isMouseOverButton, const bool isButtonDown)
{
	//Background Color
	if (isButtonDown)
	{
	  g.setColour(Colour(this->theme.getButtonColor()));
		//_threadPlayer = std::thread(&Player::Play, &_player);
		//_threadPlayer.detach();
	}
	else if (isMouseOverButton)
	{
	  g.setColour(Colour(this->theme.getButtonColor()));
	}
	else
	{
	  g.setColour(Colour(this->theme.getButtonColor()));
	}

	//Background
	g.fillRoundedRectangle(0, 0, this->width, this->height, 30);
	//Text
	g.setColour(Colour(this->theme.getButtonFontColor()));
	g.setFont(14.0f);
	g.drawText(this->getName(), 0, 0, this->width, this->height, Justification::centred, true);
}

