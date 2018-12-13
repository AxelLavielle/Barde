/*
  ==============================================================================

    TutorialComponent.cpp
    Created: 8 Dec 2018 1:04:45pm
    Author:  Oreo

  ==============================================================================
*/

#include "TutorialComponent.h"
#include "MainComponent.h"
#include <sstream> 
#include <string> 


TutorialComponent::TutorialComponent(CmdManager & cmdManager) : _cmdManager(cmdManager)
{

	int x = getParentWidth() - 300;
	int y = getParentHeight() - 200;

	//this->_currentTheme = parseTheme("../Themes/Dark");

	
	addAndMakeVisible(_prevButton);
	_prevButton.setButtonText("<");
	_prevButton.setName("prev");
	_prevButton.setBounds(50, (y / 2), 50, 50);
	_prevButton.addListener(this);

	addAndMakeVisible(_nextButton);
	_nextButton.setButtonText(">");
	_nextButton.setName("next");
	_nextButton.setBounds(x - 50, (y / 2), 50, 50);
	_nextButton.addListener(this);

	//addAndMakeVisible(_stepCountText);
	_stepCountText.setText("Step 1/6", juce::NotificationType::dontSendNotification);
	_stepCountText.setFontSize(10);
	_stepCountText.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));
	//_stepCountText.setBounds((x / 2) - (BOX_WIDTH / 2), (y / 2) - BOX_HEIGHT / 2 + SPACE_BETWEEN * 3, 1000, BOX_HEIGHT);

	
	step = 0;


	images.push_back(ImageCache::getFromMemory(BinaryData::Barde_step1_png, BinaryData::Barde_step1_pngSize));
	images.push_back(ImageCache::getFromMemory(BinaryData::Barde_step2_png, BinaryData::Barde_step2_pngSize));
	images.push_back(ImageCache::getFromMemory(BinaryData::Barde_step3_png, BinaryData::Barde_step3_pngSize));
	images.push_back(ImageCache::getFromMemory(BinaryData::Barde_step4_png, BinaryData::Barde_step4_pngSize));
	images.push_back(ImageCache::getFromMemory(BinaryData::Barde_step5_png, BinaryData::Barde_step5_pngSize));
	images.push_back(ImageCache::getFromMemory(BinaryData::Barde_step6_png, BinaryData::Barde_step6_pngSize));



	titles.push_back(CharPointer_UTF8 ("Bienvenue sur Barde"));
	titles.push_back(CharPointer_UTF8 ("Le style"));
	titles.push_back(CharPointer_UTF8("Les arp\xc3\xa8ges et les accords"));
	titles.push_back(CharPointer_UTF8("La batterie"));
	titles.push_back(CharPointer_UTF8("Le rythme"));
	titles.push_back(CharPointer_UTF8("Ecoute ta musique"));
	

	texts.push_back(CharPointer_UTF8("Barde est une solution de g\xc3\xa9n\xc3\xa9ration de musique d'ambiance. Mais tu le sais probablement d\xc3\xa9j\xc3\xa0 ... \n\nMais sais-tu comment cela fonctionne ?"));
	texts.push_back(CharPointer_UTF8("Tu as le choix entre plusieurs styles qui te permettent de g\xc3\xa9n\xc3\xa9rer de la musique \x61\x64\x61\x70\x74\xc3\xa9\x65 \xc3\xa0 tes \x67\x6f\xc3\xbb\x74\x73."));
	texts.push_back(CharPointer_UTF8("Choisis tes \x61\x72\x70\xc3\xa8\x67\x65\x73, instruments qui constituent la \x6d\xc3\xa9\x6c\x6f\x64\x69\x65 principale de ta musique. \nMaintenant, place aux accords !Les accords \x63\x72\xc3\xa9\x65\x6e\x74 l'ambiance principale de ta musique.\n\nFais ton choix"));
	texts.push_back(CharPointer_UTF8("Tu souhaites avoir un peu de batterie dans ton morceau ? Active la !"));
	texts.push_back(CharPointer_UTF8("Le BPM \x64\xc3\xa9\x74\x65\x72\x6d\x69\x6e\x65 le tempo de ta musique. Plus il est \xc3\xa9\x6c\x65\x76\xc3\xa9, plus ta musique sera rapide. \x44\xc3\xa9\x74\x65\x72\x6d\x69\x6e\x65\x73 celui qui te conviens !"));
	texts.push_back(CharPointer_UTF8("C'est \x70\x72\xc3\xaa\x74\x20\x21\x20\x44\xc3\xa9\x6d\x61\x72\x72\x65 ta musique en cliquant sur le bouton de lecture."));
	

	addAndMakeVisible(_title);
	_title.setText(titles[step], juce::NotificationType::dontSendNotification);
	_title.setFontSize(50);
	_title.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));
	_title.setBounds(0, 0, x, 150);
	_title.setJustificationType(Justification::centred);
	_title.setFontStyle("bold");

	addAndMakeVisible(_text);
	_text.setText(texts[step], juce::NotificationType::dontSendNotification);
	_text.setFontSize(20);
	_text.setColour(Label::textColourId, Colour(Theme::getInstance().getErrorTextColor()));
	_text.setBounds(100, 700, x - 100, 150);
	_text.setJustificationType(Justification::centred);

	_prevButton.setEnabled(false);




	ThemeChanged();
}

