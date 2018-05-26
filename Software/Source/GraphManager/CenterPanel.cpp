/*
  ==============================================================================

    CenterComponent.cpp
    Created: 24 May 2018 6:29:26pm
    Author:  Anthony

  ==============================================================================
*/

#include "CenterPanel.hh"

CenterPanel::CenterPanel(MusicParameters & musicParameters, CmdManager & cmdManager) : _musicParameters(musicParameters), _cmdManager(cmdManager), _playerPanel(_musicParameters)
{
	//TO DO create a singletone to manage userInstance
	_user = _cmdManager.getUserInfo();

	_leftPanel.setUser(_user);
	addAndMakeVisible(_leftPanel);

	_reportPanel.setChangeViewCallback(std::bind(&CenterPanel::changeViewCallback, this, std::placeholders::_1));
	_leftPanel.setChangeViewCallback(std::bind(&CenterPanel::changeViewCallback, this, std::placeholders::_1));
	_mainPanel = &_playerPanel;
	addAndMakeVisible(*_mainPanel);



	using Track = Grid::TrackInfo;

	_grid.templateRows = { Track(1_fr) }; //Add 1 rows in the grid
	_grid.templateColumns = { Track(1_fr), Track(6_fr) }; //Add 2 column in the grid

	refreshGrid();
}

void CenterPanel::paint(Graphics & g)
{
}

void CenterPanel::resized()
{
	_grid.performLayout(getLocalBounds());
}

void CenterPanel::changeViewCallback(std::string viewName)
{
	if (viewName == "UserParams")
	{
		removeChildComponent(1);
		_mainPanel = &_userParamsPanel;
		refreshGrid();
		resized();
	}
	else if (viewName == "Report")
	{
		removeChildComponent(1);
		_mainPanel = &_reportPanel;
		refreshGrid();
		resized();
	}
	else if (viewName == "Player")
	{
		removeChildComponent(1);
		_mainPanel = &_playerPanel;
		refreshGrid();
		resized();
	}
}

void CenterPanel::refreshGrid()
{
	addAndMakeVisible(*_mainPanel);
	_grid.items = { GridItem(_leftPanel), GridItem(*_mainPanel) }; //Add the two components in the grid
}