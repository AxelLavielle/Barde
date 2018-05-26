/*
==============================================================================

UserRegistration.cpp
Created: 13 Jan 2018 2:36:43pm
Author:  Oreo

==============================================================================
*/

#include "UserRegistration.h"
#include "MainComponent.h"
#include <sstream> 
#include <string> 

//==============================================================================
UserRegistration::UserRegistration(CmdManager & cmdManager) : _cmdManager(cmdManager)
{

	int x = getParentWidth();
	int y = getParentHeight();

	setSize(getParentWidth(), getParentHeight() - 10);
	//this->_currentTheme = parseTheme("../Themes/Dark");

	//Connect to server
	cmdManager.connectToServer();

	addAndMakeVisible(_firstNameTextEditor);
	_firstNameTextEditor.setText(_user.getFirstName());
	_firstNameTextEditor.setText("");

	addAndMakeVisible(_lastNameTextEditor);
	_lastNameTextEditor.setText("");

	addAndMakeVisible(_userNameTextEditor);
	_userNameTextEditor.setText("");

	addAndMakeVisible(_emailTextEditor);
	_emailTextEditor.setText("");

	addAndMakeVisible(_dateOfBirthTextEditor);
	_dateOfBirthTextEditor.setText("");
	_dateOfBirthTextEditor.setTextToShowWhenEmpty("Format: dd/mm/yyyy", juce::Colours::aqua);

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
	_dateOfBirthLabel.attachToComponent(&_dateOfBirthTextEditor, true);
	_emailLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_passwordLabel);
	_passwordLabel.setText("Password:", dontSendNotification);
	_passwordLabel.attachToComponent(&_passwordTextEditor, true);
	_passwordLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_passwordConfirmationLabel);
	_passwordConfirmationLabel.setText("Confirm password:", dontSendNotification);
	_passwordConfirmationLabel.attachToComponent(&_passwordConfirmationTextEditor, true);
	_passwordConfirmationLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_errorText);
	_errorText.setText("", juce::NotificationType::dontSendNotification);
	_errorText.setColour(Label::textColourId, Colours::red);
	_errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);

	addAndMakeVisible(_saveButton);
	_saveButton.setButtonText("Sign in");
	_saveButton.setName("signin");
	_saveButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	_saveButton.addListener(this);

	addAndMakeVisible(_cancelButton);
	_cancelButton.setButtonText("Cancel");
	_cancelButton.setName("cancel");
	_cancelButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN + SPACE_BETWEEN + 100, BOX_WIDTH, BOX_HEIGHT);
	_cancelButton.addListener(this);


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

