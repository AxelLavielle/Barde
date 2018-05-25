/*
  ==============================================================================

    GuiFactory.cpp
    Created: 25 May 2018 12:45:54am
    Author:  Anthony

  ==============================================================================
*/

#include "GuiFactory.hh"

FlexBox GuiFactory::createFlexBox(const FlexBox::JustifyContent & justifyContent, const FlexBox::AlignContent & alignContent,
									const FlexBox::AlignItems & alignItems, const FlexBox::Direction & direction,
									const std::vector<FlexItem> & items,
									const FlexBox::Wrap & wrap)
{
	FlexBox	flexBox;
	std::vector<FlexItem>::const_iterator	it;

	flexBox.justifyContent = justifyContent;
	flexBox.alignContent = alignContent;
	flexBox.alignItems = alignItems;
	flexBox.flexDirection = direction;
	flexBox.flexWrap = wrap;

	for (it = items.begin(); it != items.end(); it++)
		flexBox.items.add(*it);
	return std::move(flexBox);
}

FlexBox GuiFactory::createRowCenterFlexBox(const std::vector<FlexItem>& items)
{
	FlexBox	flexBox;
	std::vector<FlexItem>::const_iterator	it;

	flexBox.justifyContent = FlexBox::JustifyContent::center;
	flexBox.alignContent = FlexBox::AlignContent::center;
	flexBox.alignItems = FlexBox::AlignItems::center;
	flexBox.flexDirection = FlexBox::Direction::row;

	for (it = items.begin(); it != items.end(); it++)
		flexBox.items.add(*it);
	return std::move(flexBox);
}

FlexItem GuiFactory::createFlexItem(Component & component, const float minWidth, const float minHeight, const FlexItem::AlignSelf & alignSelf, const float flexGrow)
{
	FlexItem flexItem(component);

	flexItem.minWidth = minWidth;
	flexItem.minHeight = minHeight;
	flexItem.alignSelf = alignSelf;
	flexItem.flexGrow = flexGrow;
	return std::move(flexItem);
}

FlexItem GuiFactory::createFlexItem(Component & component, const float maxWidth, const float maxHeight, const float minWidth, const float minHeight, const FlexItem::AlignSelf & alignSelf, const float flexGrow)
{
	FlexItem flexItem(component);

	flexItem.minWidth = minWidth;
	flexItem.minHeight = minHeight;
	flexItem.maxWidth = maxWidth;
	flexItem.maxHeight = maxHeight;
	flexItem.alignSelf = alignSelf;
	flexItem.flexGrow = flexGrow;
	return std::move(flexItem);
}
