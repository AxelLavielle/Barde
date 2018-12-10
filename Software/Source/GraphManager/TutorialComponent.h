/*
  ==============================================================================

    TutorialComponent.h
    Created: 8 Dec 2018 1:04:45pm
    Author:  Oreo

  ==============================================================================
*/

#pragma once
#ifndef TutorialComponent_H_INCLUDED
#define TutorialComponent_H_INCLUDED

#include "Theme.h"
#include "../ViewManager/FlexView.hh"
#include "../GraphManager/SimpleLabel.hh"
#include "../CmdManager.hh"
#include "../User.hh"
#include "AComponent.hh"
#include <iostream>
#include <string>
#include <regex>


#ifndef  LOGO_WIDTH
#define LOGO_WIDTH 1024 / 3
#endif
#ifndef  LOGO_HEIGHT
#define LOGO_HEIGHT 927 / 3
#endif
#define BOX_WIDTH 400
#define BOX_HEIGHT 30
#define SPACE_BETWEEN 50



class TutorialComponent : public FlexView, private TextEditor::Listener, private Button::Listener
{
public:
	//==============================================================================
	TutorialComponent(CmdManager & cmdManager);
	~TutorialComponent();

private:
	void paint(Graphics&) override;
	void resized() override;
	void buttonClicked(Button* button) override;
	void ThemeChanged();


	TextButton _prevButton, _nextButton;
	//Label _stepCountText;
	static Theme _currentTheme;
	User _user;
	CmdManager &_cmdManager;
	std::vector<Image> images;
	SimpleLabel _stepCountText, _text, _title;

	std::vector<String> titles;
	std::vector<String> texts;
	int step;
	//ComboBox themeChoice;
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TutorialComponent)
};


#endif  // TutorialComponent_H_INCLUDED