void UserRegistration::ThemeChanged()
{
	String tmp = _firstNameTextEditor.getText();
	_firstNameTextEditor.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getBackgroundColor()));
	_firstNameTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_firstNameTextEditor.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonColor()));
	_firstNameTextEditor.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getFontColor()));
	_firstNameTextEditor.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getFontColor()));
	_firstNameTextEditor.clear();
	_firstNameTextEditor.setText(tmp);

	tmp = _lastNameTextEditor.getText();
	_lastNameTextEditor.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getBackgroundColor()));
	_lastNameTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_lastNameTextEditor.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonColor()));
	_lastNameTextEditor.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getFontColor()));
	_lastNameTextEditor.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getFontColor()));
	_lastNameTextEditor.clear();
	_lastNameTextEditor.setText(tmp);

	tmp = _userNameTextEditor.getText();
	_userNameTextEditor.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getBackgroundColor()));
	_userNameTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_userNameTextEditor.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonColor()));
	_userNameTextEditor.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getFontColor()));
	_userNameTextEditor.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getFontColor()));
	_userNameTextEditor.clear();
	_userNameTextEditor.setText(tmp);

	tmp = _emailTextEditor.getText();
	_emailTextEditor.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getBackgroundColor()));
	_emailTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_emailTextEditor.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonColor()));
	_emailTextEditor.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getFontColor()));
	_emailTextEditor.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getFontColor()));
	_emailTextEditor.clear();
	_emailTextEditor.setText(tmp);


	tmp = _dateOfBirthTextEditor.getText();
	_dateOfBirthTextEditor.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getBackgroundColor()));
	_dateOfBirthTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_dateOfBirthTextEditor.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonColor()));
	_dateOfBirthTextEditor.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getFontColor()));
	_dateOfBirthTextEditor.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getFontColor()));
	_dateOfBirthTextEditor.clear();
	_dateOfBirthTextEditor.setText(tmp);


	tmp = _passwordTextEditor.getText();
	_passwordTextEditor.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getBackgroundColor()));
	_passwordTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordTextEditor.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordTextEditor.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getFontColor()));
	_passwordTextEditor.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getFontColor()));
	_passwordTextEditor.clear();
	_passwordTextEditor.setText(tmp);


	tmp = _passwordConfirmationTextEditor.getText();
	_passwordConfirmationTextEditor.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getBackgroundColor()));
	_passwordConfirmationTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordConfirmationTextEditor.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordConfirmationTextEditor.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getFontColor()));
	_passwordConfirmationTextEditor.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getFontColor()));
	_passwordConfirmationTextEditor.clear();
	_passwordConfirmationTextEditor.setText(tmp);

	_firstNameLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));
	_lastNameLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));
	_userNameLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));
	_emailLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));
	_dateOfBirthLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordConfirmationLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));

	_saveButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	_saveButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));
	_cancelButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	_cancelButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));
	this->repaint();
}

void UserRegistration::signin(const User & user)
{
	String password;
	String confirmPassword;

	_errorText.setText("", dontSendNotification);
	bool validEmail = isEmailValid(user.getEmail());
	if (!validEmail)
	{
		_errorText.setText("Error: the email is not valid", dontSendNotification);
		return;
	}
	password = _passwordTextEditor.getText();
	confirmPassword = _passwordConfirmationTextEditor.getText();
	if (password != confirmPassword)
	{
		_errorText.setText("Error passwords don't match", dontSendNotification);
		return;
	}
	if (_cmdManager.signUp(user, password.toStdString()))
	{
		_errorText.setText("Connexion error", dontSendNotification);
	}
}

void UserRegistration::buttonClicked(Button* button)
{
	if (button->getName() == "signin")
	{
		User user;

		user.setEmail(_emailTextEditor.getText().toStdString());
		user.setDayOfBirth("25");
		user.setMonthOfBirth("11");
		user.setYearOfBirth("1996");
		user.setFirstName(_firstNameTextEditor.getText().toStdString());
		user.setLastName(_lastNameLabel.getText().toStdString());
		user.setUserName(_userNameTextEditor.getText().toStdString());
		signin(user);
	}
	else if (button->getName() == "cancel")
	{
		changeView("Login");
	}
}



bool UserRegistration::isEmailValid(const std::string &email)
{
	// define a regular expression
	const std::regex pattern
	("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

	// try to match the string with the regular expression
	return std::regex_match(email, pattern);
}


UserRegistration::~UserRegistration()
{
}

void UserRegistration::paint(Graphics& g)
{
	//g.setColour(Colours::white);
	g.fillAll(Colour(Theme::getInstance().getBackgroundColor()));
}

void UserRegistration::resized()
{
	int x = (getParentWidth());
	//	int y = (getParentHeight());

	_firstNameTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	_lastNameTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 2, BOX_WIDTH, BOX_HEIGHT);
	_userNameTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);
	_emailTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 4, BOX_WIDTH, BOX_HEIGHT);
	_dateOfBirthTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 5, BOX_WIDTH, BOX_HEIGHT);
	_passwordTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 6, BOX_WIDTH, BOX_HEIGHT);
	_passwordConfirmationTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 7, BOX_WIDTH, BOX_HEIGHT);
	_saveButton.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 8, BOX_WIDTH, BOX_HEIGHT);
	_cancelButton.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 8 + 100, BOX_WIDTH, BOX_HEIGHT);
	_errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 9, BOX_WIDTH, BOX_HEIGHT);

	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
}
