/*
  ==============================================================================

    FlexView.h
    Created: 25 May 2018 1:11:29pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "../Factories/GuiFactory.hh"
#include "AView.hh"

class FlexView : public AView
{
public:

protected:
	void resized() override;
	void addFlexItem(Component & component, const float minWidth = 0.f, const float maxHeight = 0.f, const FlexItem::AlignSelf & align = FlexItem::AlignSelf::autoAlign, const float grow = 0);
	void addLabel(SimpleLabel & component);

	virtual void refresh();

	FlexBox					_flexBox;
	std::vector<FlexItem>	_items;
};