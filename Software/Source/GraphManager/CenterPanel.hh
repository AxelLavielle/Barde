/*
  ==============================================================================

    CenterComponent.h
    Created: 24 May 2018 6:29:26pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "AComponent.hh"

#include "PlayerPanel.hh"
#include "LeftPanel.hh"

class CenterPanel : public AComponent
{
public:
	CenterPanel(MusicParameters	&musicParameters);

private:
	void paint(Graphics & g) override;
	void resized() override;

	MusicParameters	&_musicParameters;

	PlayerPanel		_playerPanel;
	LeftPanel		_leftPanel;
};