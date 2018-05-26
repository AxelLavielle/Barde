/*
==============================================================================

UserParamsComponent.h
Created: 13 Jan 2018 2:36:43pm
Author:  Oreo

==============================================================================
*/


#ifndef USERPARAMSCOMPONENT_H_INCLUDED
#define USERPARAMSCOMPONENT_H_INCLUDED

#include <iostream>
#include <string>
#include <regex>

#include "../JuceLibraryCode/JuceHeader.h"
#include "Theme.h"
#include "../CmdManager.hh"
#include "../User.hh"
#include "AComponent.hh"
#include "BasicButton.hh"

#define LOGO_WIDTH 1024 / 3
#define LOGO_HEIGHT 927 / 3
#define BOX_WIDTH 400
#define BOX_HEIGHT 30
#define SPACE_BETWEEN 50

class UserParamsComponent : public AComponent, private TextEditor::Listener, private Button::Listener
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
	TextEditor			_firstNameTextEditor, _lastNameTextEditor, _userNameTextEditor, _emailTextEditor, _dateOfBirthEditor, _passwordTextEditor, _passwordConfirmationTextEditor;
	Label				_firstNameLabel, _lastNameLabel, _userNameLabel, _emailLabel, _dateOfBirthLabel, _passwordLabel, _passwordConfirmationLabel;
	ComboBox			_languageComboBox;
	Label				_errorText;
	TextButton			_saveButton;
	User				_user;
	CmdManager			_cmdManager;
	BasicButton			_backButton;
	//ComboBox themeChoice;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UserParamsComponent)
};


#endif  // USERPARAMSCOMPONENT_H_INCLUDED
