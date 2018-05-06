/*
  ==============================================================================

    BasicButton.h
    Created: 6 May 2018 12:08:31pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class BasicButton : public Button
{
public:
	BasicButton();
	~BasicButton();

private:
	void paintButton(Graphics& g, const bool isMouseOverButton, const bool isButtonDown) override;

};