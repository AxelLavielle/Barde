/*
==============================================================================

UserParamsComponent.cpp
Created: 13 Jan 2018 2:36:43pm
Author:  Oreo

==============================================================================
*/

#include "UserParamsComponent.h"
#include "MainComponent.h"
#include <sstream> 
#include <string> 

//==============================================================================
UserParamsComponent::UserParamsComponent()
{
	int x = getParentWidth();
	int y = getParentHeight();

	setSize(getParentWidth(), getParentHeight() - 10);
	_currentTheme = parseTheme("../Themes/Dark");

	//Connect to server
	_cmdManager.connectToServer();

	//login
	//_cmdManager.login("micha@barde.io", "titiletutu");
	_cmdManager.login("arnaud.p@outlook.fr", "arnaud");

	//get User info
	_user = _cmdManager.getUserInfo();

	addAndMakeVisible(_firstNameTextEditor);
	_firstNameTextEditor.setText(_user.getFirstName());
	_firstNameTextEditor.setText(_user.getFirstName());

	addAndMakeVisible(_lastNameTextEditor);
	_lastNameTextEditor.setText(_user.getLastName());

	addAndMakeVisible(_userNameTextEditor);
	_userNameTextEditor.setText(_user.getUserName());

	addAndMakeVisible(_emailTextEditor);
	_emailTextEditor.setText(_user.getEmail());

	addAndMakeVisible(_dateOfBirthEditor);
	_dateOfBirthEditor.setText(_user.getDateOfBirth());
	
	addAndMakeVisible(_passwordTextEditor);
	_passwordTextEditor.setText("");
	_passwordTextEditor.setPasswordCharacter((juce_wchar)0x2022);//To replace chars with rounds

														 /*addAndMakeVisible(comboBox);
														 comboBox.setBounds(100, 85, 200, 24);
														 comboBox.setEditableText(true);
														 comboBox.setJustificationType(Justification::centred);*/

	addAndMakeVisible(_passwordConfirmationTextEditor);
	_passwordConfirmationTextEditor.setText("");
	_passwordConfirmationTextEditor.setPasswordCharacter((juce_wchar)0x2022);//To replace chars with rounds

														 /*addAndMakeVisible(comboBox);
														 comboBox.setBounds(100, 85, 200, 24);
														 comboBox.setEditableText(true);
														 comboBox.setJustificationType(Justification::centred);*/


	addAndMakeVisible(_firstNameLabel);
	_firstNameLabel.setText("FirstName:", dontSendNotification);
	_firstNameLabel.attachToComponent(&_firstNameTextEditor, true);
	_firstNameLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_lastNameLabel);
	_lastNameLabel.setText("LastName:", dontSendNotification);
	_lastNameLabel.attachToComponent(&_lastNameTextEditor, true);
	_lastNameLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_userNameLabel);
	_userNameLabel.setText("UserName:", dontSendNotification);
	_userNameLabel.attachToComponent(&_userNameTextEditor, true);
	_userNameLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_emailLabel);
	_emailLabel.setText("Email:", dontSendNotification);
	_emailLabel.attachToComponent(&_emailTextEditor, true);
	_emailLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_dateOfBirthLabel);
	_dateOfBirthLabel.setText("Date of Birth:", dontSendNotification);
	_dateOfBirthLabel.attachToComponent(&_dateOfBirthEditor, true);
	_emailLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_passwordLabel);
	_passwordLabel.setText("Password:", dontSendNotification);
	_passwordLabel.attachToComponent(&_passwordTextEditor, true);
	_passwordLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_passwordConfirmationLabel);
	_passwordConfirmationLabel.setText("Confirm password:", dontSendNotification);
	_passwordConfirmationLabel.attachToComponent(&_passwordConfirmationTextEditor, true);
	_passwordConfirmationLabel.setJustificationType(Justification::right);

	//textEditor1.addListener(this);
	//textEditor2.addListener(this);

	addAndMakeVisible(_errorText);
	_errorText.setText("", juce::NotificationType::dontSendNotification);
	_errorText.setColour(Label::textColourId, Colours::red);
	_errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);

	addAndMakeVisible(_saveButton);
	_saveButton.setButtonText("Save modifications");
	_saveButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	_saveButton.addListener(this);

	addAndMakeVisible(_backButton);
	_backButton.setName("Back");
	_backButton.setButtonText("Quit");
	_backButton.setBounds((x / 2) - (BOX_WIDTH / 2), y - 400, BOX_WIDTH, BOX_HEIGHT);
	_backButton.addListener(this);

	/*
	addAndMakeVisible(languageComboBox);
	languageComboBox.setBounds(10, 85, 200, 24);
	languageComboBox.setEditableText(true);
	languageComboBox.setJustificationType(Justification::centred);

	languageComboBox.addItem("English", 1);
	languageComboBox.addItem("French", 2);

	languageComboBox.setSelectedId(1);*/


	ThemeChanged();


}

