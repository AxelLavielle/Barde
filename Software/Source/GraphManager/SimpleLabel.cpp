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
	_font.setSizeAndStyle(10, _font.getTypefaceStyle(), 1, 0.3);
	setFont(_font);
}

void SimpleLabel::setFontSize(const float size)
{
	_fontSize = size;
	_font.setSizeAndStyle(size, _font.getTypefaceStyle(), 1, 0.3);
	setFont(_font);
}

void SimpleLabel::setLabelText(const std::string & text)
{
	setText(text, NotificationType::dontSendNotification);
}

float SimpleLabel::getFontSize() const
{
	return _fontSize;
}

float SimpleLabel::getTextWidth() const
{
	return getText().length() * 0.3;
}

Font SimpleLabel::getFont() const
{
	return _font;
}
