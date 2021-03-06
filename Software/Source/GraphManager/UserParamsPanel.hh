/*
  ==============================================================================

    UserParamPanel.h
    Created: 25 May 2018 6:46:36am
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include <vector>
#include "../Factories/GuiFactory.hh"
#include "../ViewManager/FlexView.hh"
#include "../Utils/StringChecker.hh"
#include "../User.hh"
#include "../CmdManager.hh"
#include "LabeledTextBox.hh"


#define TEXTBOX_MIN_WIDTH 400
#define TEXTBOX_MIN_HEIGHT 50

class UserParamsPanel : public FlexView, private Button::Listener
{
public:
	UserParamsPanel();
	void refresh() override;

private:
	void paint(Graphics & g) override;
	void buttonClicked(Button * button) override;
	void initTextBoxes();
	bool updateUser();
	void applyTheme();

	SimpleLabel			_titleLabel;
	SimpleLabel			_errorLabel;
	LabeledTextBox		_firstNameTextBox;
	LabeledTextBox		_lastNameTextBox;
	LabeledTextBox		_userNameTextBox;
	LabeledTextBox		_emailTextBox;
	LabeledTextBox		_dateOfBirthTextBox;
	LabeledTextBox		_passwordTextBox;
	LabeledTextBox		_passwordConfirmationTextBox;
	TextButton			_confirmButton;
	TextButton			_cancelButton;

	CmdManager			&_cmdManager;

	User				_user;
};