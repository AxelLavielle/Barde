/*
  ==============================================================================

    CenterComponent.h
    Created: 24 May 2018 6:29:26pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "AComponent.hh"
#include "UserParamsPanel.hh"
#include "PlayerPanel.hh"
#include "LeftPanel.hh"
#include "../CmdManager.hh"

class CenterPanel : public AComponent
{
public:
	CenterPanel(MusicParameters	&musicParameters, CmdManager & cmdManager);

private:
	void paint(Graphics & g) override;
	void resized() override;
	void changeViewCallback(std::string viewName);
	void refreshGrid();

	MusicParameters	&_musicParameters;
	CmdManager		&_cmdManager;

	PlayerPanel		_playerPanel;
	AComponent		*_mainPanel;
	LeftPanel		_leftPanel;
	UserParamsPanel	_userParamsPanel;
	Grid			_grid;

	User			_user;
};