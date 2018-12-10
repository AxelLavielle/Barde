/*
==============================================================================

PlayListButton.cpp
Created: 14 Mar 2017 3:34:30pm
Author:  Oreo

==============================================================================
*/

#include "PlayListButton.h"
#include "../JuceLibraryCode/JuceHeader.h"


PlayListButton::PlayListButton(const String & buttonName, const int width, const int height) : Button(buttonName)
{
	_width = width;
	_height = height;
}

PlayListButton::~PlayListButton()
{
}

void PlayListButton::paintButton(Graphics& g, const bool isMouseOverButton, const bool isButtonDown)
{
	//Background Color
	if (isButtonDown)
	{
		g.setColour(Colour(Theme::getInstance().getButtonColor()));
	}
	else if (isMouseOverButton)
	{
		g.setColour(Colour(Theme::getInstance().getButtonColor()));
	}
	else
	{
		g.setColour(Colour(Theme::getInstance().getButtonColor()));
	}

	//Background
	g.fillRoundedRectangle(0.f, 0.f, static_cast<float>(_width), static_cast<float>(_height), 30.f);
	//Text
	g.setColour(Colour(Theme::getInstance().getButtonFontColor()));
	g.setFont(14.0f);
	g.drawText(this->getName(), 0, 0, _width, _height, Justification::centred, true);
}

