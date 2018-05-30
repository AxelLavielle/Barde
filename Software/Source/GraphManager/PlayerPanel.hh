/*
  ==============================================================================

    PlayerPanel.h
    Created: 24 May 2018 6:08:41pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include <ctime>

#include "FlexGroup.hh"
#include "SimpleLabel.hh"
#include "../Factories/GuiFactory.hh"
#include "../MusicParameters.hh"
#include "../GraphManager/Theme.h"
#include "../ViewManager/FlexView.hh"

class PlayerPanel : public FlexView, private Slider::Listener, private ToggleButton::Listener
{
public:
	PlayerPanel(MusicParameters & musicParameters);

private:
	void paint(Graphics & g) override;
	void sliderValueChanged(Slider *slider) override;
	void buttonClicked(Button * button) override;
	void initInstrumentsButtons(ToggleButton buttons[], const std::string & categoryName, const std::vector<Instrument> & instruments);
	void initMusicParameters();
	bool containInstrument(const std::vector<Instrument>& instruments, const std::string & instrumentName);
	void initInstrumentsGroup();

	MusicParameters			&_musicParameters;

	Slider					_bpmSlider;
	SimpleLabel				_titleLabel;
	SimpleLabel				_bpmLabel;
	FlexGroup				_bpmGroup;
	SimpleLabel				_bpmTitleLabel;

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

	FlexGroup				_styleGroup;
	SimpleLabel				_styleLabel;
	ToggleButton			_bluesButton;
	ToggleButton			_raggaeButton;
	ToggleButton			_houseButton;

	StringArray				_instrusChoice;
};