void UserParamsComponent::ThemeChanged()
{
	String tmp = _firstNameTextEditor.getText();
	_firstNameTextEditor.setColour(TextEditor::backgroundColourId, Colour(_currentTheme.getBackgroundColor()));
	_firstNameTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(_currentTheme.getButtonColor()));
	_firstNameTextEditor.setColour(TextEditor::highlightColourId, Colour(_currentTheme.getButtonColor()));
	_firstNameTextEditor.setColour(TextEditor::textColourId, Colour(_currentTheme.getFontColor()));
	_firstNameTextEditor.setColour(TextEditor::outlineColourId, Colour(_currentTheme.getFontColor()));
	_firstNameTextEditor.clear();
	_firstNameTextEditor.setText(tmp);

	tmp = _lastNameTextEditor.getText();
	_lastNameTextEditor.setColour(TextEditor::backgroundColourId, Colour(_currentTheme.getBackgroundColor()));
	_lastNameTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(_currentTheme.getButtonColor()));
	_lastNameTextEditor.setColour(TextEditor::highlightColourId, Colour(_currentTheme.getButtonColor()));
	_lastNameTextEditor.setColour(TextEditor::textColourId, Colour(_currentTheme.getFontColor()));
	_lastNameTextEditor.setColour(TextEditor::outlineColourId, Colour(_currentTheme.getFontColor()));
	_lastNameTextEditor.clear();
	_lastNameTextEditor.setText(tmp);

	tmp = _userNameTextEditor.getText();
	_userNameTextEditor.setColour(TextEditor::backgroundColourId, Colour(_currentTheme.getBackgroundColor()));
	_userNameTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(_currentTheme.getButtonColor()));
	_userNameTextEditor.setColour(TextEditor::highlightColourId, Colour(_currentTheme.getButtonColor()));
	_userNameTextEditor.setColour(TextEditor::textColourId, Colour(_currentTheme.getFontColor()));
	_userNameTextEditor.setColour(TextEditor::outlineColourId, Colour(_currentTheme.getFontColor()));
	_userNameTextEditor.clear();
	_userNameTextEditor.setText(tmp);

	tmp = _emailTextEditor.getText();
	_emailTextEditor.setColour(TextEditor::backgroundColourId, Colour(_currentTheme.getBackgroundColor()));
	_emailTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(_currentTheme.getButtonColor()));
	_emailTextEditor.setColour(TextEditor::highlightColourId, Colour(_currentTheme.getButtonColor()));
	_emailTextEditor.setColour(TextEditor::textColourId, Colour(_currentTheme.getFontColor()));
	_emailTextEditor.setColour(TextEditor::outlineColourId, Colour(_currentTheme.getFontColor()));
	_emailTextEditor.clear();
	_emailTextEditor.setText(tmp);


	tmp = _dateOfBirthEditor.getText();
	_dateOfBirthEditor.setColour(TextEditor::backgroundColourId, Colour(_currentTheme.getBackgroundColor()));
	_dateOfBirthEditor.setColour(TextEditor::focusedOutlineColourId, Colour(_currentTheme.getButtonColor()));
	_dateOfBirthEditor.setColour(TextEditor::highlightColourId, Colour(_currentTheme.getButtonColor()));
	_dateOfBirthEditor.setColour(TextEditor::textColourId, Colour(_currentTheme.getFontColor()));
	_dateOfBirthEditor.setColour(TextEditor::outlineColourId, Colour(_currentTheme.getFontColor()));
	_dateOfBirthEditor.clear();
	_dateOfBirthEditor.setText(tmp);


	tmp = _passwordTextEditor.getText();
	_passwordTextEditor.setColour(TextEditor::backgroundColourId, Colour(_currentTheme.getBackgroundColor()));
	_passwordTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(_currentTheme.getButtonColor()));
	_passwordTextEditor.setColour(TextEditor::highlightColourId, Colour(_currentTheme.getButtonColor()));
	_passwordTextEditor.setColour(TextEditor::textColourId, Colour(_currentTheme.getFontColor()));
	_passwordTextEditor.setColour(TextEditor::outlineColourId, Colour(_currentTheme.getFontColor()));
	_passwordTextEditor.clear();
	_passwordTextEditor.setText(tmp);


	tmp = _passwordConfirmationTextEditor.getText();
	_passwordConfirmationTextEditor.setColour(TextEditor::backgroundColourId, Colour(_currentTheme.getBackgroundColor()));
	_passwordConfirmationTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(_currentTheme.getButtonColor()));
	_passwordConfirmationTextEditor.setColour(TextEditor::highlightColourId, Colour(_currentTheme.getButtonColor()));
	_passwordConfirmationTextEditor.setColour(TextEditor::textColourId, Colour(_currentTheme.getFontColor()));
	_passwordConfirmationTextEditor.setColour(TextEditor::outlineColourId, Colour(_currentTheme.getFontColor()));
	_passwordConfirmationTextEditor.clear();
	_passwordConfirmationTextEditor.setText(tmp);

	_firstNameLabel.setColour(Label::textColourId, Colour(_currentTheme.getButtonColor()));
	_lastNameLabel.setColour(Label::textColourId, Colour(_currentTheme.getButtonColor()));
	_userNameLabel.setColour(Label::textColourId, Colour(_currentTheme.getButtonColor()));
	_emailLabel.setColour(Label::textColourId, Colour(_currentTheme.getButtonColor()));
	_dateOfBirthLabel.setColour(Label::textColourId, Colour(_currentTheme.getButtonColor()));
	_passwordLabel.setColour(Label::textColourId, Colour(_currentTheme.getButtonColor()));
	_passwordConfirmationLabel.setColour(Label::textColourId, Colour(_currentTheme.getButtonColor()));

	_saveButton.setColour(TextButton::buttonColourId, Colour(_currentTheme.getButtonColor()));
	_saveButton.setColour(TextButton::textColourOnId, Colour(_currentTheme.getButtonFontColor()));
	this->repaint();
}

