/*
  ==============================================================================

    LeftPanel.h
    Created: 24 May 2018 6:37:24pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "AComponent.hh"

class LeftPanel : public AComponent
{
public:
	LeftPanel();

private:
	void paint(Graphics & g) override;

};