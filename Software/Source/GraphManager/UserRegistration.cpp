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
	this->_currentTheme = parseTheme("../Themes/Dark");

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
	_saveButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	_saveButton.addListener(this);

	addAndMakeVisible(_cancelButton);
	_cancelButton.setButtonText("Cancel");
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
	_firstNameTextEditor.setColour(TextEditor::backgroundColourId, Colour(this->_currentTheme.getBackgroundColor()));
	_firstNameTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(this->_currentTheme.getButtonColor()));
	_firstNameTextEditor.setColour(TextEditor::highlightColourId, Colour(this->_currentTheme.getButtonColor()));
	_firstNameTextEditor.setColour(TextEditor::textColourId, Colour(this->_currentTheme.getFontColor()));
	_firstNameTextEditor.setColour(TextEditor::outlineColourId, Colour(this->_currentTheme.getFontColor()));
	_firstNameTextEditor.clear();
	_firstNameTextEditor.setText(tmp);

	tmp = _lastNameTextEditor.getText();
	_lastNameTextEditor.setColour(TextEditor::backgroundColourId, Colour(this->_currentTheme.getBackgroundColor()));
	_lastNameTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(this->_currentTheme.getButtonColor()));
	_lastNameTextEditor.setColour(TextEditor::highlightColourId, Colour(this->_currentTheme.getButtonColor()));
	_lastNameTextEditor.setColour(TextEditor::textColourId, Colour(this->_currentTheme.getFontColor()));
	_lastNameTextEditor.setColour(TextEditor::outlineColourId, Colour(this->_currentTheme.getFontColor()));
	_lastNameTextEditor.clear();
	_lastNameTextEditor.setText(tmp);

	tmp = _userNameTextEditor.getText();
	_userNameTextEditor.setColour(TextEditor::backgroundColourId, Colour(this->_currentTheme.getBackgroundColor()));
	_userNameTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(this->_currentTheme.getButtonColor()));
	_userNameTextEditor.setColour(TextEditor::highlightColourId, Colour(this->_currentTheme.getButtonColor()));
	_userNameTextEditor.setColour(TextEditor::textColourId, Colour(this->_currentTheme.getFontColor()));
	_userNameTextEditor.setColour(TextEditor::outlineColourId, Colour(this->_currentTheme.getFontColor()));
	_userNameTextEditor.clear();
	_userNameTextEditor.setText(tmp);

	tmp = _emailTextEditor.getText();
	_emailTextEditor.setColour(TextEditor::backgroundColourId, Colour(this->_currentTheme.getBackgroundColor()));
	_emailTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(this->_currentTheme.getButtonColor()));
	_emailTextEditor.setColour(TextEditor::highlightColourId, Colour(this->_currentTheme.getButtonColor()));
	_emailTextEditor.setColour(TextEditor::textColourId, Colour(this->_currentTheme.getFontColor()));
	_emailTextEditor.setColour(TextEditor::outlineColourId, Colour(this->_currentTheme.getFontColor()));
	_emailTextEditor.clear();
	_emailTextEditor.setText(tmp);


	tmp = _dateOfBirthTextEditor.getText();
	_dateOfBirthTextEditor.setColour(TextEditor::backgroundColourId, Colour(this->_currentTheme.getBackgroundColor()));
	_dateOfBirthTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(this->_currentTheme.getButtonColor()));
	_dateOfBirthTextEditor.setColour(TextEditor::highlightColourId, Colour(this->_currentTheme.getButtonColor()));
	_dateOfBirthTextEditor.setColour(TextEditor::textColourId, Colour(this->_currentTheme.getFontColor()));
	_dateOfBirthTextEditor.setColour(TextEditor::outlineColourId, Colour(this->_currentTheme.getFontColor()));
	_dateOfBirthTextEditor.clear();
	_dateOfBirthTextEditor.setText(tmp);


	tmp = _passwordTextEditor.getText();
	_passwordTextEditor.setColour(TextEditor::backgroundColourId, Colour(this->_currentTheme.getBackgroundColor()));
	_passwordTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(this->_currentTheme.getButtonColor()));
	_passwordTextEditor.setColour(TextEditor::highlightColourId, Colour(this->_currentTheme.getButtonColor()));
	_passwordTextEditor.setColour(TextEditor::textColourId, Colour(this->_currentTheme.getFontColor()));
	_passwordTextEditor.setColour(TextEditor::outlineColourId, Colour(this->_currentTheme.getFontColor()));
	_passwordTextEditor.clear();
	_passwordTextEditor.setText(tmp);


	tmp = _passwordConfirmationTextEditor.getText();
	_passwordConfirmationTextEditor.setColour(TextEditor::backgroundColourId, Colour(this->_currentTheme.getBackgroundColor()));
	_passwordConfirmationTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(this->_currentTheme.getButtonColor()));
	_passwordConfirmationTextEditor.setColour(TextEditor::highlightColourId, Colour(this->_currentTheme.getButtonColor()));
	_passwordConfirmationTextEditor.setColour(TextEditor::textColourId, Colour(this->_currentTheme.getFontColor()));
	_passwordConfirmationTextEditor.setColour(TextEditor::outlineColourId, Colour(this->_currentTheme.getFontColor()));
	_passwordConfirmationTextEditor.clear();
	_passwordConfirmationTextEditor.setText(tmp);

	_firstNameLabel.setColour(Label::textColourId, Colour(this->_currentTheme.getButtonColor()));
	_lastNameLabel.setColour(Label::textColourId, Colour(this->_currentTheme.getButtonColor()));
	_userNameLabel.setColour(Label::textColourId, Colour(this->_currentTheme.getButtonColor()));
	_emailLabel.setColour(Label::textColourId, Colour(this->_currentTheme.getButtonColor()));
	_dateOfBirthLabel.setColour(Label::textColourId, Colour(this->_currentTheme.getButtonColor()));
	_passwordLabel.setColour(Label::textColourId, Colour(this->_currentTheme.getButtonColor()));
	_passwordConfirmationLabel.setColour(Label::textColourId, Colour(this->_currentTheme.getButtonColor()));

	_saveButton.setColour(TextButton::buttonColourId, Colour(this->_currentTheme.getButtonColor()));
	_saveButton.setColour(TextButton::textColourOnId, Colour(this->_currentTheme.getButtonFontColor()));
	_cancelButton.setColour(TextButton::buttonColourId, Colour(this->_currentTheme.getButtonColor()));
	_cancelButton.setColour(TextButton::textColourOnId, Colour(this->_currentTheme.getButtonFontColor()));
	this->repaint();
}

void UserRegistration::buttonClicked(Button* button)
{
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
	username = _userNameTextEditor.getText();
	email = _emailTextEditor.getText();
	bool a = isEmailValid(email.toStdString());
	if (!a)
	{
		_errorText.setText("Error: the email is not valid", dontSendNotification);
		return;
	}
	dateofbirth = _dateOfBirthTextEditor.getText();
	password = _passwordTextEditor.getText();
	confirmpassword = _passwordConfirmationTextEditor.getText();
	if (password != confirmpassword)
	{
		_errorText.setText("Error passwords don't match", dontSendNotification);
		return;
	}

	test.setEmail(email.toStdString());
	test.setDayOfBirth("25");
	test.setMonthOfBirth("11");
	test.setYearOfBirth("1996");
	test.setFirstName(firstName.toStdString());
	test.setLastName(lastName.toStdString());
	test.setUserName(username.toStdString());
	_cmdManager.signUp(test, password.toStdString());
	std::cout << "username : " << username << " email: " << email << "date of birth: " << dateofbirth << "password: " << password << " confirm password :" << confirmpassword << std::endl;
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
	g.fillAll(Colour(this->_currentTheme.getBackgroundColor()));
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
