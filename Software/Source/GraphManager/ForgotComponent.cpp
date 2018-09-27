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
	setBounds(w / 2 - x / 2, h / 2 - y / 2, x, y);
	//setBounds(0, 0, x, y);

	Theme::getInstance().parseTheme("../Themes/Dark");


	addAndMakeVisible(_emailEditor);
	_emailEditor.setText("");



	addAndMakeVisible(_tokenEditor);
	_tokenEditor.setText("");
	_tokenEditor.setPasswordCharacter((juce_wchar)0x2022);//To replace chars with rounds


	addAndMakeVisible(_emailLabel);
	_emailLabel.setText("Email:", dontSendNotification);
	_emailLabel.attachToComponent(&_emailEditor, true);
	_emailLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_tokenLabel);
	_tokenLabel.setText("Token:", dontSendNotification);
	_tokenLabel.attachToComponent(&_tokenEditor, true);
	_tokenLabel.setJustificationType(Justification::right);

	_emailEditor.addListener(this);
	_tokenEditor.addListener(this);
	_passwordEditor.addListener(this);
	_confirmPasswordEditor.addListener(this);

	addAndMakeVisible(_errorText);
	_errorText.setText("", juce::NotificationType::dontSendNotification);


	addAndMakeVisible(_sendEmailButton);
	_sendEmailButton.setButtonText("Send Email");
	_sendEmailButton.setName("sendmail");
	_sendEmailButton.addListener(this);

	addAndMakeVisible(_resetPasswordButton);
	_resetPasswordButton.setButtonText("Reset Password");
	_resetPasswordButton.setName("reset");
	_resetPasswordButton.addListener(this);

	_emailEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	_tokenEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 2, BOX_WIDTH, BOX_HEIGHT);
	_sendEmailButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);
	_resetPasswordButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 4, BOX_WIDTH, BOX_HEIGHT);
	_errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN / 2, BOX_WIDTH, BOX_HEIGHT);

	ThemeChanged();
}


void ForgotComponent::forgot(const std::string & login, const std::string & password)
{
	String errorMessage;


	try
	{
		if (_cmdManager.login(login, password)) {
			errorMessage = "";
			changeView("Player");
		}
		else
		{
			if (_cmdManager.getResponseCode() == 400)
				errorMessage = "The email or password is incorrect";
			else
				errorMessage = "There was an error during the login process";
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
	if (button->getName() == "Login")
	{
		//send forgot api
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

	String tmp = _emailEditor.getText();
	_emailEditor.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	_emailEditor.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_emailEditor.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_emailEditor.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_emailEditor.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_emailEditor.clear();
	_emailEditor.setText(tmp);

	tmp = _tokenEditor.getText();
	_tokenEditor.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	_tokenEditor.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_tokenEditor.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_tokenEditor.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_tokenEditor.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_tokenEditor.clear();
	_tokenEditor.setText(tmp);

	_emailLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));
	_tokenLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));

	_sendEmailButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	_sendEmailButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));
	_sendEmailButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
	_resetPasswordButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	_resetPasswordButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));
	_resetPasswordButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));

	this->repaint();
}

void ForgotComponent::resized()
{
	int x = (getParentWidth());
	int y = (getParentHeight());

	x = 900;
	y = 600;

	juce::Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
	int w = r.getWidth();
	int h = r.getHeight();
	setBounds(w / 2 - x / 2, h / 2 - y / 2, x, y);


	//rectY = (getHeight() / 15) + (LOGO_HEIGHT)+50;
	_emailEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	_tokenEditor.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 2, BOX_WIDTH, BOX_HEIGHT);
	_sendEmailButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);
	_resetPasswordButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 4, BOX_WIDTH, BOX_HEIGHT);
	_errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 - SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);

	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
}
