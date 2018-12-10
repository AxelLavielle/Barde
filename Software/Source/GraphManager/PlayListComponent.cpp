/*
  ==============================================================================

    PlayListComponent.cpp
    Created: 22 Nov 2018 10:28:16am
    Author:  Oreo

  ==============================================================================
*/

#include "PlayListComponent.h"


PlayListComponent::PlayListComponent(CmdManager & cmdManager) : _cmdManager(cmdManager)
{
	Theme::getInstance().parseTheme("../Themes/Dark");


	for (int i = 0; i < 4; ++i) {
		auto btn = new PlayListButton("PlayList" + String::charToString('A' + i), 100, 100);
		//auto btn = new TextButton(String::charToString('A' + i));
		btn->addListener(this);
		addAndMakeVisible(btn);
		playListButtons.add(btn);
	}
}

void PlayListComponent::buttonClicked(Button * button)
{
	//TODO GERER LES PLAYLISTS
}

