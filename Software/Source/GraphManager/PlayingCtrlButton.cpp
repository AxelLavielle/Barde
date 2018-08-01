/*
  ==============================================================================

    PlayingCtrlButton.cpp
    Created: 22 Jul 2018 12:31:24am
    Author:  Anthony

  ==============================================================================
*/

#include "PlayingCtrlButton.hh"

PlayingCtrlButton::PlayingCtrlButton(const String &buttonName, BUTTON_PLAYING_TYPE buttonType) : Button(buttonName)
{
	_type = buttonType;
}

PlayingCtrlButton::~PlayingCtrlButton()
{
}

void PlayingCtrlButton::paintButton(Graphics & g, const bool isMouseOverButton, const bool isButtonDown)
{
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
	g.fillEllipse(0.f, 0.f, PLAYING_BUTTON_WIDTH, PLAYING_BUTTON_HEIGHT);
	//g.fillRoundedRectangle(0.f, 0.f, static_cast<float>(50), static_cast<float>(50), 90.f);

	g.setColour(Colour(Theme::getInstance().getButtonFontColor()));
	if (_type == BUTTON_PLAYING_TYPE::PLAY)
	{
		juce::Line<float>	line(15, 25, 34, 25);

		g.drawArrow(line, 0.f, 24, 24);
	}
	else if (_type == BUTTON_PLAYING_TYPE::STOP)
	{
		g.fillRect(17, 17, 16, 16);
	}
}
