/*
  ==============================================================================

    CenterComponent.cpp
    Created: 24 May 2018 6:29:26pm
    Author:  Anthony

  ==============================================================================
*/

#include "CenterPanel.hh"

CenterPanel::CenterPanel(MusicParameters & musicParameters) : _musicParameters(musicParameters), _playerPanel(musicParameters)
{
	addAndMakeVisible(_playerPanel);
	addAndMakeVisible(_leftPanel);
}

void CenterPanel::paint(Graphics & g)
{
}

void CenterPanel::resized()
{
	Grid grid;

	using Track = Grid::TrackInfo;

	grid.templateRows = { Track(1_fr) }; //Add 1 rows in the grid
	grid.templateColumns = { Track(1_fr), Track(6_fr) }; //Add 2 column in the grid
	grid.items = { GridItem(_leftPanel), GridItem(_playerPanel) }; //Add the two components in the grid

	grid.performLayout(getLocalBounds());
}
