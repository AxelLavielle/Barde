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
	GuiFactory::initMediumTitle("Edit your informations", _titleLabel);
	addFlexItem(_titleLabel, 200, 30, FlexItem::AlignSelf::stretch, 1);

	GuiFactory::initLittleTitle("", _errorLabel);
	_errorLabel.setColour(Label::textColourId, Colours::red);
	addFlexItem(_errorLabel, 200, 30, FlexItem::AlignSelf::center, 1);

	initTextBoxes();

	_cancelButton.setButtonText("Cancel");
	_cancelButton.setName("Cancel");
	_cancelButton.addListener(this);
	addFlexItem(_cancelButton, 100, 20, FlexItem::AlignSelf::flexEnd, 1);

	_confirmButton.setButtonText("Confirm");
	_confirmButton.setName("Confirm");
	_confirmButton.addListener(this);
	addFlexItem(_confirmButton, 100, 20, FlexItem::AlignSelf::flexEnd, 1);

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

	GuiFactory::initLabeledTextBox("Firstname", _user.getFirstName(), _firstNameTextBox);
	addFlexItem(_firstNameTextBox, TEXTBOX_MIN_WIDTH, TEXTBOX_MIN_HEIGHT, FlexItem::AlignSelf::stretch, 1);

	GuiFactory::initLabeledTextBox("Lastname", _user.getLastName(), _lastNameTextBox);
	addFlexItem(_lastNameTextBox, TEXTBOX_MIN_WIDTH, TEXTBOX_MIN_HEIGHT, FlexItem::AlignSelf::stretch, 1);

	GuiFactory::initLabeledTextBox("Username", _user.getUserName(), _userNameTextBox);
	addFlexItem(_userNameTextBox, TEXTBOX_MIN_WIDTH, TEXTBOX_MIN_HEIGHT, FlexItem::AlignSelf::stretch, 1);

	GuiFactory::initLabeledTextBox("Email", _user.getEmail(), _emailTextBox);
	addFlexItem(_emailTextBox, TEXTBOX_MIN_WIDTH, TEXTBOX_MIN_HEIGHT, FlexItem::AlignSelf::stretch, 1);


	int d = stoi(_user.getMonthOfBirth());
	if (d == 1)
		d = 12;
	else
		d = d - 1;

	std::string dateUser = _user.getDayOfBirth() + "/" + std::to_string(d) + "/" + _user.getYearOfBirth();
	GuiFactory::initLabeledTextBox("Date of birth", dateUser, _dateOfBirthTextBox);
	addFlexItem(_dateOfBirthTextBox, TEXTBOX_MIN_WIDTH, TEXTBOX_MIN_HEIGHT, FlexItem::AlignSelf::stretch, 1);

	GuiFactory::initLabeledTextBoxPassword("New password (optional)", (juce_wchar)0x2022, _passwordTextBox);
	addFlexItem(_passwordTextBox, TEXTBOX_MIN_WIDTH, TEXTBOX_MIN_HEIGHT, FlexItem::AlignSelf::stretch, 1);

	GuiFactory::initLabeledTextBoxPassword("New password confirmation (optional)", (juce_wchar)0x2022, _passwordConfirmationTextBox);
	addFlexItem(_passwordConfirmationTextBox, TEXTBOX_MIN_WIDTH, TEXTBOX_MIN_HEIGHT, FlexItem::AlignSelf::stretch, 1);
}

bool UserParamsPanel::updateUser()
{

	if (!(StringChecker::isNameValid(_firstNameTextBox.getText())))
	{
		_errorLabel.setLabelText("Invalid firstName.");
		return false;
	}


	if (!(StringChecker::isNameValid(_lastNameTextBox.getText())))
	{
		_errorLabel.setLabelText("Invalid lastName.");
		return false;
	}

	if (!(StringChecker::isUserNameValid(_userNameTextBox.getText())))
	{
		_errorLabel.setLabelText("Invalid userName.");
		return false;
	}

	if (StringChecker::isEmailValid(_emailTextBox.getText()) == false)
	{
		_errorLabel.setLabelText("Invalid email.");
		return false;
	}

	if (!(StringChecker::isDateValid(_dateOfBirthTextBox.getText())))
	{
		_errorLabel.setText("Error: Date is not valid", dontSendNotification);
		return false;
	}

	if (!(StringChecker::isDateInPast(_dateOfBirthTextBox.getText())))
	{
		_errorLabel.setText("Error: Date should not be in the future", dontSendNotification);
		return false;
	}


	if (_passwordTextBox.getText() != _passwordConfirmationTextBox.getText())
	{
		_errorLabel.setLabelText("Error passwords don't match");
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
		if (_cmdManager.editUserInfo(_user, _passwordTextBox.getText()) == false)
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
			_errorLabel.setLabelText("Informations updated.");
		}
	}
	else if (button->getName() == "Cancel")
	{
		changeView("Player");
	}
}
