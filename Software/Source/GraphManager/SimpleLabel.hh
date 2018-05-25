/*
  ==============================================================================

    SimpleLabel.h
    Created: 25 May 2018 8:33:19am
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "../JuceHeader.h"

class SimpleLabel : public Label
{
public:
	SimpleLabel();
	void setFontSize(const float size);
	void setLabelText(const std::string & text);
	Font getFont() const;


private:
	Font	_font;
};