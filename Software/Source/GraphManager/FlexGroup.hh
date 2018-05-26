/*
  ==============================================================================

    FlexGroup.h
    Created: 24 May 2018 9:45:33pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include <vector>
#include "AComponent.hh"

class FlexGroup : public AComponent
{
public:
	FlexGroup();
	FlexGroup(const FlexBox::JustifyContent & justifyContent, const FlexBox::AlignContent & alignContent, const FlexBox::AlignItems & alignItem, const FlexBox::Direction & direction);
	void addItem(const FlexItem & item);
	void refreshItems(const std::vector<FlexItem> & items);
	void setJustifyContent(const FlexBox::JustifyContent & justifyContent);
	void setAlignContent(const FlexBox::AlignContent & alignContent);
	void setAlignItems(const FlexBox::AlignItems & alignItem);
	void setFlexDirection(const FlexBox::Direction & direction);
	void refreshExclusiveToggleItems(const std::string & toggleName);

protected:
	void paint(Graphics & g) override;
	void resized() override;

	FlexBox						_flexBox;
};