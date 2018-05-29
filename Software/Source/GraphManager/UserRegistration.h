/*
==============================================================================

UserRegistration.h
Created: 13 Jan 2018 2:36:43pm
Author:  Oreo

==============================================================================
*/


#ifndef USERREGISTRATION_H_INCLUDED
#define USERREGISTRATION_H_INCLUDED

#include "Theme.h"
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



class UserRegistration : public AComponent, private TextEditor::Listener, private Button::Listener
{
public:
	//==============================================================================
	UserRegistration(CmdManager & cmdManager);
	~UserRegistration();

private:
	void paint(Graphics&) override;
	void resized() override;
	void buttonClicked(Button* button) override;
	void ThemeChanged();
	bool isEmailValid(const std::string &email);
	bool isDateValid(const std::string &date);
	void signin(const User & user);

	TextEditor _firstNameTextEditor, _lastNameTextEditor, _userNameTextEditor, _emailTextEditor, _dateOfBirthTextEditor, _passwordTextEditor, _passwordConfirmationTextEditor;
	Label _firstNameLabel, _lastNameLabel, _userNameLabel, _emailLabel, _dateOfBirthLabel, _passwordLabel, _passwordConfirmationLabel;
	ComboBox _languageComboBox;
	Label _errorText;
	TextButton _saveButton;
	TextButton _cancelButton;
	static Theme _currentTheme;
	User _user;
	CmdManager &_cmdManager;
	//ComboBox themeChoice;
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UserRegistration)
};


#endif  // USERREGISTRATION_H_INCLUDED
