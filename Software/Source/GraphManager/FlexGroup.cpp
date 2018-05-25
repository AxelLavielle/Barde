/*
  ==============================================================================

    FlexGroup.cpp
    Created: 24 May 2018 9:45:33pm
    Author:  Anthony

  ==============================================================================
*/

#include "FlexGroup.hh"

FlexGroup::FlexGroup()
{
}

FlexGroup::FlexGroup(const FlexBox::JustifyContent & justifyContent, const FlexBox::AlignContent & alignContent,
						const FlexBox::AlignItems & alignItem, const FlexBox::Direction & direction)
{
	_flexBox.justifyContent = justifyContent;
	_flexBox.alignContent = alignContent;
	_flexBox.alignItems = alignItem;
	_flexBox.flexDirection = direction;
}

void FlexGroup::paint(Graphics & g)
{
}

void FlexGroup::resized()
{
	_flexBox.performLayout(getLocalBounds().toFloat());
}

void FlexGroup::addItem(FlexItem & item)
{
	addAndMakeVisible(item.associatedComponent);
	_flexBox.items.add(item);
}

void FlexGroup::setJustifyContent(const FlexBox::JustifyContent & justifyContent)
{
	_flexBox.justifyContent = justifyContent;
}

void FlexGroup::setAlignContent(const FlexBox::AlignContent & alignContent)
{
	_flexBox.alignContent = alignContent;

}

void FlexGroup::setAlignItems(const FlexBox::AlignItems & alignItem)
{
	_flexBox.alignItems = alignItem;
}

void FlexGroup::setFlexDirection(const FlexBox::Direction & direction)
{
	_flexBox.flexDirection = direction;
}