void TutorialComponent::ThemeChanged()
{
	
	_prevButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	_prevButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));
	_prevButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
	_nextButton.setColour(TextButton::buttonColourId, Colour(Theme::getInstance().getButtonColor()));
	_nextButton.setColour(TextButton::textColourOnId, Colour(Theme::getInstance().getButtonFontColor()));
	_nextButton.setColour(TextButton::textColourOffId, Colour(Theme::getInstance().getButtonFontColor()));
	_stepCountText.setColour(Label::textColourId, Colour(Theme::getInstance().getFontColor()));
	_title.setColour(Label::textColourId, Colour(Theme::getInstance().getFontColor()));
	_text.setColour(Label::textColourId, Colour(Theme::getInstance().getFontColor()));
	this->repaint();
}

void TutorialComponent::buttonClicked(Button* button)
{
	_prevButton.setEnabled(true);
	_nextButton.setEnabled(true);
	if (button->getName() == "cancel")
	{
		changeView("Login");
	}

	else if (button->getName() == "prev")
	{
		if (step - 1 >= 0)
			step--;
		if (step == 0)
			_prevButton.setEnabled(false);
		else
			_prevButton.setEnabled(true);
		String str = "Step " + String(step+1) + "/6";
		_stepCountText.setText(str, dontSendNotification);
		_title.setText(titles[step], dontSendNotification);
		_text.setText(texts[step], dontSendNotification);
		this->repaint();
	}

	else if (button->getName() == "next")
	{
		if (step + 1 < images.size())
			step++;
		if (step == images.size() - 1)
			_nextButton.setEnabled(false);
		else
			_nextButton.setEnabled(true);
		String str = "Step " + String(step + 1) + "/6";
		_stepCountText.setText(str, dontSendNotification);
		_title.setText(titles[step], dontSendNotification);
		_text.setText(texts[step], dontSendNotification);
		this->repaint();
	}
}






TutorialComponent::~TutorialComponent()
{
}

void TutorialComponent::paint(Graphics& g)
{
	int x = getParentWidth() - 300;
	int y = getParentHeight() - 200;
	//int x = getWidth();
	//int y = getHeight();
	g.fillAll(Colour(Theme::getInstance().getBackgroundColor()));
	Image background = images[step];
	int imgH = background.getHeight();
	int imgW = background.getWidth();
	g.drawImageAt(background, (x/2) - (imgW / 2), (y / 2) - (imgH / 2) + 90);
}

void TutorialComponent::resized()
{
	int x = (getParentWidth());
	//	int y = (getParentHeight());

	//_saveButton.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 8, BOX_WIDTH, BOX_HEIGHT);
	//_cancelButton.setBounds((x / 2) - (BOX_WIDTH / 2), (100) + BOX_HEIGHT / 2 + SPACE_BETWEEN * 8 + 100, BOX_WIDTH, BOX_HEIGHT);


	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
}
