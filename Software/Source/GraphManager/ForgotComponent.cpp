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

	int x = getParentWidth();
	int y = getParentHeight();

	//int x = 900;
	//int y = 600;


	juce::Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
	int w = r.getWidth();
	int h = r.getHeight();
	//setBounds(w / 2 - x / 2, h / 2 - y / 2, x, y);
	//setBounds(0, 0, x, y);
	setSize(getParentWidth(), getParentHeight() - 10);

	//Theme::getInstance().parseTheme("../Themes/Dark");

	addAndMakeVisible(_errorText);
	_errorText.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));
	_errorText.setText("", juce::NotificationType::dontSendNotification);
	_errorText.setBounds(x - (BOX_WIDTH / 2), y - BOX_HEIGHT / 2 - SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);

	addAndMakeVisible(_successText);
	_successText.setText("", juce::NotificationType::dontSendNotification);
	_successText.setBounds(x - (BOX_WIDTH / 2), y - BOX_HEIGHT / 2 - SPACE_BETWEEN , BOX_WIDTH, BOX_HEIGHT);

	addAndMakeVisible(_emailTextBox);
	_emailTextBox.setText("");

	addAndMakeVisible(_emailLabel);
	_emailLabel.setText("Email:", dontSendNotification);
	_emailLabel.attachToComponent(&_emailTextBox, true);
	_emailLabel.setJustificationType(Justification::right);

	addAndMakeVisible(_sendTokenButton);
	_sendTokenButton.setButtonText("Envoyer le token par email");
	_sendTokenButton.setName("sendToken");
	_sendTokenButton.addListener(this);

	addAndMakeVisible(_tokenTextBox);
	_tokenTextBox.setText("");

	addAndMakeVisible(_tokenLabel);
	_tokenLabel.setText("Token:", dontSendNotification);
	_tokenLabel.attachToComponent(&_tokenTextBox, true);
	_tokenLabel.setJustificationType(Justification::right);

	//Passwords
	addAndMakeVisible(_passwordTextBox);
	_passwordTextBox.setText("");
	_passwordTextBox.setPasswordCharacter((juce_wchar)0x2022);//To replace chars with rounds

	addAndMakeVisible(_passwordLabel);
	_passwordLabel.setText("Mot de passe:", dontSendNotification);
	_passwordLabel.attachToComponent(&_passwordTextBox, true);
	_passwordLabel.setJustificationType(Justification::right);


	addAndMakeVisible(_passwordConfirmationTextBox);
	_passwordConfirmationTextBox.setText("");
	_passwordConfirmationTextBox.setPasswordCharacter((juce_wchar)0x2022);//To replace chars with rounds

	addAndMakeVisible(_passwordConfirmationLabel);
	_passwordConfirmationLabel.setText("Confirmer le mot de passe:", dontSendNotification);
	_passwordConfirmationLabel.attachToComponent(&_passwordConfirmationTextBox, true);
	_passwordConfirmationLabel.setJustificationType(Justification::right);



	_emailTextBox.addListener(this);
	_passwordTextBox.addListener(this);
	_passwordConfirmationTextBox.addListener(this);

	addAndMakeVisible(_changePasswordButton);
	_changePasswordButton.setButtonText("Reinitialiser le mot de passe");
	_changePasswordButton.setName("resetPassword");
	_changePasswordButton.addListener(this);

	addAndMakeVisible(_cancelButton);
	_cancelButton.setButtonText("Annuler");
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


