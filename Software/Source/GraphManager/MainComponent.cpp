/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "Theme.h"

//==============================================================================

MainContentComponent::MainContentComponent() : _cmdManager(CmdManager::getInstance()), _playerFooter(_player, _musicParameters), _centerPanel(_musicParameters)
{
	setSize(getParentWidth(), getParentHeight() - 10);

	_loginPanel.setChangeViewCallback(std::bind(&MainContentComponent::changeViewCallback, this, std::placeholders::_1));
	_centerPanel.setChangeViewCallback(std::bind(&MainContentComponent::changeViewCallback, this, std::placeholders::_1));


	//_currentsPanel.push_back(&_loginPanel);

	_currentsPanel.push_back(&_centerPanel);
	_currentsPanel.push_back(&_playerFooter);

	std::vector<AView * >::iterator	it;

	for (it = _currentsPanel.begin(); it != _currentsPanel.end(); ++it)
	{
		addAndMakeVisible(*it);
	}

	Theme::getInstance().parseTheme("../Theme/Dark");
	_player.Init();

	//auto test =  CmdManager::getInstance().getUserInfo().getEmail();
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
}

void MainContentComponent::resized()
{
	Grid grid;

	using Track = Grid::TrackInfo;

	grid.templateRows = { Track(8_fr), Track(1_fr) }; //Add 2 rows in the grid
	grid.templateColumns = { Track(1_fr) }; //Add 1 column in the grid

	std::vector<AView * >::iterator	it;

	for (it = _currentsPanel.begin(); it != _currentsPanel.end(); ++it)
	{
		grid.items.add(GridItem(*it));
	}

	grid.performLayout(getLocalBounds());
}

void MainContentComponent::refresh()
{
	std::vector<AView * >::iterator	it;

	for (it = _currentsPanel.begin(); it != _currentsPanel.end(); ++it)
	{
		(*it)->refresh();
	}
}

void MainContentComponent::changeViewCallback(std::string viewName)
{
	if (viewName == "Logout")
	{
		changeView("Logout");
	}
}