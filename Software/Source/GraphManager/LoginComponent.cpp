/*
  ==============================================================================

    LoginComponent.cpp
    Created: 13 Jan 2018 2:36:43pm
    Author:  Oreo

  ==============================================================================
*/

#include "LoginComponent.h"
#include "MainComponent.h"
#include <sstream> 
#include <string> 

//==============================================================================
LoginComponent::LoginComponent()
{
	int x = getParentWidth();
	int y = getParentHeight();

	setSize(getParentWidth(), getParentHeight() - 10);
	this->currentTheme = parseTheme("../Themes/Dark");


	addAndMakeVisible(textEditor1);
	textEditor1.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT);

	textEditor1.setText("");
	


	addAndMakeVisible(textEditor2);
	textEditor2.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN + 200, BOX_WIDTH, BOX_HEIGHT);
	textEditor2.setText("");
	textEditor2.setPasswordCharacter((juce_wchar)0x2022);//To replace chars with rounds

														 /*addAndMakeVisible(comboBox);
														 comboBox.setBounds(100, 85, 200, 24);
														 comboBox.setEditableText(true);
														 comboBox.setJustificationType(Justification::centred);*/
	

	addAndMakeVisible(inputLabel1);
	inputLabel1.setText("Login:", dontSendNotification);
	inputLabel1.attachToComponent(&textEditor1, true);
	inputLabel1.setJustificationType(Justification::right);

	addAndMakeVisible(inputLabel2);
	inputLabel2.setText("Password:", dontSendNotification);
	inputLabel2.attachToComponent(&textEditor2, true);
	inputLabel2.setJustificationType(Justification::right);

	textEditor1.addListener(this);
	textEditor2.addListener(this);

	addAndMakeVisible(errorText);
	errorText.setText("", juce::NotificationType::dontSendNotification);
	errorText.setColour(Label::textColourId, Colours::red);
	errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);

	addAndMakeVisible(loginButton);
	loginButton.setButtonText("Login");
	loginButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	loginButton.addListener(this);


	//TODO Add a file and read theme list
	addAndMakeVisible(themeChoice);
	themeChoice.setBounds(10, 85, 200, 24);
	themeChoice.setEditableText(true);
	themeChoice.setJustificationType(Justification::centred);

	themeChoice.addItem("Dark", 1);
	themeChoice.addItem("Light", 2);


	themeChoice.setSelectedId(1);
	themeChoice.addListener(this);
	ThemeChanged();


}

void LoginComponent::comboBoxChanged(ComboBox * comboBox)
{
	String value = comboBox->getText();
	//String pathOfTheme = "../Themes/" + value;
	this->currentTheme = parseTheme("../Themes/" + value.toStdString());
	ThemeChanged();
}

void LoginComponent::buttonClicked(Button* button)
{
	//TODO Add API Connection to check login instead of the code below
	String toto;
	String login;
	String password;

	login = textEditor1.getText();
	password = textEditor2.getText();

	if (login == "abc" && password == "abc")
		toto = "correct";
	else
		toto = "wrong";

	errorText.setText(toto, juce::NotificationType::sendNotification);
}


LoginComponent::~LoginComponent()
{
}

void LoginComponent::paint(Graphics& g)
{
	int imgX;
	int imgY;
	float imgH;
	float imgW;
	int rectX;
	int rectY;

	imgH = (LOGO_HEIGHT);
	imgW = (LOGO_WIDTH);

	imgX = (getWidth() / 2) - (imgW / 2);
	imgY = (getHeight() / 15);
	rectX = (getWidth() / 2) - (400 / 2);
	rectY = (getHeight() / 15) + (LOGO_HEIGHT)+50;

	//g.setColour(Colours::white);
	g.fillAll(Colour(this->currentTheme.getBackgroundColor()));
	Image logo = ImageCache::getFromMemory(BinaryData::logo_png,
		BinaryData::logo_pngSize);
	g.drawImage(logo, imgX, imgY, (int)imgW, (int)imgH, 0, 0, 1024, 927, false);
}

void LoginComponent::ThemeChanged()
{
	String tmp = textEditor1.getText();
	textEditor1.setColour(TextEditor::backgroundColourId, Colour(this->currentTheme.getBackgroundColor()));
	textEditor1.setColour(TextEditor::focusedOutlineColourId, Colour(this->currentTheme.getButtonColor()));
	textEditor1.setColour(TextEditor::highlightColourId, Colour(this->currentTheme.getButtonColor()));
	textEditor1.setColour(TextEditor::textColourId, Colour(this->currentTheme.getFontColor()));
	textEditor1.setColour(TextEditor::outlineColourId, Colour(this->currentTheme.getFontColor()));
	textEditor1.clear();
	textEditor1.setText(tmp);

	tmp = textEditor2.getText();
	textEditor2.setColour(TextEditor::backgroundColourId, Colour(this->currentTheme.getBackgroundColor()));
	textEditor2.setColour(TextEditor::focusedOutlineColourId, Colour(this->currentTheme.getButtonColor()));
	textEditor2.setColour(TextEditor::highlightColourId, Colour(this->currentTheme.getButtonColor()));
	textEditor2.setColour(TextEditor::textColourId, Colour(this->currentTheme.getFontColor()));
	textEditor2.setColour(TextEditor::outlineColourId, Colour(this->currentTheme.getFontColor()));
	textEditor2.clear();
	textEditor2.setText(tmp);

	inputLabel1.setColour(Label::textColourId, Colour(this->currentTheme.getButtonColor()));
	inputLabel2.setColour(Label::textColourId, Colour(this->currentTheme.getButtonColor()));

	loginButton.setColour(TextButton::buttonColourId, Colour(this->currentTheme.getButtonColor()));
	loginButton.setColour(TextButton::textColourOnId, Colour(this->currentTheme.getButtonFontColor()));
	this->repaint();
}

void LoginComponent::resized()
{
	int x = (getParentWidth());
	int y = (getParentHeight());



	//rectY = (getHeight() / 15) + (LOGO_HEIGHT)+50;
	textEditor1.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN, BOX_WIDTH, BOX_HEIGHT);
	textEditor2.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 2, BOX_WIDTH, BOX_HEIGHT);
	loginButton.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, BOX_WIDTH, BOX_HEIGHT);
	errorText.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 4, BOX_WIDTH, BOX_HEIGHT);

	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
}
