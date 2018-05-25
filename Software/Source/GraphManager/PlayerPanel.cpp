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
	Font font;
	font.setSizeAndStyle(13, "plain", 0.8, 0.5);
	_bpmLabel.setText("Bpm : " + std::to_string(_musicParameters.getBpm()), NotificationType::dontSendNotification);
	_bpmLabel.setFont(font);

	_bpmSlider.setRange(70, 200);
	_bpmSlider.setBounds(10, 0, 1000, 50);
	_bpmSlider.setValue(_musicParameters.getBpm());
	_bpmSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	_bpmSlider.addListener(this);

	_titleLabel.setText("Edit your music", NotificationType::dontSendNotification);
	font.setSizeAndStyle(30, "plain", 0.8, 0.5);
	_titleLabel.setFont(font);
	addAndMakeVisible(_titleLabel);

	_bpmGroup.setAlignContent(FlexBox::AlignContent::stretch);
	_bpmGroup.setJustifyContent(FlexBox::JustifyContent::center);
	_bpmGroup.setAlignItems(FlexBox::AlignItems::stretch);
	_bpmGroup.setFlexDirection(FlexBox::Direction::row);
	_bpmGroup.addItem(GuiFactory::createFlexItem(_bpmSlider, 300, 30, FlexItem::AlignSelf::autoAlign, 1));
	_bpmGroup.addItem(GuiFactory::createFlexItem(_bpmLabel, 100, 30));
	addAndMakeVisible(_bpmGroup);

	_flexBox = GuiFactory::createFlexBox(FlexBox::JustifyContent::spaceAround, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::Direction::column,
		{ GuiFactory::createFlexItem(_titleLabel, 100, 50), GuiFactory::createFlexItem(_bpmGroup, 400, 30) });
}

void PlayerPanel::paint(Graphics & g)
{
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

