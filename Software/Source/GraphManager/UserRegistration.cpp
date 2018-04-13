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
UserRegistration::UserRegistration()
{

	int x = getParentWidth();
	int y = getParentHeight();

	setSize(getParentWidth(), getParentHeight() - 10);
	this->currentTheme = parseTheme("../Themes/Dark");

	//Connect to server
	cmdManager.connectToServer();

	addAndMakeVisible(firstNameTextEditor);
	firstNameTextEditor.setText(user.getFirstName());
	firstNameTextEditor.setText("");

	addAndMakeVisible(lastNameTextEditor);
	lastNameTextEditor.setText("");

	addAndMakeVisible(userNameTextEditor);
	userNameTextEditor.setText("");

	addAndMakeVisible(emailTextEditor);
	emailTextEditor.setText("");

	addAndMakeVisible(dateOfBirthTextEditor);
	dateOfBirthTextEditor.setText("");
	dateOfBirthTextEditor.setTextToShowWhenEmpty("Format: dd/mm/yyyy", juce::Colours::aqua);

	addAndMakeVisible(passwordTextEditor);
	passwordTextEditor.setText("");
	passwordTextEditor.setPasswordCharacter((juce_wchar)0x2022);//To replace chars with rounds

																/*addAndMakeVisible(comboBox);
																comboBox.setBounds(100, 85, 200, 24);
																comboBox.setEditableText(true);
																comboBox.setJustificationType(Justification::centred);*/

	addAndMakeVisible(passwordConfirmationTextEditor);
	passwordConfirmationTextEditor.setText("");
	passwordConfirmationTextEditor.setPasswordCharacter((juce_wchar)0x2022);//To replace chars with rounds

																			/*addAndMakeVisible(comboBox);
																			comboBox.setBounds(100, 85, 200, 24);
																			comboBox.setEditableText(true);
																			comboBox.setJustificationType(Justification::centred);*/


	addAndMakeVisible(firstNameLabel);
	firstNameLabel.setText("FirstName:", dontSendNotification);
	firstNameLabel.attachToComponent(&firstNameTextEditor, true);
	firstNameLabel.setJustificationType(Justification::right);

	addAndMakeVisible(lastNameLabel);
	lastNameLabel.setText("LastName:", dontSendNotification);
	lastNameLabel.attachToComponent(&lastNameTextEditor, true);
	lastNameLabel.setJustificationType(Justification::right);

	addAndMakeVisible(userNameLabel);
	userNameLabel.setText("UserName:", dontSendNotification);
	userNameLabel.attachToComponent(&userNameTextEditor, true);
	userNameLabel.setJustificationType(Justification::right);

	addAndMakeVisible(emailLabel);
	emailLabel.setText("Email:", dontSendNotification);
	emailLabel.attachToComponent(&emailTextEditor, true);
	emailLabel.setJustificationType(Justification::right);

	addAndMakeVisible(dateOfBirthLabel);
	dateOfBirthLabel.setText("Date of Birth:", dontSendNotification);
	dateOfBirthLabel.attachToComponent(&dateOfBirthTextEditor, true);
	emailLabel.setJustificationType(Justification::right);

	addAndMakeVisible(passwordLabel);
	passwordLabel.setText("Password:", dontSendNotification);
	passwordLabel.attachToComponent(&passwordTextEditor, true);
	passwordLabel.setJustificationType(Justification::right);

	addAndMakeVisible(passwordConfirmationLabel);
	passwordConfirmationLabel.setText("Confirm password:", dontSendNotification);
	passwordConfirmationLabel.attachToComponent(&passwordConfirmationTextEditor, true);
	passwordConfirmationLabel.setJustificationType(Justification::right);

	addAndMakeVisible(errorText);
	errorText.setText("", juce::NotificationType::dontSendNotification);
	errorText.setColour(Label::textColourId, Colours::red);
	errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);

	addAndMakeVisible(saveButton);
	saveButton.setButtonText("Sign up");
	saveButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	saveButton.addListener(this);


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
	String tmp = firstNameTextEditor.getText();
	firstNameTextEditor.setColour(TextEditor::backgroundColourId, Colour(this->currentTheme.getBackgroundColor()));
	firstNameTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(this->currentTheme.getButtonColor()));
	firstNameTextEditor.setColour(TextEditor::highlightColourId, Colour(this->currentTheme.getButtonColor()));
	firstNameTextEditor.setColour(TextEditor::textColourId, Colour(this->currentTheme.getFontColor()));
	firstNameTextEditor.setColour(TextEditor::outlineColourId, Colour(this->currentTheme.getFontColor()));
	firstNameTextEditor.clear();
	firstNameTextEditor.setText(tmp);

	tmp = lastNameTextEditor.getText();
	lastNameTextEditor.setColour(TextEditor::backgroundColourId, Colour(this->currentTheme.getBackgroundColor()));
	lastNameTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(this->currentTheme.getButtonColor()));
	lastNameTextEditor.setColour(TextEditor::highlightColourId, Colour(this->currentTheme.getButtonColor()));
	lastNameTextEditor.setColour(TextEditor::textColourId, Colour(this->currentTheme.getFontColor()));
	lastNameTextEditor.setColour(TextEditor::outlineColourId, Colour(this->currentTheme.getFontColor()));
	lastNameTextEditor.clear();
	lastNameTextEditor.setText(tmp);

	tmp = userNameTextEditor.getText();
	userNameTextEditor.setColour(TextEditor::backgroundColourId, Colour(this->currentTheme.getBackgroundColor()));
	userNameTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(this->currentTheme.getButtonColor()));
	userNameTextEditor.setColour(TextEditor::highlightColourId, Colour(this->currentTheme.getButtonColor()));
	userNameTextEditor.setColour(TextEditor::textColourId, Colour(this->currentTheme.getFontColor()));
	userNameTextEditor.setColour(TextEditor::outlineColourId, Colour(this->currentTheme.getFontColor()));
	userNameTextEditor.clear();
	userNameTextEditor.setText(tmp);

	tmp = emailTextEditor.getText();
	emailTextEditor.setColour(TextEditor::backgroundColourId, Colour(this->currentTheme.getBackgroundColor()));
	emailTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(this->currentTheme.getButtonColor()));
	emailTextEditor.setColour(TextEditor::highlightColourId, Colour(this->currentTheme.getButtonColor()));
	emailTextEditor.setColour(TextEditor::textColourId, Colour(this->currentTheme.getFontColor()));
	emailTextEditor.setColour(TextEditor::outlineColourId, Colour(this->currentTheme.getFontColor()));
	emailTextEditor.clear();
	emailTextEditor.setText(tmp);


	tmp = dateOfBirthTextEditor.getText();
	dateOfBirthTextEditor.setColour(TextEditor::backgroundColourId, Colour(this->currentTheme.getBackgroundColor()));
	dateOfBirthTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(this->currentTheme.getButtonColor()));
	dateOfBirthTextEditor.setColour(TextEditor::highlightColourId, Colour(this->currentTheme.getButtonColor()));
	dateOfBirthTextEditor.setColour(TextEditor::textColourId, Colour(this->currentTheme.getFontColor()));
	dateOfBirthTextEditor.setColour(TextEditor::outlineColourId, Colour(this->currentTheme.getFontColor()));
	dateOfBirthTextEditor.clear();
	dateOfBirthTextEditor.setText(tmp);


	tmp = passwordTextEditor.getText();
	passwordTextEditor.setColour(TextEditor::backgroundColourId, Colour(this->currentTheme.getBackgroundColor()));
	passwordTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(this->currentTheme.getButtonColor()));
	passwordTextEditor.setColour(TextEditor::highlightColourId, Colour(this->currentTheme.getButtonColor()));
	passwordTextEditor.setColour(TextEditor::textColourId, Colour(this->currentTheme.getFontColor()));
	passwordTextEditor.setColour(TextEditor::outlineColourId, Colour(this->currentTheme.getFontColor()));
	passwordTextEditor.clear();
	passwordTextEditor.setText(tmp);


	tmp = passwordConfirmationTextEditor.getText();
	passwordConfirmationTextEditor.setColour(TextEditor::backgroundColourId, Colour(this->currentTheme.getBackgroundColor()));
	passwordConfirmationTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(this->currentTheme.getButtonColor()));
	passwordConfirmationTextEditor.setColour(TextEditor::highlightColourId, Colour(this->currentTheme.getButtonColor()));
	passwordConfirmationTextEditor.setColour(TextEditor::textColourId, Colour(this->currentTheme.getFontColor()));
	passwordConfirmationTextEditor.setColour(TextEditor::outlineColourId, Colour(this->currentTheme.getFontColor()));
	passwordConfirmationTextEditor.clear();
	passwordConfirmationTextEditor.setText(tmp);

	firstNameLabel.setColour(Label::textColourId, Colour(this->currentTheme.getButtonColor()));
	lastNameLabel.setColour(Label::textColourId, Colour(this->currentTheme.getButtonColor()));
	userNameLabel.setColour(Label::textColourId, Colour(this->currentTheme.getButtonColor()));
	emailLabel.setColour(Label::textColourId, Colour(this->currentTheme.getButtonColor()));
	dateOfBirthLabel.setColour(Label::textColourId, Colour(this->currentTheme.getButtonColor()));
	passwordLabel.setColour(Label::textColourId, Colour(this->currentTheme.getButtonColor()));
	passwordConfirmationLabel.setColour(Label::textColourId, Colour(this->currentTheme.getButtonColor()));

	saveButton.setColour(TextButton::buttonColourId, Colour(this->currentTheme.getButtonColor()));
	saveButton.setColour(TextButton::textColourOnId, Colour(this->currentTheme.getButtonFontColor()));
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

	errorText.setText("", dontSendNotification);
	firstName = firstNameTextEditor.getText();
	username = userNameTextEditor.getText();
	email = emailTextEditor.getText();
	bool a = isEmailValid(email.toStdString());
	if (!a)
	{
		errorText.setText("Error: the email is not valid", dontSendNotification);
		return;
	}
	dateofbirth = dateOfBirthTextEditor.getText();
	password = passwordTextEditor.getText();
	confirmpassword = passwordConfirmationTextEditor.getText();
	if (password != confirmpassword)
	{
		errorText.setText("Error passwords don't match", dontSendNotification);
		return;
	}

	test.setEmail(email.toStdString());
	test.setDayOfBirth("25");
	test.setMonthOfBirth("11");
	test.setYearOfBirth("1996");
	test.setFirstName(firstName.toStdString());
	test.setLastName(lastName.toStdString());
	test.setUserName(username.toStdString());
	cmdManager.signUp(test, password.toStdString());
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
	g.fillAll(Colour(this->currentTheme.getBackgroundColor()));
}

void UserRegistration::resized()
{
	int x = (getParentWidth());
	int y = (getParentHeight());

	firstNameTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	lastNameTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 2, BOX_WIDTH, BOX_HEIGHT);
	userNameTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);
	emailTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 4, BOX_WIDTH, BOX_HEIGHT);
	dateOfBirthTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 5, BOX_WIDTH, BOX_HEIGHT);
	passwordTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 6, BOX_WIDTH, BOX_HEIGHT);
	passwordConfirmationTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 7, BOX_WIDTH, BOX_HEIGHT);
	saveButton.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 8, BOX_WIDTH, BOX_HEIGHT);
	errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 9, BOX_WIDTH, BOX_HEIGHT);

	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
}
