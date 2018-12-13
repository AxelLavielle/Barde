/*
  ==============================================================================

    UserParamPanel.cpp
    Created: 25 May 2018 6:46:37am
    Author:  Anthony

  ==============================================================================
*/

#include "UserParamsPanel.hh"

UserParamsPanel::UserParamsPanel() : _cmdManager(CmdManager::getInstance())
{
	GuiFactory::initMediumTitle("Editez vos informations", _titleLabel);
	addFlexItem(_titleLabel, 200, 30, FlexItem::AlignSelf::stretch, 1);

	GuiFactory::initLittleTitle("", _errorLabel);
	_errorLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));
	addFlexItem(_errorLabel, 500, 30, FlexItem::AlignSelf::center, 1);

	initTextBoxes();

	GuiFactory::initMediumTitle("", _emptyLabel1);
	addFlexItem(_emptyLabel1, 200, 15, FlexItem::AlignSelf::stretch, 1);

	GuiFactory::initButton("Confirmer", "Confirm", this, _confirmButton);
	addFlexItem(_confirmButton, TEXTBOX_MIN_WIDTH, 30, FlexItem::AlignSelf::stretch, 1);

	GuiFactory::initMediumTitle("", _emptyLabel2);
	addFlexItem(_emptyLabel2, 200, 20, FlexItem::AlignSelf::stretch, 1);

	initTextBoxesPassword();

	GuiFactory::initMediumTitle("", _emptyLabel3);
	addFlexItem(_emptyLabel3, 200, 15, FlexItem::AlignSelf::stretch, 1);

	GuiFactory::initButton("Changer le mot de passe", "Password", this, _passwordButton);
	addFlexItem(_passwordButton, TEXTBOX_MIN_WIDTH, 30, FlexItem::AlignSelf::stretch, 1);

	//GuiFactory::initButton("Cancel", "Cancel", this, _cancelButton);
	//addFlexItem(_cancelButton, TEXTBOX_MIN_WIDTH, TEXTBOX_MIN_HEIGHT, FlexItem::AlignSelf::stretch, 1);

	_flexBox = GuiFactory::createFlexBox(FlexBox::JustifyContent::center, FlexBox::AlignContent::center, FlexBox::AlignItems::stretch, FlexBox::Direction::column, _items, 500, 50);
}

void UserParamsPanel::refresh()
{
	initTextBoxes();
}

void UserParamsPanel::paint(Graphics & g)
{
	g.fillAll(Colour(Theme::getInstance().getBackgroundColor()));
}

void UserParamsPanel::initTextBoxes()
{
	_errorLabel.setLabelText("");
	try
	{
		_user = _cmdManager.getUserInfo();

	}
	catch (RestClientException &e)
	{
		_errorLabel.setLabelText("Connection error.");
	}

	GuiFactory::initLabeledTextBox("Pr\xc3\xa9nom", _user.getFirstName(), _firstNameTextBox);
	addFlexItem(_firstNameTextBox, TEXTBOX_MIN_WIDTH, TEXTBOX_MIN_HEIGHT, FlexItem::AlignSelf::stretch, 1);


	GuiFactory::initLabeledTextBox("Nom", _user.getLastName(), _lastNameTextBox);
	addFlexItem(_lastNameTextBox, TEXTBOX_MIN_WIDTH, TEXTBOX_MIN_HEIGHT, FlexItem::AlignSelf::stretch, 1);

	GuiFactory::initLabeledTextBox("Pseudonyme", _user.getUserName(), _userNameTextBox);
	addFlexItem(_userNameTextBox, TEXTBOX_MIN_WIDTH, TEXTBOX_MIN_HEIGHT, FlexItem::AlignSelf::stretch, 1);

	GuiFactory::initLabeledTextBox("Email", _user.getEmail(), _emailTextBox);
	addFlexItem(_emailTextBox, TEXTBOX_MIN_WIDTH, TEXTBOX_MIN_HEIGHT, FlexItem::AlignSelf::stretch, 1);

	std::string dateUser = "";
	if (_user.getDateOfBirth() != "") {
		dateUser = _user.getDayOfBirth() + "/" + _user.getMonthOfBirth() + "/" + _user.getYearOfBirth();
	}
	GuiFactory::initLabeledTextBox("Date de naissance", dateUser, _dateOfBirthTextBox);
	addFlexItem(_dateOfBirthTextBox, TEXTBOX_MIN_WIDTH, TEXTBOX_MIN_HEIGHT, FlexItem::AlignSelf::stretch, 1);
}

