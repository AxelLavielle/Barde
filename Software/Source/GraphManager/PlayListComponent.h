/*
  ==============================================================================

    PlayListComponent.h
    Created: 22 Nov 2018 10:28:16am
    Author:  Oreo

  ==============================================================================
*/


#pragma once

#include <ctime>

#include "FlexGroup.hh"
#include "SimpleLabel.hh"
#include "../Factories/GuiFactory.hh"
#include "../MusicParameters.hh"
#include "../GraphManager/Theme.h"
#include "../ViewManager/FlexView.hh"
#include "BpmSlider.hh"
#include "../GraphManager/PlaylistButton.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "../CmdManager.hh"

class PlayListComponent : public AComponent, public TextButton::Listener
{
public:
	PlayListComponent(CmdManager & cmdManager);
	
private:
	//void paint(Graphics & g) override;
	void buttonClicked(Button * button) override;
	
	CmdManager	&_cmdManager;
	OwnedArray<PlayListButton> playListButtons;


};