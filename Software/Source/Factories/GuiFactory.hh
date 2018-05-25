/*
  ==============================================================================

    GuiFactory.h
    Created: 25 May 2018 12:45:54am
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "../JuceHeader.h"

class GuiFactory
{
public:
	static FlexBox createFlexBox(const FlexBox::JustifyContent & justifyContent, const FlexBox::AlignContent & alignContent,
							const FlexBox::AlignItems & alignItems, const FlexBox::Direction & direction,
							const std::vector<FlexItem> & items,
							const FlexBox::Wrap & wrap = FlexBox::Wrap::noWrap);

	static FlexBox createRowCenterFlexBox(const std::vector<FlexItem> & items);
	static FlexItem createFlexItem(Component & component, const float minWidth = 0.f, const float minHeight = 0.f, const FlexItem::AlignSelf & alignSelf = FlexItem::AlignSelf::autoAlign, const float flexGrow = 0.f);
};