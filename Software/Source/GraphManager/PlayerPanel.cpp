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

	GuiFactory::initBigTitle("Edit your music", _titleLabel);
	addFlexItem(_titleLabel, 100, 35);

	GuiFactory::initLittleTitle("Choice your style", _styleLabel);
	addFlexItem(_styleLabel, 100, 25);

	GuiFactory::initLittleTitle("Chords instruments", _chordsLabel);

	GuiFactory::initLittleTitle("Arpegios instruments", _arpegiosLabel);

	GuiFactory::initLittleTitle("Drums instruments", _drumsLabel);

	_instrumentsGroup.setAlignContent(FlexBox::AlignContent::stretch);
	_instrumentsGroup.setJustifyContent(FlexBox::JustifyContent::center);
	_instrumentsGroup.setAlignItems(FlexBox::AlignItems::stretch);
	_instrumentsGroup.setFlexDirection(FlexBox::Direction::row);
	_instrumentsGroup.addItem(GuiFactory::createFlexItem(_chordsLabel, 50, 25, FlexItem::AlignSelf::autoAlign, 1));
	_instrumentsGroup.addItem(GuiFactory::createFlexItem(_arpegiosLabel, 50, 25, FlexItem::AlignSelf::autoAlign, 1));
	_instrumentsGroup.addItem(GuiFactory::createFlexItem(_drumsLabel, 50, 25, FlexItem::AlignSelf::autoAlign, 1));
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