void UserParamsPanel::initTextBoxesPassword()
{
	GuiFactory::initLabeledTextBoxPassword("Ancien mot de passe", "", (juce_wchar)0x2022, _oldPasswordTextBox);
	addFlexItem(_oldPasswordTextBox, TEXTBOX_MIN_WIDTH, TEXTBOX_MIN_HEIGHT, FlexItem::AlignSelf::stretch, 1);

	GuiFactory::initLabeledTextBoxPassword("Nouveau mot de passe", "", (juce_wchar)0x2022, _passwordTextBox);
	addFlexItem(_passwordTextBox, TEXTBOX_MIN_WIDTH, TEXTBOX_MIN_HEIGHT, FlexItem::AlignSelf::stretch, 1);

	GuiFactory::initLabeledTextBoxPassword("Nouveau mot de passe confirmation", "", (juce_wchar)0x2022, _passwordConfirmationTextBox);
	addFlexItem(_passwordConfirmationTextBox, TEXTBOX_MIN_WIDTH, TEXTBOX_MIN_HEIGHT, FlexItem::AlignSelf::stretch, 1);
}

void UserParamsPanel::applyTheme()
{


	LabeledTextBox		_emailTextBox;
	LabeledTextBox		_dateOfBirthTextBox;
	LabeledTextBox		_passwordTextBox;
	LabeledTextBox		_passwordConfirmationTextBox;



	_titleLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getFontColor()));
	_errorLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));



	_confirmButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	_confirmButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));
	_confirmButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
	
	_cancelButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	_cancelButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
	_cancelButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));


	_firstNameTextBox.setColour(TextEditor::backgroundColourId, Colour(Colours::red));
	_firstNameTextBox.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_firstNameTextBox.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonColor()));
	_firstNameTextBox.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getFontColor()));
	_firstNameTextBox.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getFontColor()));

	_lastNameTextBox.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getBackgroundColor()));
	_lastNameTextBox.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_lastNameTextBox.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonColor()));
	_lastNameTextBox.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getFontColor()));
	_lastNameTextBox.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getFontColor()));


	_userNameTextBox.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getBackgroundColor()));
	_userNameTextBox.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_userNameTextBox.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonColor()));
	_userNameTextBox.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getFontColor()));
	_userNameTextBox.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getFontColor()));

	_emailTextBox.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getBackgroundColor()));
	_emailTextBox.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_emailTextBox.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonColor()));
	_emailTextBox.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getFontColor()));
	_emailTextBox.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getFontColor()));

	_dateOfBirthTextBox.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getBackgroundColor()));
	_dateOfBirthTextBox.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_dateOfBirthTextBox.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonColor()));
	_dateOfBirthTextBox.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getFontColor()));
	_dateOfBirthTextBox.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getFontColor()));

	_oldPasswordTextBox.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getBackgroundColor()));
	_oldPasswordTextBox.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_oldPasswordTextBox.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonColor()));
	_oldPasswordTextBox.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getFontColor()));
	_oldPasswordTextBox.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getFontColor()));
	
	_passwordTextBox.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getBackgroundColor()));
	_passwordTextBox.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordTextBox.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordTextBox.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getFontColor()));
	_passwordTextBox.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getFontColor()));

	_passwordConfirmationTextBox.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getBackgroundColor()));
	_passwordConfirmationTextBox.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordConfirmationTextBox.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordConfirmationTextBox.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getFontColor()));
	_passwordConfirmationTextBox.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getFontColor()));

}