void UserParamsComponent::buttonClicked(Button* button)
{
	if (button->getName() == "Back")
	{
		changeView("Main");
		return;
	}

	//TODO Add API Connection to save changes instead of the code below

	String firstName;
	String lastName;
	String username;
	String email;
	String dateofbirth;
	String password;
	String confirmpassword;
	User test;
	
	(void)button;
	_errorText.setText("", dontSendNotification);
	firstName = _firstNameTextEditor.getText();
	lastName = _lastNameTextEditor.getText();
	username = _userNameTextEditor.getText();
	email = _emailTextEditor.getText();
	bool a = isEmailValid(email.toStdString());
	if (!a)
	{
		_errorText.setText("Error: the email is not valid", dontSendNotification);
		return;
	}
	dateofbirth = _dateOfBirthEditor.getText();
	password = _passwordTextEditor.getText();
	confirmpassword = _passwordConfirmationTextEditor.getText();
	if (password != confirmpassword)
		_errorText.setText("Error passwords don't match", dontSendNotification);
	std::cout << "username : " << username << " email: " << email << "date of birth: " << dateofbirth  << "password: " << password << " confirm password :" << confirmpassword << std::endl;
	test.setEmail(email.toStdString());
	test.setDayOfBirth("25");
	test.setMonthOfBirth("11");
	test.setYearOfBirth("1996");
	test.setFirstName(firstName.toStdString());
	test.setLastName(lastName.toStdString());
	test.setUserName(username.toStdString());
	_cmdManager.editUserInfo(_user);
}



bool UserParamsComponent::isEmailValid(const std::string &email)
{
	// define a regular expression
	const std::regex pattern
	("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

	// try to match the string with the regular expression
	return std::regex_match(email, pattern);
}


UserParamsComponent::~UserParamsComponent()
{
}

void UserParamsComponent::paint(Graphics& g)
{
	//g.setColour(Colours::white);
	g.fillAll(Colour(_currentTheme.getBackgroundColor()));
}

void UserParamsComponent::resized()
{
	int x = (getParentWidth());
	//	int y = (getParentHeight());

	_firstNameTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	_lastNameTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 2, BOX_WIDTH, BOX_HEIGHT);
	_userNameTextEditor.setBounds((x/2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);
	_emailTextEditor.setBounds((x/2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 4, BOX_WIDTH, BOX_HEIGHT);
	_dateOfBirthEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 5, BOX_WIDTH, BOX_HEIGHT);
	_passwordTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 6, BOX_WIDTH, BOX_HEIGHT);
	_passwordConfirmationTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 7, BOX_WIDTH, BOX_HEIGHT);
	_saveButton.setBounds((x/2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 8, BOX_WIDTH, BOX_HEIGHT);
	_errorText.setBounds((x/2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 9, BOX_WIDTH, BOX_HEIGHT);

	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
}
