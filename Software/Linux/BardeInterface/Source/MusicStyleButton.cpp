/*
  ==============================================================================

    MusicStyleButton.cpp
    Created: 14 Mar 2017 3:34:30pm
    Author:  Oreo

  ==============================================================================
*/

#include "MusicStyleButton.h"
#include "../JuceLibraryCode/JuceHeader.h"

MusicStyleButton::MusicStyleButton(const String & buttonName) : Button(buttonName)
{
	setSize(50, 50);
}

MusicStyleButton::~MusicStyleButton()
{

}

void MusicStyleButton::paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
	if (isButtonDown)
	{
		g.setColour(Colour(0xff4169E1));
	}
	else if (isMouseOverButton)
	{
		g.setColour(Colour(0xff6495ED));
	}
	else
	{
		g.setColour(Colour(0xff4682B4));
	}

	g.fillRoundedRectangle(0, 0, 400, 50, 20);
	//Text
	g.setColour(Colours::white);
	g.setFont(14.0f);
	g.drawText("Generer du Blues", 0, 0, 400, 50, Justification::centred, true);
}