bool UserParamsPanel::updateUser()
{
	_errorLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));
	if (!(StringChecker::isNameValid(_firstNameTextBox.getText())))
	{
		_errorLabel.setLabelText("Pr\xc3\xa9nom non valide.");
		return false;
	}


	if (!(StringChecker::isNameValid(_lastNameTextBox.getText())))
	{
		_errorLabel.setLabelText("Nom non valide.");
		return false;
	}

	if (!(StringChecker::isUserNameValid(_userNameTextBox.getText())))
	{
		_errorLabel.setLabelText("Pseudonyme non valide.");
		return false;
	}

	if (StringChecker::isEmailValid(_emailTextBox.getText()) == false)
	{
		_errorLabel.setLabelText("Email non valide.");
		return false;
	}

	if (!(StringChecker::isDateValid(_dateOfBirthTextBox.getText())))
	{
		_errorLabel.setText("Date non valide", dontSendNotification);
		return false;
	}

	if (!(StringChecker::isDateInPast(_dateOfBirthTextBox.getText())))
	{
		_errorLabel.setText("La date ne doit pas etre dans le futur.", dontSendNotification);
		return false;
	}

	_user.setEmail(_emailTextBox.getText());
	std::string date = _dateOfBirthTextBox.getText();
	_user.setDayOfBirth(date.substr(0, 2));
	_user.setMonthOfBirth(date.substr(3, 2));
	_user.setYearOfBirth(date.substr(6, 4));
	_user.setMonthOfBirth(_user.getMonthOfBirth());
	_user.setYearOfBirth(_user.getYearOfBirth());
	_user.setFirstName(_firstNameTextBox.getText());
	_user.setLastName(_lastNameTextBox.getText());
	_user.setUserName(_userNameTextBox.getText());
	try
	{
		if (_cmdManager.editUserInfo(_user) == false)
		{
			if (_cmdManager.getResponseMsg() !="")
				_errorLabel.setLabelText("API error : " + _cmdManager.getResponseMsg());
			else
				_errorLabel.setLabelText("Connection error.");
			return false;
		}

	}
	catch (RestClientException &e)
	{
		_errorLabel.setLabelText("Erreur de connection, merci de vous reconnecter.");
		return false;
	}
	return true;
}

bool UserParamsPanel::updatePassword()
{
	_errorLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));
	
	if (_passwordTextBox.getText() == "" || _passwordConfirmationTextBox.getText() == "" || _oldPasswordTextBox.getText() == "")
	{
		_errorLabel.setLabelText("Mot de passe invalide.");
		return false;
	}

	if (_passwordTextBox.getText() != _passwordConfirmationTextBox.getText())
	{
		_errorLabel.setLabelText("Les mots de passes ne sont pas identiques");
		return false;
	}

	String oldPassword = _oldPasswordTextBox.getText();
	String password = _passwordTextBox.getText();

	if (!(StringChecker::isPasswordLongEnough(password.toStdString())))
	{
		_errorLabel.setText("Password should be at least 8 characters long", dontSendNotification);
		return false;
	}

	if (!(StringChecker::containsLowercase(password.toStdString())))
	{
		_errorLabel.setText("Password should contain at least one lowercase letter", dontSendNotification);
		return false;
	}

	if (!(StringChecker::containsUppercase(password.toStdString())))
	{
		_errorLabel.setText("Password should contain at least one uppercase letter", dontSendNotification);
		return false;
	}

	if (!(StringChecker::containsNumber(password.toStdString())))
	{
		_errorLabel.setText("Password should contain at least one number", dontSendNotification);
		return false;
	}

	if (!(StringChecker::containsSpecialChar(password.toStdString())))
	{
		_errorLabel.setText("Password should contain at least one special character", dontSendNotification);
		return false;
	}

	try
	{
		if (_cmdManager.editUserPassword(oldPassword.toStdString(), password.toStdString()) == false)
		{
			if (_cmdManager.getResponseMsg() != "")
				_errorLabel.setLabelText("API error : " + _cmdManager.getResponseMsg());
			else
				_errorLabel.setLabelText("Connection error.");
			return false;
		}

	}
	catch (RestClientException &e)
	{
		_errorLabel.setLabelText("Connection error, please reconnect yourself.");
		return false;
	}
	return true;
}

void UserParamsPanel::buttonClicked(Button * button)
{
	if (button->getName() == "Confirm")
	{
		_errorLabel.setLabelText("");
		if (updateUser())
		{
			//TO DO manage theme
			_errorLabel.setColour(Label::textColourId, Colours::black);
			initTextBoxes();
			_errorLabel.setLabelText("Informations mises a jour.");
		}
	}
	else if (button->getName() == "Cancel")
	{
		changeView("Player");
	}
	else if (button->getName() == "Password")
	{
		_errorLabel.setLabelText("");
		if (updatePassword())
		{
			//TO DO manage theme
			_errorLabel.setColour(Label::textColourId, Colours::black);
			initTextBoxes();
			_errorLabel.setLabelText("Mot de passe mis a jour.");
		}
	}
}
