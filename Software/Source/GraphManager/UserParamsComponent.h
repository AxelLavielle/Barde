/*
==============================================================================

UserParamsComponent.h
Created: 13 Jan 2018 2:36:43pm
Author:  Oreo

==============================================================================
*/


#ifndef USERPARAMSCOMPONENT_H_INCLUDED
#define USERPARAMSCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Theme.h"
#include "../CmdManager.hh"
#include "../User.hh"
#include <iostream>
#include <string>
#include <regex>


#define LOGO_WIDTH 1024 / 3
#define LOGO_HEIGHT 927 / 3
#define BOX_WIDTH 400
#define BOX_HEIGHT 30
#define SPACE_BETWEEN 50



class UserParamsComponent : public Component, private TextEditor::Listener, public Button::Listener
{
public:
	//==============================================================================
	UserParamsComponent();
	~UserParamsComponent();

	void paint(Graphics&) override;
	void resized() override;
	void buttonClicked(Button* button) override;
	void ThemeChanged();
	bool isEmailValid(const std::string &email);

private:
	TextEditor firstNameTextEditor, lastNameTextEditor, userNameTextEditor, emailTextEditor, dateOfBirthTextEditor, passwordTextEditor, passwordConfirmationTextEditor;
	Label firstNameLabel, lastNameLabel, userNameLabel, emailLabel, dateOfBirthLabel, passwordLabel, passwordConfirmationLabel;
	ComboBox languageComboBox;
	Label errorText;
	TextButton saveButton;
	Theme currentTheme;
	User user;
	CmdManager cmdManager;
	//ComboBox themeChoice;
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UserParamsComponent)
};


#endif  // USERPARAMSCOMPONENT_H_INCLUDED
