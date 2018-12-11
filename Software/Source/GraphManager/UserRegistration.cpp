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
	_dateOfBirthTextEditor.setTextToShowWhenEmpty("Format: dd/mm/yyyy", Colour(Theme::getInstance().getClueColor()));

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
	_firstNameLabel.setText(CharPointer_UTF8("Pr\xc3\xa9nom:"), dontSendNotification);
	_firstNameLabel.attachToComponent(&_firstNameTextEditor, true);
	_firstNameLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_lastNameLabel);
	_lastNameLabel.setText("Nom:", dontSendNotification);
	_lastNameLabel.attachToComponent(&_lastNameTextEditor, true);
	_lastNameLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_userNameLabel);
	_userNameLabel.setText("*Pseudonyme:", dontSendNotification);
	_userNameLabel.attachToComponent(&_userNameTextEditor, true);
	_userNameLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_emailLabel);
	_emailLabel.setText("*Email:", dontSendNotification);
	_emailLabel.attachToComponent(&_emailTextEditor, true);
	_emailLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_dateOfBirthLabel);
	_dateOfBirthLabel.setText("Date de naissance:", dontSendNotification);
	_dateOfBirthLabel.attachToComponent(&_dateOfBirthTextEditor, true);
	_emailLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_passwordLabel);
	_passwordLabel.setText("*Mot de passe:", dontSendNotification);
	_passwordLabel.attachToComponent(&_passwordTextEditor, true);
	_passwordLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_passwordConfirmationLabel);
	_passwordConfirmationLabel.setText("*Confirmation du mot de passe:", dontSendNotification);
	_passwordConfirmationLabel.attachToComponent(&_passwordConfirmationTextEditor, true);
	_passwordConfirmationLabel.setJustificationType(Justification::right);


	addAndMakeVisible(_firstNameError);
	_firstNameError.setText("", dontSendNotification);
	_firstNameError.attachToComponent(&_firstNameTextEditor, false);
	_firstNameError.setJustificationType(Justification::centredLeft);

	addAndMakeVisible(_lastNameError);
	_lastNameError.setText("", dontSendNotification);
	_lastNameError.attachToComponent(&_lastNameTextEditor, false);
	_lastNameError.setJustificationType(Justification::centredLeft);

	addAndMakeVisible(_userNameError);
	_userNameError.setText("", dontSendNotification);
	_userNameError.attachToComponent(&_userNameTextEditor, false);
	_userNameError.setJustificationType(Justification::centredLeft);

	addAndMakeVisible(_emailError);
	_emailError.setText("", dontSendNotification);
	_emailError.attachToComponent(&_emailTextEditor, false);
	_emailError.setJustificationType(Justification::centredLeft);

	addAndMakeVisible(_dateOfBirthError);
	_dateOfBirthError.setText("", dontSendNotification);
	_dateOfBirthError.attachToComponent(&_dateOfBirthTextEditor, false);
	_dateOfBirthError.setJustificationType(Justification::centredLeft);

	addAndMakeVisible(_passwordError);
	_passwordError.setText("", dontSendNotification);
	_passwordError.attachToComponent(&_passwordTextEditor, false);
	_passwordError.setJustificationType(Justification::centredLeft);

	addAndMakeVisible(_passwordConfirmationError);
	_passwordConfirmationError.setText("", dontSendNotification);
	_passwordConfirmationError.attachToComponent(&_passwordConfirmationTextEditor, false);
	_passwordConfirmationError.setJustificationType(Justification::centredLeft);


	addAndMakeVisible(_saveButton);
	_saveButton.setButtonText("S'inscrire");
	_saveButton.setName("signup");
	_saveButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	_saveButton.addListener(this);

	addAndMakeVisible(_cancelButton);
	_cancelButton.setButtonText("Annuler");
	_cancelButton.setName("cancel");
	_cancelButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN + SPACE_BETWEEN + 100, BOX_WIDTH, BOX_HEIGHT);
	_cancelButton.addListener(this);

	addAndMakeVisible(_errorText);
	_errorText.setText("", juce::NotificationType::dontSendNotification);
	_errorText.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));
	_errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, 1000, BOX_HEIGHT);


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

	_firstNameTextEditor.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	_firstNameTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_firstNameTextEditor.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_firstNameTextEditor.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_firstNameTextEditor.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_firstNameTextEditor.clear();
	_firstNameTextEditor.setText(tmp);

	tmp = _lastNameTextEditor.getText();
	_lastNameTextEditor.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	_lastNameTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_lastNameTextEditor.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_lastNameTextEditor.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_lastNameTextEditor.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_lastNameTextEditor.clear();
	_lastNameTextEditor.setText(tmp);

	tmp = _userNameTextEditor.getText();
	_userNameTextEditor.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	_userNameTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_userNameTextEditor.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_userNameTextEditor.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_userNameTextEditor.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_userNameTextEditor.clear();
	_userNameTextEditor.setText(tmp);

	tmp = _emailTextEditor.getText();
	_emailTextEditor.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	_emailTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_emailTextEditor.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_emailTextEditor.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_emailTextEditor.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_emailTextEditor.clear();
	_emailTextEditor.setText(tmp);


	tmp = _dateOfBirthTextEditor.getText();
	_dateOfBirthTextEditor.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	_dateOfBirthTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_dateOfBirthTextEditor.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_dateOfBirthTextEditor.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_dateOfBirthTextEditor.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_dateOfBirthTextEditor.clear();
	_dateOfBirthTextEditor.setText(tmp);


	tmp = _passwordTextEditor.getText();
	_passwordTextEditor.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordTextEditor.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_passwordTextEditor.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_passwordTextEditor.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_passwordTextEditor.clear();
	_passwordTextEditor.setText(tmp);


	tmp = _passwordConfirmationTextEditor.getText();
	_passwordConfirmationTextEditor.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordConfirmationTextEditor.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordConfirmationTextEditor.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_passwordConfirmationTextEditor.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_passwordConfirmationTextEditor.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_passwordConfirmationTextEditor.clear();
	_passwordConfirmationTextEditor.setText(tmp);

	_firstNameLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));
	_lastNameLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));
	_userNameLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));
	_emailLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));
	_dateOfBirthLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordConfirmationLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));

	_firstNameError.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));
	_lastNameError.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));
	_userNameError.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));
	_emailError.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));
	_dateOfBirthError.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));
	_passwordError.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));
	_passwordConfirmationError.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));

	_saveButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	_saveButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));
	_saveButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
	_cancelButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	_cancelButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
	_cancelButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));
	this->repaint();
}

