/*
  ==============================================================================

    CenterComponent.h
    Created: 24 May 2018 6:29:26pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "UserParamsPanel.hh"
#include "PlayerPanel.hh"
#include "LeftPanel.hh"
#include "ReportPanel.hh"
#include "../CmdManager.hh"
#include "../GraphManager/TutorialComponent.h"

class CenterPanel : public FlexView //Need to change heritage
{
public:
	CenterPanel(MusicParameters	&musicParameters);
	void refresh() override;

private:
	void paint(Graphics & g) override;
	void resized() override;
	void changeViewCallback(std::string viewName);
	void refreshGrid();

	MusicParameters	&_musicParameters;
	CmdManager		&_cmdManager;

	PlayerPanel		_playerPanel;
	AView			*_mainPanel;
	LeftPanel		_leftPanel;
	UserParamsPanel	_userParamsPanel;
	ReportPanel		_reportPanel;
	TutorialComponent        _tutorialPanel;
	Grid			_grid;

	User			_user;
};