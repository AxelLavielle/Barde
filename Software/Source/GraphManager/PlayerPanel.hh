/*
  ==============================================================================

    PlayerPanel.h
    Created: 24 May 2018 6:08:41pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "AComponent.hh"
#include "FlexGroup.hh"
#include "SimpleLabel.hh"
#include "../Factories/GuiFactory.hh"
#include "../MusicParameters.hh"

class PlayerPanel : public AComponent, private Slider::Listener
{
public:
	PlayerPanel(MusicParameters & musicParameters);

private:
	void paint(Graphics & g) override;
	void resized() override;
	void sliderValueChanged(Slider *slider) override;
	void addFlexItem(Component & component, const float minWidth = 0.f, const float maxHeight = 0.f, const FlexItem::AlignSelf & align = FlexItem::AlignSelf::autoAlign);

	MusicParameters			&_musicParameters;

	Slider					_bpmSlider;
	SimpleLabel				_titleLabel;
	SimpleLabel				_bpmLabel;
	FlexGroup				_bpmGroup;
	FlexGroup				_instrumentsGroup;
	FlexBox					_flexBox;

	SimpleLabel				_styleLabel;
	ToggleButton			_bluesButton;
	ToggleButton			_raggaeButton;
	ToggleButton			_houseButton;

	SimpleLabel				_chordsLabel;
	SimpleLabel				_arpegiosLabel;
	SimpleLabel				_drumsLabel;

	std::vector<FlexItem>	_items;
};