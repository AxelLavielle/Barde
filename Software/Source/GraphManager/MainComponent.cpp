/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "Theme.h"

//==============================================================================

MainContentComponent::MainContentComponent(CmdManager & cmdManager) : _cmdManager(cmdManager), _playerFooter(_player, _musicParameters), _centerPanel(_musicParameters, _cmdManager)
{
	setSize(getParentWidth(), getParentHeight() - 10);
	addAndMakeVisible(_playerFooter);
	addAndMakeVisible(_centerPanel);
	Theme::getInstance().parseTheme("../Theme/Dark");
	_player.Init();
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
	grid.items = { GridItem(_centerPanel), GridItem(_playerFooter) }; //Add the two components in the grid

	grid.performLayout(getLocalBounds());
}
