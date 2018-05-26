/*
  ==============================================================================

    FlexView.cpp
    Created: 25 May 2018 1:11:29pm
    Author:  Anthony

  ==============================================================================
*/

#include "FlexView.hh"

void FlexView::resized()
{
	_flexBox.performLayout(getLocalBounds().toFloat());
}

void FlexView::addFlexItem(Component & component, const float minWidth, const float maxHeight, const FlexItem::AlignSelf & align, const float grow)
{
	addAndMakeVisible(component);
	_items.push_back(GuiFactory::createFlexItem(component, minWidth, maxHeight, align, grow));
}

void FlexView::addLabel(SimpleLabel & component)
{
	addAndMakeVisible(component);
	_items.push_back(GuiFactory::createFlexItemLabel(component));
}
