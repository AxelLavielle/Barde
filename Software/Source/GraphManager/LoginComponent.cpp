/*
  ==============================================================================

    LoginComponent.cpp
    Created: 13 Jan 2018 2:36:43pm
    Author:  Oreo

  ==============================================================================
*/

#include <sstream> 
#include <string> 
#include "LoginComponent.h"
#include "MainComponent.h"

//==============================================================================
LoginComponent::LoginComponent(CmdManager & cmdMaager) : _cmdManager(cmdMaager)
{
	int x = getParentWidth();
	int y = getParentHeight();

	setSize(getParentWidth(), getParentHeight() - 10);
	_currentTheme = parseTheme("../Themes/Dark");


	addAndMakeVisible(_textEditor1);
	_textEditor1.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT);
	_textEditor1.setText("");
	


	addAndMakeVisible(_textEditor2);
	_textEditor2.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN + 200, BOX_WIDTH, BOX_HEIGHT);
	_textEditor2.setText("");
	_textEditor2.setPasswordCharacter((juce_wchar)0x2022);//To replace chars with rounds

														 /*addAndMakeVisible(comboBox);
														 comboBox.setBounds(100, 85, 200, 24);
														 comboBox.setEditableText(true);
														 comboBox.setJustificationType(Justification::centred);*/
	

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
	_errorText.setColour(Label::textColourId, Colours::red);
	_errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);

	addAndMakeVisible(_loginButton);
	_loginButton.setButtonText("Login");
	_loginButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	_loginButton.addListener(this);


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

	_cmdManager.connectToServer();

}

void LoginComponent::comboBoxChanged(ComboBox * comboBox)
{
	String value = comboBox->getText();
	//String pathOfTheme = "../Themes/" + value;
	_currentTheme = parseTheme("../Themes/" + value.toStdString());
	ThemeChanged();
}

void LoginComponent::buttonClicked(Button* button)
{
	String errorMessage;
	String login;
	String password;

	login = _textEditor1.getText();
	password = _textEditor2.getText();

	if (_cmdManager.login(login.toStdString(), password.toStdString())) {
	  (void)button;
		errorMessage = "Login correct";
		changeView("Main");
	}

	else {
		errorMessage = "There was an error during the login process";
	}
	_errorText.setText(errorMessage, juce::NotificationType::sendNotification);
}


LoginComponent::~LoginComponent()
{
}

void LoginComponent::paint(Graphics& g)
{
	int imgX;
	int imgY;
	int imgH;
	int imgW;
	//	int rectX;
	//	int rectY;

	imgH = (LOGO_HEIGHT);
	imgW = (LOGO_WIDTH);

	imgX = (getWidth() / 2) - (imgW / 2);
	imgY = (getHeight() / 15);
	//	rectX = (getWidth() / 2) - (400 / 2);
	//	rectY = (getHeight() / 15) + (LOGO_HEIGHT)+50;

	//g.setColour(Colours::white);
	g.fillAll(Colour(_currentTheme.getBackgroundColor()));
	Image logo = ImageCache::getFromMemory(BinaryData::logo_png,
		BinaryData::logo_pngSize);
	g.drawImage(logo, imgX, imgY, (int)imgW, (int)imgH, 0, 0, 1024, 927, false);
}

void LoginComponent::ThemeChanged()
{
	String tmp = _textEditor1.getText();
	_textEditor1.setColour(TextEditor::backgroundColourId, Colour(_currentTheme.getBackgroundColor()));
	_textEditor1.setColour(TextEditor::focusedOutlineColourId, Colour(_currentTheme.getButtonColor()));
	_textEditor1.setColour(TextEditor::highlightColourId, Colour(_currentTheme.getButtonColor()));
	_textEditor1.setColour(TextEditor::textColourId, Colour(_currentTheme.getFontColor()));
	_textEditor1.setColour(TextEditor::outlineColourId, Colour(_currentTheme.getFontColor()));
	_textEditor1.clear();
	_textEditor1.setText(tmp);

	tmp = _textEditor2.getText();
	_textEditor2.setColour(TextEditor::backgroundColourId, Colour(_currentTheme.getBackgroundColor()));
	_textEditor2.setColour(TextEditor::focusedOutlineColourId, Colour(_currentTheme.getButtonColor()));
	_textEditor2.setColour(TextEditor::highlightColourId, Colour(_currentTheme.getButtonColor()));
	_textEditor2.setColour(TextEditor::textColourId, Colour(_currentTheme.getFontColor()));
	_textEditor2.setColour(TextEditor::outlineColourId, Colour(_currentTheme.getFontColor()));
	_textEditor2.clear();
	_textEditor2.setText(tmp);

	_inputLabel1.setColour(Label::textColourId, Colour(_currentTheme.getButtonColor()));
	_inputLabel2.setColour(Label::textColourId, Colour(_currentTheme.getButtonColor()));

	_loginButton.setColour(TextButton::buttonColourId, Colour(_currentTheme.getButtonColor()));
	_loginButton.setColour(TextButton::textColourOnId, Colour(_currentTheme.getButtonFontColor()));
	this->repaint();
}

void LoginComponent::resized()
{
	int x = (getParentWidth());
	int y = (getParentHeight());



	//rectY = (getHeight() / 15) + (LOGO_HEIGHT)+50;
	_textEditor1.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	_textEditor2.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 2, BOX_WIDTH, BOX_HEIGHT);
	_loginButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);
	_errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 4, BOX_WIDTH, BOX_HEIGHT);

	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
}
