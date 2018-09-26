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


	addAndMakeVisible(_textEditor1);
	_textEditor1.setText("");



	addAndMakeVisible(_textEditor2);
	_textEditor2.setText("");
	_textEditor2.setPasswordCharacter((juce_wchar)0x2022);//To replace chars with rounds


	addAndMakeVisible(_inputLabel1);
	_inputLabel1.setText("Login:", dontSendNotification);
	_inputLabel1.attachToComponent(&_textEditor1, true);
	_inputLabel1.setJustificationType(Justification::right);

	addAndMakeVisible(_inputLabel2);
	_inputLabel2.setText("Password:", dontSendNotification);
	_inputLabel2.attachToComponent(&_textEditor2, true);
	_inputLabel2.setJustificationType(Justification::right);

	_textEditor1.addListener(this);
	_textEditor2.addListener(this);

	addAndMakeVisible(_errorText);
	_errorText.setText("", juce::NotificationType::dontSendNotification);


	addAndMakeVisible(_loginButton);
	_loginButton.setButtonText("Login");
	_loginButton.setName("Login");
	_loginButton.addListener(this);

	addAndMakeVisible(_signinButton);
	_signinButton.setButtonText("Sign up");
	_signinButton.setName("signup");
	_signinButton.addListener(this);


	addAndMakeVisible(_forgotPasswordButton);
	_forgotPasswordButton.setButtonText("Forgot Password ?");
	_forgotPasswordButton.setName("Forgot");
	_forgotPasswordButton.addListener(this);

	_textEditor1.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	_textEditor2.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 2, BOX_WIDTH, BOX_HEIGHT);
	_loginButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);
	_signinButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 4, BOX_WIDTH, BOX_HEIGHT);
	_forgotPasswordButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 5, BOX_WIDTH, BOX_HEIGHT);
	_errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN / 2, BOX_WIDTH, BOX_HEIGHT);





	//TODO Add a file and read theme list
	_themeChoice.setBounds(10, 85, 200, 24);
	_themeChoice.setEditableText(true);
	_themeChoice.setJustificationType(Justification::centred);
	_themeChoice.addItem("Dark", 1);
	_themeChoice.addItem("Light", 2);
	_themeChoice.setSelectedId(1);
	_themeChoice.addListener(this);
	//addAndMakeVisible(_themeChoice);

	ThemeChanged();
}




void ForgotComponent::comboBoxChanged(ComboBox * comboBox)
{
	String value = comboBox->getText();
	//String pathOfTheme = "../Themes/" + value;
	Theme::getInstance().parseTheme("../Themes/" + value.toStdString());
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

	String tmp = _textEditor1.getText();
	_textEditor1.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	_textEditor1.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_textEditor1.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_textEditor1.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_textEditor1.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_textEditor1.clear();
	_textEditor1.setText(tmp);

	tmp = _textEditor2.getText();
	_textEditor2.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	_textEditor2.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_textEditor2.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_textEditor2.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_textEditor2.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_textEditor2.clear();
	_textEditor2.setText(tmp);

	_inputLabel1.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));
	_inputLabel2.setColour(Label::textColourId, Colour(Theme::getInstance().getButtonColor()));

	_loginButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	_loginButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));
	_loginButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
	_signinButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	_signinButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));
	_signinButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
	_forgotPasswordButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getBackgroundColor()));
	_forgotPasswordButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getFontColor()));
	_forgotPasswordButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getFontColor()));
	_forgotPasswordButton.setColour(TextButton::buttonOnColourId, Colour(Theme::getInstance().getBackgroundColor()));

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
	_textEditor1.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	_textEditor2.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 2, BOX_WIDTH, BOX_HEIGHT);
	_loginButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);
	_signinButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 4, BOX_WIDTH, BOX_HEIGHT);
	_forgotPasswordButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 5, BOX_WIDTH, BOX_HEIGHT);
	_errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 - SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);

	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
}
