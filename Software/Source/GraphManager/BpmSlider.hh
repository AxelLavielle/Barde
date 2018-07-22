/*
  ==============================================================================

    BpmSlider.h
    Created: 22 Jul 2018 11:39:34am
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "../Factories/GuiFactory.hh"

class BpmSlider : public FlexGroup, private Slider::Listener
{
public:
	BpmSlider();
	~BpmSlider();
	void init(const int sliderValue, std::function<void(Slider *slider)> sliderHandler);

private:
	void sliderValueChanged(Slider *slider) override;


	int									_sliderValue;
	std::function<void(Slider *slider)>	_sliderHandler;

	Slider								_bpmSlider;
	SimpleLabel							_bpmLabel;
	SimpleLabel							_minBpmLabel;
	SimpleLabel							_maxBpmLabel;
	FlexGroup							_sliderBpmGroup;
};