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
#include "../GraphManager/Theme.h"

class PlayerPanel : public AComponent, private Slider::Listener, private ToggleButton::Listener
{
public:
	PlayerPanel(MusicParameters & musicParameters);

private:
	void paint(Graphics & g) override;
	void resized() override;
	void sliderValueChanged(Slider *slider) override;
	void buttonClicked(Button * button) override;
	void addFlexItem(Component & component, const float minWidth = 0.f, const float maxHeight = 0.f, const FlexItem::AlignSelf & align = FlexItem::AlignSelf::autoAlign);
	void initInstrumentsButtons(ToggleButton buttons[], const std::string & categoryName);
	void initInstrumentsGroup();

	MusicParameters			&_musicParameters;

	Slider					_bpmSlider;
	SimpleLabel				_titleLabel;
	SimpleLabel				_bpmLabel;
	FlexGroup				_bpmGroup;

	FlexGroup				_instrumentsGroup;

	FlexGroup				_chordsGroup;
	SimpleLabel				_chordsLabel;
	ToggleButton			_chordInstrumentButtons[3];

	FlexGroup				_arpegiosGroup;
	SimpleLabel				_arpegiosLabel;
	ToggleButton			_arpegiosInstrumentButtons[3];

	FlexGroup				_drumsGroup;
	SimpleLabel				_drumsLabel;
	ToggleButton			_drumsInstrumentButton;

	SimpleLabel				_styleLabel;
	ToggleButton			_bluesButton;
	ToggleButton			_raggaeButton;
	ToggleButton			_houseButton;


	FlexBox					_flexBox;

	std::vector<FlexItem>	_items;

	StringArray				_instrusChoice;
};