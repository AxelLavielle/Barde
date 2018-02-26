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
	this->currentTheme = parseTheme("../Themes/Dark");

	//TODO GET INFO FROM API
	//initData();

	addAndMakeVisible(userNameTextEditor);
	userNameTextEditor.setText("");

	addAndMakeVisible(emailTextEditor);
	emailTextEditor.setText("");

	addAndMakeVisible(dateOfBirthTextEditor);
	dateOfBirthTextEditor.setText("");
	
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






	//textEditor1.addListener(this);
	//textEditor2.addListener(this);

	addAndMakeVisible(errorText);
	errorText.setText("", juce::NotificationType::dontSendNotification);
	errorText.setColour(Label::textColourId, Colours::red);
	errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);

	addAndMakeVisible(saveButton);
	saveButton.setButtonText("Save modifications");
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

void UserParamsComponent::ThemeChanged()
{
	String tmp = userNameTextEditor.getText();
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


	userNameLabel.setColour(Label::textColourId, Colour(this->currentTheme.getButtonColor()));
	emailLabel.setColour(Label::textColourId, Colour(this->currentTheme.getButtonColor()));
	dateOfBirthLabel.setColour(Label::textColourId, Colour(this->currentTheme.getButtonColor()));
	passwordLabel.setColour(Label::textColourId, Colour(this->currentTheme.getButtonColor()));
	passwordConfirmationLabel.setColour(Label::textColourId, Colour(this->currentTheme.getButtonColor()));

	saveButton.setColour(TextButton::buttonColourId, Colour(this->currentTheme.getButtonColor()));
	saveButton.setColour(TextButton::textColourOnId, Colour(this->currentTheme.getButtonFontColor()));
	this->repaint();
}

void UserParamsComponent::buttonClicked(Button* button)
{
	//TODO Add API Connection to save changes instead of the code below

	String username;
	String email;
	String dateofbirth;
	String password;
	String confirmpassword;
	String language;

	username = userNameTextEditor.getText();
	email = emailTextEditor.getText();
	dateofbirth = dateOfBirthTextEditor.getText();
	language = languageComboBox.getText();
	password = passwordTextEditor.getText();
	confirmpassword = passwordConfirmationTextEditor.getText();
	if (password != confirmpassword)
		errorText.setText("Error passwords don't match", dontSendNotification);
	std::cout << "username : " << username << " email: " << email << "date of birth: " << dateofbirth << " language : " << language << "password: " << password << " confirm password :" << confirmpassword << std::endl;
}


UserParamsComponent::~UserParamsComponent()
{
}

void UserParamsComponent::paint(Graphics& g)
{
	//g.setColour(Colours::white);
	g.fillAll(Colour(this->currentTheme.getBackgroundColor()));
}

void UserParamsComponent::resized()
{
	int x = (getParentWidth());
	int y = (getParentHeight());

	userNameTextEditor.setBounds((x/2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	emailTextEditor.setBounds((x/2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 2, BOX_WIDTH, BOX_HEIGHT);
	dateOfBirthTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);
	passwordTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 4, BOX_WIDTH, BOX_HEIGHT);
	passwordConfirmationTextEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 5, BOX_WIDTH, BOX_HEIGHT);
	saveButton.setBounds((x/2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 6, BOX_WIDTH, BOX_HEIGHT);
	errorText.setBounds((x/2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 7, BOX_WIDTH, BOX_HEIGHT);

	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
}
