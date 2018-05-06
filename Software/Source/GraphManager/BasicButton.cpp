/*
  ==============================================================================

    BasicButton.cpp
    Created: 6 May 2018 12:08:14pm
    Author:  Anthony

  ==============================================================================
*/

#include "BasicButton.hh"

BasicButton::BasicButton() : Button("")
{
}

BasicButton::~BasicButton()
{
}

void BasicButton::paintButton(Graphics & g, const bool isMouseOverButton, const bool isButtonDown)
{
	//Background Color
	if (isButtonDown)
	{
		g.setColour(Colour(0xFFD2005F));
	}
	else if (isMouseOverButton)
	{
		g.setColour(Colour(0xFF2c3e50));
	}
	else
	{
		g.setColour(Colour(0xFFFFFFFF));
	}

	//Background
	g.fillRoundedRectangle(0.f, 0.f, static_cast<float>(getWidth()), static_cast<float>(getHeight()), 30.f);
	//Text
	g.setColour(Colour(0xFF000000));
	g.setFont(14.0f);
	g.drawText(getButtonText(), 0, 0, getWidth(), getHeight(), Justification::centred, true);
}
