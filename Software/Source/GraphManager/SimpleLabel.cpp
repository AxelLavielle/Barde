/*
  ==============================================================================

    SimpleLabel.cpp
    Created: 25 May 2018 8:33:20am
    Author:  Anthony

  ==============================================================================
*/

#include "SimpleLabel.hh"

SimpleLabel::SimpleLabel()
{
	_font.setTypefaceStyle("plain");
	_font.setSizeAndStyle(10, _font.getTypefaceStyle(), 0.8, 0.5);
	setFont(_font);
}

void SimpleLabel::setFontSize(const float size)
{
	_font.setSizeAndStyle(size, _font.getTypefaceStyle(), 0.8, 0.5);
	setFont(_font);
}

void SimpleLabel::setLabelText(const std::string & text)
{
	setText(text, NotificationType::dontSendNotification);
}
