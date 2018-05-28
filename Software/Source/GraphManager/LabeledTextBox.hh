/*
  ==============================================================================

    LabeledTextBox.h
    Created: 25 May 2018 7:00:30pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "FlexGroup.hh"
#include "../Factories/GuiFactory.hh"

class LabeledTextBox : public FlexGroup
{
public:
	LabeledTextBox();
	void setLabelText(const std::string & text);
	std::string	getText() const;
	void setText(const std::string & text);

private:

	TextEditor		_textBox;
	SimpleLabel		_label;
	FlexItem		_textItem;
	FlexItem		_labelItem;
};