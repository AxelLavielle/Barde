/*
  ==============================================================================

    MusicStyleButton.cpp
    Created: 14 Mar 2017 3:34:30pm
    Author:  Oreo

  ==============================================================================
*/

#include "MusicStyleButton.h"
#include "../JuceLibraryCode/JuceHeader.h"


MusicStyleButton::MusicStyleButton(const String & buttonName, const int width, const int height, Theme theme, UserSettings *us) : Button(buttonName)
{
	_width = width;
	_height = height;
	_theme = theme;
	_us = us;
}

MusicStyleButton::~MusicStyleButton()
{

}

void MusicStyleButton::paintButton(Graphics& g, const bool isMouseOverButton, const bool isButtonDown)
{
	//Background Color
	if (isButtonDown)
	{
		g.setColour(Colour(_theme.getButtonColor()));
		_player.setMusicparameters(_us->getMusicParameter());
		_threadPlayer = std::thread(&Player::Play, &_player);
		_threadPlayer.detach();
	}
	else if (isMouseOverButton)
	{
	  g.setColour(Colour(_theme.getButtonColor()));
	}
	else
	{
	  g.setColour(Colour(_theme.getButtonColor()));
	}

	//Background
	g.fillRoundedRectangle(0.f, 0.f, static_cast<float>(_width), static_cast<float>(_height), 30.f);
	//Text
	g.setColour(Colour(_theme.getButtonFontColor()));
	g.setFont(14.0f);
	g.drawText(this->getName(), 0, 0, _width, _height, Justification::centred, true);
}

