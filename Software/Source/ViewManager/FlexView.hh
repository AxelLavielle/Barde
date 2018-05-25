/*
  ==============================================================================

    FlexView.h
    Created: 25 May 2018 1:11:29pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "AView.hh"

class FlexView : public AView
{
public:

protected:
	void resized() override;

	FlexBox		_flexBox;
};