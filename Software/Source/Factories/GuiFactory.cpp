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

FlexItem GuiFactory::createFlexItemLabel(SimpleLabel & label, const FlexItem::AlignSelf & alignSelf, const float flexGrow)
{
	FlexItem flexItem(label);

	flexItem.minWidth = GuiFactory::getBoxLabelWidth(label);
	flexItem.minHeight = GuiFactory::getBoxLabelHeight(label);
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

void GuiFactory::initBigTitle(const std::string & text, SimpleLabel & label)
{
	label.setLabelText(text);
	label.setFontSize(BIG_TITLE_SIZE);

	//TO DO manage theme color
	label.setColour(Label::textColourId, Colours::black);
}

void GuiFactory::initMediumTitle(const std::string & text, SimpleLabel & label)
{
	label.setLabelText(text);
	label.setFontSize(MEDIUM_TITLE_SIZE);

	//TO DO manage theme color
	label.setColour(Label::textColourId, Colours::black);
}

void GuiFactory::initLittleTitle(const std::string & text, SimpleLabel & label)
{
	label.setLabelText(text);
	label.setFontSize(LITTLE_TITLE_SIZE);

	//TO DO manage theme color
	label.setColour(Label::textColourId, Colours::black);
}

float GuiFactory::getBoxLabelHeight(const SimpleLabel & label)
{
	float fontSize;

	fontSize = label.getFontSize();
	return fontSize + LABEL_HEIGHT_PADDING;
}

float GuiFactory::getBoxLabelWidth(const SimpleLabel & label)
{
	float fontSize;

	fontSize = label.getTextWidth();
	return fontSize + LABEL_WIDTH_PADDING;
}

void GuiFactory::initToggleButton(const std::string & text, const std::string & name, ToggleButton & button, const bool state)
{
	button.setButtonText(text);
	button.setName(name);
	//TO DO manage Theme Color
	button.setColour(ToggleButton::textColourId, Colours::black);
	button.setColour(ToggleButton::tickColourId, Colours::black);
	button.setColour(ToggleButton::tickDisabledColourId, Colours::black);
	button.setToggleState(state, NotificationType::dontSendNotification);
}

void GuiFactory::initFlexGroup(const FlexBox::JustifyContent & justifyContent, const FlexBox::AlignContent & alignContent, const FlexBox::AlignItems & alignItems, const FlexBox::Direction & direction, const std::vector<FlexItem>& items, FlexGroup & group)
{
	std::vector<FlexItem>::const_iterator	it;

	group.setAlignContent(alignContent);
	group.setJustifyContent(justifyContent);
	group.setAlignItems(alignItems);
	group.setFlexDirection(direction);
	for (it = items.begin(); it != items.end(); it++)
		group.addItem(*it);
}

void GuiFactory::initVerticalFlexGroup(const std::vector<FlexItem>& items, FlexGroup & group)
{
	std::vector<FlexItem>::const_iterator	it;

	group.setAlignContent(FlexBox::AlignContent::stretch);
	group.setJustifyContent(FlexBox::JustifyContent::center);
	group.setAlignItems(FlexBox::AlignItems::stretch);
	group.setFlexDirection(FlexBox::Direction::column);
	for (it = items.begin(); it != items.end(); it++)
		group.addItem(*it);

}

void GuiFactory::initHoryzontalFlexGroup(const std::vector<FlexItem>& items, FlexGroup & group)
{
	std::vector<FlexItem>::const_iterator	it;

	group.setAlignContent(FlexBox::AlignContent::stretch);
	group.setJustifyContent(FlexBox::JustifyContent::center);
	group.setAlignItems(FlexBox::AlignItems::stretch);
	group.setFlexDirection(FlexBox::Direction::row);
	for (it = items.begin(); it != items.end(); it++)
		group.addItem(*it);

}
