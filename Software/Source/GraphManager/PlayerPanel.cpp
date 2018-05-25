/*
  ==============================================================================

    PlayerPanel.cpp
    Created: 24 May 2018 6:08:41pm
    Author:  Anthony

  ==============================================================================
*/

#include "PlayerPanel.hh"

PlayerPanel::PlayerPanel(MusicParameters & musicParameters) : _musicParameters(musicParameters)
{
	_bpmLabel.setFontSize(13);
	_bpmLabel.setLabelText("Bpm : " + std::to_string(_musicParameters.getBpm()));
	_bpmLabel.setColour(Label::textColourId, Colours::black);

	_titleLabel.setFontSize(30);
	_titleLabel.setLabelText("Edit your music");
	_titleLabel.setColour(Label::textColourId, Colours::black);
	addFlexItem(_titleLabel, 100, 35);

	_styleLabel.setFontSize(20);
	_styleLabel.setLabelText("Choice your style");
	_styleLabel.setColour(Label::textColourId, Colours::black);
	addFlexItem(_styleLabel, 100, 25);

	_chordsLabel.setFontSize(15);
	_chordsLabel.setLabelText("Chords instruments");
	_chordsLabel.setColour(Label::textColourId, Colours::black);

	_arpegiosLabel.setFontSize(15);
	_arpegiosLabel.setLabelText("Arpegios instruments");
	_arpegiosLabel.setColour(Label::textColourId, Colours::black);

	_drumsLabel.setFontSize(15);
	_drumsLabel.setLabelText("Drums instruments");
	_drumsLabel.setColour(Label::textColourId, Colours::black);

	_instrumentsGroup.setAlignContent(FlexBox::AlignContent::stretch);
	_instrumentsGroup.setJustifyContent(FlexBox::JustifyContent::center);
	_instrumentsGroup.setAlignItems(FlexBox::AlignItems::stretch);
	_instrumentsGroup.setFlexDirection(FlexBox::Direction::row);
	_instrumentsGroup.addItem(GuiFactory::createFlexItem(_chordsLabel, 50, 20, FlexItem::AlignSelf::autoAlign, 1));
	_instrumentsGroup.addItem(GuiFactory::createFlexItem(_arpegiosLabel, 50, 20, FlexItem::AlignSelf::autoAlign, 1));
	_instrumentsGroup.addItem(GuiFactory::createFlexItem(_drumsLabel, 50, 20, FlexItem::AlignSelf::autoAlign, 1));
	addFlexItem(_instrumentsGroup, 300, 100);

	_bpmSlider.setRange(70, 200);
	_bpmSlider.setValue(_musicParameters.getBpm());
	_bpmSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	_bpmSlider.addListener(this);

	_bpmGroup.setAlignContent(FlexBox::AlignContent::stretch);
	_bpmGroup.setJustifyContent(FlexBox::JustifyContent::center);
	_bpmGroup.setAlignItems(FlexBox::AlignItems::stretch);
	_bpmGroup.setFlexDirection(FlexBox::Direction::row);
	_bpmGroup.addItem(GuiFactory::createFlexItem(_bpmSlider, 300, 30, FlexItem::AlignSelf::autoAlign, 1));
	_bpmGroup.addItem(GuiFactory::createFlexItem(_bpmLabel, 100, 30));
	addFlexItem(_bpmGroup, 400, 30);

	_flexBox = GuiFactory::createFlexBox(FlexBox::JustifyContent::spaceAround, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::Direction::column, _items);
}

void PlayerPanel::addFlexItem(Component & component, const float minWidth, const float maxHeight, const FlexItem::AlignSelf & align)
{
	addAndMakeVisible(component);
	_items.push_back(GuiFactory::createFlexItem(component, minWidth, maxHeight, align));
}

void PlayerPanel::paint(Graphics & g)
{
	g.fillAll(Colours::white);
}

void PlayerPanel::resized()
{
	_flexBox.performLayout(getLocalBounds().toFloat());
}

void PlayerPanel::sliderValueChanged(Slider * slider)
{
	_bpmLabel.setText("Bpm : " + std::to_string(static_cast<int>(slider->getValue())), NotificationType::dontSendNotification);
	_musicParameters.setBpm(static_cast<int>(slider->getValue()));
}