void ForgotComponent::changePassword()
{
	bool noError = true;
	String errorMessage = "";
	String successMessage = "";

	std::string email = _emailTextBox.getText().toStdString();
	std::string token = _tokenTextBox.getText().toStdString();
	std::string password = _passwordTextBox.getText().toStdString();
	std::string passwordConfirm = _passwordConfirmationTextBox.getText().toStdString();

	if (password == "" || passwordConfirm == "")
	{
		errorMessage = "Mot de passe non valide.";
		noError = false;
	}

	if (password != passwordConfirm)
	{
		errorMessage = "Les mots de passe ne sont pas identiques";
		noError = false;
	}


	if (!(StringChecker::isPasswordLongEnough(password)))
	{
		errorMessage = "Le mot de passe doit faire au moins 8 caracteres de long";
		noError = false;
	}

	if (!(StringChecker::containsLowercase(password)))
	{
		errorMessage = "Le mot de passe doit contenir au moins une miniscule";
		noError = false;
	}

	if (!(StringChecker::containsUppercase(password)))
	{
		errorMessage = "Le mot de passe doit contenir au moins une majuscule";
		noError = false;
	}

	if (!(StringChecker::containsNumber(password)))
	{
		errorMessage = "Le mot de passe doit contenir au moins un chiffre";
		noError = false;
	}

	if (!(StringChecker::containsSpecialChar(password)))
	{
		errorMessage = "Le mot de passe doit contenir au moins un caractere special";
		noError = false;
	}

	if (noError) {
		try
		{
			if (_cmdManager.resetPassword(email, token, password)) {
				errorMessage = "";
				successMessage = "Not de passe mis a jour.";
			}
			else
			{
				if (_cmdManager.getResponseCode() == 400)
					errorMessage = "Parametres incorrects";
				else
					errorMessage = "Une erreur est survenue";
			}
		}
		catch (RestClientException &e)
		{
			errorMessage = "Une erreur est s";
		}
	}
	_successText.setText(successMessage, juce::NotificationType::sendNotification);
	_errorText.setText(errorMessage, juce::NotificationType::sendNotification);
}

void ForgotComponent::forgot()
{
	String errorMessage;
	String successMessage = "";
	std::string login = _emailTextBox.getText().toStdString();

	try
	{
		if (_cmdManager.forgetPassword(login)) {
			errorMessage = "";
			successMessage = "Token envoye. Verifiez vos mails.";
		}
		else
		{
			if (_cmdManager.getResponseCode() == 400)
				errorMessage = "L'email est incorrect";
			else
				errorMessage = "Une erreur est survenue";
		}
	}
	catch (RestClientException &e)
	{
		errorMessage = "Une erreur est survenue";
	}
	_successText.setText(successMessage, juce::NotificationType::sendNotification);
	_errorText.setText(errorMessage, juce::NotificationType::sendNotification);
}

void ForgotComponent::buttonClicked(Button* button)
{
	if (button->getName() == "sendToken")
	{
		//send forgot api
		forgot();
	}

	if (button->getName() == "cancel")
	{
		changeView("Login");
	}

	if (button->getName() == "resetPassword")
	{
		//TODO forgot api
		changePassword();
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

	tmp = _tokenTextBox.getText();
	_tokenTextBox.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	_tokenTextBox.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_tokenTextBox.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_tokenTextBox.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_tokenTextBox.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_tokenTextBox.clear();
	_tokenTextBox.setText(tmp);

	tmp = _passwordTextBox.getText();
	_passwordTextBox.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordTextBox.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordTextBox.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_passwordTextBox.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_passwordTextBox.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_passwordTextBox.clear();
	_passwordTextBox.setText(tmp);

	tmp = _passwordConfirmationTextBox.getText();
	_passwordConfirmationTextBox.setColour(TextEditor::backgroundColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordConfirmationTextBox.setColour(TextEditor::focusedOutlineColourId, Colour(Theme::getInstance().getButtonColor()));
	_passwordConfirmationTextBox.setColour(TextEditor::highlightColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_passwordConfirmationTextBox.setColour(TextEditor::textColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_passwordConfirmationTextBox.setColour(TextEditor::outlineColourId, Colour(Theme::getInstance().getButtonFontColor()));
	_passwordConfirmationTextBox.clear();
	_passwordConfirmationTextBox.setText(tmp);

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

	/*x = 900;
	y = 600;
	int startX = (x / 2);
	int startY = (y / 4);

	juce::Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
	int w = r.getWidth();
	int h = r.getHeight();
	setBounds(w / 2 - x / 2, h / 2 - y / 2, x, y);*/


	//rectY = (getHeight() / 15) + (LOGO_HEIGHT)+50;
	_emailTextBox.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	_sendTokenButton.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN *2, BOX_WIDTH, BOX_HEIGHT);
	_tokenTextBox.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);
	_passwordTextBox.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 4, BOX_WIDTH, BOX_HEIGHT);
	_passwordConfirmationTextBox.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 5, BOX_WIDTH, BOX_HEIGHT);
	_changePasswordButton.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 6, BOX_WIDTH, BOX_HEIGHT);
	_cancelButton.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 7, BOX_WIDTH, BOX_HEIGHT);
	_errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 8, BOX_WIDTH, BOX_HEIGHT);
	_successText.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 8, BOX_WIDTH, BOX_HEIGHT);

	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
}