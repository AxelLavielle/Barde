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

FlexBox GuiFactory::createFlexBox(const FlexBox::JustifyContent & justifyContent, const FlexBox::AlignContent & alignContent, const FlexBox::AlignItems & alignItems, const FlexBox::Direction & direction, std::vector<FlexItem>& items, const float maxWidth, const float maxHeight, const FlexBox::Wrap & wrap)
{
	FlexBox	flexBox;
	std::vector<FlexItem>::iterator	it;

	flexBox.justifyContent = justifyContent;
	flexBox.alignContent = alignContent;
	flexBox.alignItems = alignItems;
	flexBox.flexDirection = direction;
	flexBox.flexWrap = wrap;

	for (it = items.begin(); it != items.end(); it++)
	{
		it->maxWidth = maxWidth;
		it->maxHeight = maxHeight;
		flexBox.items.add(*it);
	}
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

	label.setColour(Label::textColourId, Colour(Theme::getInstance().getFontColor()));
}

void GuiFactory::initMediumTitle(const std::string & text, SimpleLabel & label)
{
	label.setLabelText(text);
	label.setFontSize(MEDIUM_TITLE_SIZE);

	label.setColour(Label::textColourId, Colour(Theme::getInstance().getFontColor()));
}

void GuiFactory::initLittleTitle(const std::string & text, SimpleLabel & label)
{
	label.setLabelText(text);
	label.setFontSize(LITTLE_TITLE_SIZE);

	label.setColour(Label::textColourId, Colour(Theme::getInstance().getFontColor()));
}

void GuiFactory::initLegendLabel(const std::string & text, SimpleLabel & label)
{
	label.setLabelText(text);
	label.setFontSize(LEGEND_LABEL_SIZE);

	label.setColour(Label::textColourId, Colour(Theme::getInstance().getFontColor()));
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
	return fontSize * LABEL_WIDTH_PADDING;
}

void GuiFactory::initToggleButton(const std::string & text, const std::string & name, ToggleButton & button, const bool state)
{
	button.setButtonText(text);
	button.setName(name);
	button.setToggleState(state, NotificationType::dontSendNotification);
	button.setColour(ToggleButton::textColourId, Colour(Theme::getInstance().getFontColor()));
	button.setColour(ToggleButton::tickColourId, Colour(Theme::getInstance().getFontColor()));
	button.setColour(ToggleButton::tickDisabledColourId, Colour(Theme::getInstance().getFontColor()));
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

void GuiFactory::initSlider(const float min, const float max, const float value, Slider & slider)
{
	slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	slider.setColour(Slider::backgroundColourId, Colour(Theme::getInstance().getSliderOffColor()));
	slider.setColour(Slider::thumbColourId, Colour(Theme::getInstance().getSliderPointerColor()));
	slider.setColour(Slider::trackColourId, Colour(Theme::getInstance().getSliderOnColor()));
	//For the TextBox
	//slider.setColour(Label::textColourId, Colour(Theme::getInstance().getFontColor()));
	//slider.setColour(Slider::textBoxBackgroundColourId, Colour(Theme::getInstance().getBackgroundColor()));
	//slider.setColour(Slider::textBoxTextColourId, Colour(Theme::getInstance().getFontColor()));
	slider.setRange(min, max, 1);
	slider.setValue(value);

}

void GuiFactory::initLabeledTextBox(const std::string & labelText, const std::string & boxText, LabeledTextBox & textBox)
{
	textBox.setLabelText(labelText);
	textBox.setText(boxText);
}

void GuiFactory::initTextEditor(TextEditor & textBox)
{
	textBox.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	textBox.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	textBox.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	textBox.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	textBox.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
}

void GuiFactory::initLabeledTextBoxPassword(const std::string & labelText, const std::string & boxText, const juce_wchar & character, LabeledTextBox & textBox)
{
	textBox.setPasswordCharacter(character);
	textBox.setLabelText(labelText);
	textBox.setText(boxText);
}

void GuiFactory::initButton(const std::string & buttonText, const std::string & buttonName, juce::Button::Listener *listener, Button & button)
{
	button.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	button.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));
	button.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
	button.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	button.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
	button.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));

	button.setButtonText(buttonText);
	button.setName(buttonName);
	button.addListener(listener);
}