void UserRegistration::signin(const User & user)
{
	String password;
	String confirmPassword;
	bool noError = true;

	_errorText.setText("", dontSendNotification);
	_firstNameError.setText("", dontSendNotification);
	_lastNameError.setText("", dontSendNotification);
	_userNameError.setText("", dontSendNotification);
	_emailError.setText("", dontSendNotification);
	_dateOfBirthError.setText("", dontSendNotification);
	_passwordError.setText("", dontSendNotification);
	_passwordConfirmationError.setText("", dontSendNotification);


	if (!(StringChecker::isNameValid(user.getFirstName())) && user.getFirstName() != "")
	{
		_firstNameError.setText(CharPointer_UTF8("Pr\xc3\xa9nom non valide"), dontSendNotification);
		noError = false;
	}

	if (!(StringChecker::isNameValid(user.getLastName())) && user.getLastName() != "")
	{
		_lastNameError.setText("Nom non valide", dontSendNotification);
		noError = false;
	}

 
	if (!(StringChecker::isUserNameValid(user.getUserName())))
	{
		_userNameError.setText("Pseudonyme non valide", dontSendNotification);
		noError = false;
	}

	if (!(StringChecker::isEmailValid(user.getEmail())))
	{
		_emailError.setText("Email non valide", dontSendNotification);
		noError = false;
	}
	
	if (user.getDateOfBirth() != "" && !(StringChecker::isDateValid(user.getDateOfBirth())))
	{
		_dateOfBirthError.setText("Date non valide", dontSendNotification);
		noError = false;
	}

	else
	{

		if (user.getDateOfBirth() != "" && !(StringChecker::isDateInPast(user.getDateOfBirth())))
		{
			_dateOfBirthError.setText("La date ne peut pas etre dans le futur", dontSendNotification);
			noError = false;
		}
	}

	password = _passwordTextEditor.getText();
	confirmPassword = _passwordConfirmationTextEditor.getText();
	if (password != confirmPassword)
	{
		_passwordConfirmationError.setText("Les mots de passe ne sont pas identiques", dontSendNotification);
		noError = false;
	}

	if (password == "")
	{
		_passwordError.setText("Le mot de passe ne peut pas etre vide", dontSendNotification);
		noError = false;
	}

	/*if (!(StringChecker::isPasswordValid(password.toStdString())))
	{
		_errorText.setText("Error Password must be 8 characters long, \ncontain an uppercase letter, one number and one special character", dontSendNotification);
		return;
	}*/

	if (!(StringChecker::isPasswordLongEnough(password.toStdString())))
	{
		_passwordError.setText("Le mot de passe doit faire au moisn 8 characteres de long", dontSendNotification);
		noError = false;
	}

	if (!(StringChecker::containsLowercase(password.toStdString())))
	{
		_passwordError.setText("Le mot de passe doit contenir au moins une miniscule", dontSendNotification);
		noError = false;
	}

	if (!(StringChecker::containsUppercase(password.toStdString())))
	{
		_passwordError.setText("Le mot de passe doit contenir au moins une majuscule", dontSendNotification);
		noError = false;
	}

	if (!(StringChecker::containsNumber(password.toStdString())))
	{
		_passwordError.setText("Le mot de passe doit contenir au moins un chiffre", dontSendNotification);
		noError = false;
	}

	if (!(StringChecker::containsSpecialChar(password.toStdString())))
	{
		_passwordError.setText("Le mot de passe doit contenir au moins un caractere special", dontSendNotification);
		noError = false;
	}

	if (noError)
	{
		if (_cmdManager.signUp(user, password.toStdString()) == false)
		{
			if (_cmdManager.getResponseMsg() != "")
				_errorText.setText("Error : " + _cmdManager.getResponseMsg(), dontSendNotification);
			else
				_errorText.setText("Erreur de connection", dontSendNotification);
		}
		else
		{
			_errorText.setText("", dontSendNotification);
			changeView("Player");
		}
	}
}

void UserRegistration::buttonClicked(Button* button)
{
	if (button->getName() == "signup")
	{
		User user;
		std::string date = _dateOfBirthTextEditor.getText().toStdString();
		user.setEmail(_emailTextEditor.getText().toStdString());
		user.setDateOfBirth(date);
		if (StringChecker::isDateValid(date) && StringChecker::isDateInPast(date))
		{
			user.setDayOfBirth(date.substr(0, 2));
			user.setMonthOfBirth(date.substr(3, 2));
			user.setYearOfBirth(date.substr(6, 4));
		}
		user.setFirstName(_firstNameTextEditor.getText().toStdString());
		user.setLastName(_lastNameTextEditor.getText().toStdString());
		user.setUserName(_userNameTextEditor.getText().toStdString());
		signin(user);
	}
	else if (button->getName() == "cancel")
	{
		changeView("Login");
	}
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
	_cancelButton.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 10, BOX_WIDTH, BOX_HEIGHT);
	_errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 9, BOX_WIDTH, BOX_HEIGHT);

	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
}
