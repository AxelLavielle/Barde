/*
  ==============================================================================

    LabeledTextBox.h
    Created: 25 May 2018 7:00:30pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "FlexGroup.hh"
#include "SimpleLabel.hh"

#ifndef __GUIFACTORY__
class GuiFactory
{
public:
	static void initVerticalFlexGroup(const std::vector<FlexItem>& items, FlexGroup & group);
	static FlexItem createFlexItem(Component & component, const float minWidth = 0.f, const float minHeight = 0.f,
		const FlexItem::AlignSelf & alignSelf = FlexItem::AlignSelf::autoAlign, const float flexGrow = 0.f);
	static void initLegendLabel(const std::string & text, SimpleLabel & label);
};
#endif

class LabeledTextBox : public FlexGroup
{
public:
	LabeledTextBox();
	void setLabelText(const std::string & text);
	std::string	getText() const;
	void setText(const std::string & text);
	void setPasswordCharacter(juce::juce_wchar passwordCharacter);

private:

	TextEditor		_textBox;
	SimpleLabel		_label;
	FlexItem		_textItem;
	FlexItem		_labelItem;
};