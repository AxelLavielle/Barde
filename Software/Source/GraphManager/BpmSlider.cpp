/*
  ==============================================================================

    BpmSlider.cpp
    Created: 22 Jul 2018 11:39:08am
    Author:  Anthony

  ==============================================================================
*/

#include "BpmSlider.hh"

BpmSlider::BpmSlider()
{
	_sliderHandler = NULL;
}

BpmSlider::~BpmSlider()
{
}

void BpmSlider::init(const int sliderValue, std::function<void(Slider *slider)> sliderHandler)
{
	_sliderValue = sliderValue;
	_sliderHandler = sliderHandler;

	_bpmLabel.setFontSize(13);
	_bpmLabel.setLabelText(std::to_string(sliderValue) + " BPM");
	_bpmLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getFontColor()));
	_minBpmLabel.setFontSize(13);
	_minBpmLabel.setLabelText("70");
	_minBpmLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getFontColor())); //Need to do that in the factory !
	_maxBpmLabel.setFontSize(13);
	_maxBpmLabel.setLabelText("200");
	_maxBpmLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getFontColor())); //Need to do that in the factory !

	GuiFactory::initSlider(70.f, 200.f, sliderValue, _bpmSlider);
	_bpmSlider.addListener(this);

	GuiFactory::initVerticalFlexGroup({ GuiFactory::createFlexItem(_bpmLabel, 100, GuiFactory::getBoxLabelHeight(_bpmLabel), FlexItem::AlignSelf::center), GuiFactory::createFlexItem(_bpmSlider, 300, 30, FlexItem::AlignSelf::stretch, 1) }, _sliderBpmGroup);

	GuiFactory::initHoryzontalFlexGroup({ GuiFactory::createFlexItem(_minBpmLabel, 30, GuiFactory::getBoxLabelHeight(_minBpmLabel), FlexItem::AlignSelf::autoAlign).withMargin(FlexItem::Margin(18, 0, 0, 0)),
		GuiFactory::createFlexItem(_sliderBpmGroup, 50, 30, FlexItem::AlignSelf::autoAlign, 1),
		GuiFactory::createFlexItem(_maxBpmLabel, 50, GuiFactory::getBoxLabelHeight(_maxBpmLabel), FlexItem::AlignSelf::autoAlign).withMargin(FlexItem::Margin(18, 0, 0, 0)) }, *this);
}

void BpmSlider::sliderValueChanged(Slider * slider)
{
	_bpmLabel.setText(std::to_string(static_cast<int>(slider->getValue())) + " BPM", NotificationType::dontSendNotification);
	if (_sliderHandler)
		_sliderHandler(slider);
}
