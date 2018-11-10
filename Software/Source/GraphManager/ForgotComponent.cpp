/*
==============================================================================

ForgotComponent.cpp
Created: 13 Jan 2018 2:36:43pm
Author:  Oreo

==============================================================================
*/

#include <sstream> 
#include <string> 
#include "ForgotComponent.h"
#include "MainComponent.h"


//==============================================================================
ForgotComponent::ForgotComponent(CmdManager & cmdMaager) : _cmdManager(cmdMaager)
{
	//int x = getParentWidth();
	//int y = getParentHeight();

	int x = 900;
	int y = 600;


	juce::Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
	int w = r.getWidth();
	int h = r.getHeight();
	//setBounds(w / 2 - x / 2, h / 2 - y / 2, x, y);
	setBounds(0, 0, x, y);

	Theme::getInstance().parseTheme("../Themes/Dark");


	addAndMakeVisible(_emailTextBox);
	_emailTextBox.setText("");

	addAndMakeVisible(_emailLabel);
	_emailLabel.setText("Email:", dontSendNotification);
	_emailLabel.attachToComponent(&_emailTextBox, true);
	_emailLabel.setJustificationType(Justification::right);

	//Passwords
	addAndMakeVisible(_passwordTextBox);
	_passwordTextBox.setText("");
	_passwordTextBox.setPasswordCharacter((juce_wchar)0x2022);//To replace chars with rounds

	addAndMakeVisible(_passwordLabel);
	_passwordLabel.setText("Password:", dontSendNotification);
	_passwordLabel.attachToComponent(&_passwordTextBox, true);
	_passwordLabel.setJustificationType(Justification::right);


	addAndMakeVisible(_passwordConfirmationTextBox);
	_passwordConfirmationTextBox.setText("");
	_passwordConfirmationTextBox.setPasswordCharacter((juce_wchar)0x2022);//To replace chars with rounds

	addAndMakeVisible(_passwordConfirmationLabel);
	_passwordConfirmationLabel.setText("Confirm Password:", dontSendNotification);
	_passwordConfirmationLabel.attachToComponent(&_passwordConfirmationTextBox, true);
	_passwordConfirmationLabel.setJustificationType(Justification::right);



	_emailTextBox.addListener(this);
	_passwordTextBox.addListener(this);
	_passwordConfirmationTextBox.addListener(this);

	addAndMakeVisible(_errorText);
	_errorText.setText("", juce::NotificationType::dontSendNotification);


	addAndMakeVisible(_sendTokenButton);
	_sendTokenButton.setButtonText("Send recovery email");
	_sendTokenButton.setName("sendToken");
	_sendTokenButton.addListener(this);

	addAndMakeVisible(_changePasswordButton);
	_changePasswordButton.setButtonText("Reset Password");
	_changePasswordButton.setName("resetPassword");
	_changePasswordButton.addListener(this);

	addAndMakeVisible(_cancelButton);
	_cancelButton.setButtonText("Cancel");
	_cancelButton.setName("cancel");
	_cancelButton.addListener(this);


	//_textEditor1.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	//_textEditor2.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 2, BOX_WIDTH, BOX_HEIGHT);
	//_loginButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);
	//_signinButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 4, BOX_WIDTH, BOX_HEIGHT);
	//_forgotPasswordButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 5, BOX_WIDTH, BOX_HEIGHT);
	//_errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN / 2, BOX_WIDTH, BOX_HEIGHT);

	ThemeChanged();
}




void ForgotComponent::forgot(const std::string & login)
{
	String errorMessage;


	try
	{
		if (_cmdManager.forgetPassword(login)) {
			errorMessage = "";
			//changeView("");
			//TDO DISPLAY TOKEN INFO
		}
		else
		{
			if (_cmdManager.getResponseCode() == 400)
				errorMessage = "The email is incorrect";
			else
				errorMessage = "There was an error during the process";
		}
	}
	catch (RestClientException &e)
	{
		errorMessage = "There was an error during the login process";
	}
	_errorText.setText(errorMessage, juce::NotificationType::sendNotification);
}

void ForgotComponent::buttonClicked(Button* button)
{
	if (button->getName() == "sendToken")
	{
		//send forgot api
		forgot(_emailTextBox.getText().toStdString());
	}

	if (button->getName() == "cancel")
	{
		changeView("Login");
	}

	if (button->getName() == "resetPassword")
	{
		//TODO forgot api
	}
}


ForgotComponent::~ForgotComponent()
{
}

void ForgotComponent::paint(Graphics& g)
{
	g.fillAll(Colour(Theme::getInstance().getBackgroundColor()));

}

void ForgotComponent::ThemeChanged()
{
	_errorText.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));

	String tmp = _emailTextBox.getText();
	_emailTextBox.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	_emailTextBox.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_emailTextBox.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_emailTextBox.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_emailTextBox.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_emailTextBox.clear();
	_emailTextBox.setText(tmp);

	tmp = _passwordTextBox.getText();
	_passwordTextBox.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordTextBox.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordTextBox.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_passwordTextBox.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_passwordTextBox.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_passwordTextBox.clear();
	_passwordTextBox.setText(tmp);

	_emailLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));

	_sendTokenButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	_sendTokenButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));
	_sendTokenButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
	_changePasswordButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	_changePasswordButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));
	_changePasswordButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
	_cancelButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	_cancelButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));
	_cancelButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));

	this->repaint();
}

void ForgotComponent::resized()
{
	int x = (getParentWidth());
	int y = (getParentHeight());

	x = 900;
	y = 600;
	int startX = (x / 2);
	int startY = (y / 4);

	juce::Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
	int w = r.getWidth();
	int h = r.getHeight();
	setBounds(w / 2 - x / 2, h / 2 - y / 2, x, y);


	//rectY = (getHeight() / 15) + (LOGO_HEIGHT)+50;
	_emailTextBox.setBounds(startX - (BOX_WIDTH / 2), startY - BOX_HEIGHT / 2 + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	_passwordTextBox.setBounds(startX - (BOX_WIDTH / 2), startY - BOX_HEIGHT / 2 + SPACE_BETWEEN * 2, BOX_WIDTH, BOX_HEIGHT);
	_changePasswordButton.setBounds(startX - (BOX_WIDTH / 2), startY - BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);
	_cancelButton.setBounds(startX - (BOX_WIDTH / 2), startY - BOX_HEIGHT / 2 + SPACE_BETWEEN * 4, BOX_WIDTH, BOX_HEIGHT);
	_sendTokenButton.setBounds(startX - (BOX_WIDTH / 2), startY - BOX_HEIGHT / 2 + SPACE_BETWEEN * 5, BOX_WIDTH, BOX_HEIGHT);
	_errorText.setBounds(startX - (BOX_WIDTH / 2), startY - BOX_HEIGHT / 2 - SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);

	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
}