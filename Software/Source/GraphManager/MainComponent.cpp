/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "Theme.h"

//==============================================================================
MainContentComponent::MainContentComponent()
{
	int rectX;
	int rectY;
	
	//TODO Receive MusicParameters from main or something to send to the player
	us = UserSettings(new MusicParameters());

	setSize(getParentWidth(), getParentHeight() - 10);
	this->currentTheme = parseTheme("../Themes/Dark");
	addAndMakeVisible(blues = new MusicStyleButton("Generate some blues", 400, 50, this->currentTheme));
	addAndMakeVisible(params = new MusicStyleButton("User params (TEST)", 400, 50, this->currentTheme));
	rectX = (600 / 2) - (400 / 2);
	rectY = (400 / 15) + (LOGO_WIDTH) + 100;
	blues->setBounds(rectX, rectY, 400, 50);
	params->setBounds(rectX + 100, rectY + 100, 600, 100);
	blues->addListener(this);
	params->addListener(this);


	addAndMakeVisible(frequencySlider);
	frequencySlider.setRange(20, 200, 1);          // [1] 
	frequencySlider.setTextValueSuffix(" BPM");     // [2] 
	addAndMakeVisible(frequencyLabel);
	frequencySlider.addListener(this);
	frequencySlider.setName("BPM");
	frequencyLabel.setText("BPM", dontSendNotification);
	frequencyLabel.attachToComponent(&frequencySlider, true); // [4] 	
}

MainContentComponent::~MainContentComponent()
{
	deleteAllChildren();
}

void MainContentComponent::paint (Graphics& g)
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
  rectY = (getHeight() / 15) + (LOGO_HEIGHT) + 50;

	g.setColour (Colours::white);
    Image logo = ImageCache::getFromMemory (BinaryData::logo_png,    
					      BinaryData::logo_pngSize);
	g.fillAll(Colour(this->currentTheme.getBackgroundColor()));
    g.drawImage(logo, imgX, imgY, (int) imgW, (int) imgH, 0, 0, 1024, 927, false);
	blues->setBounds(rectX, rectY, 400, 50);
	params->setBounds(rectX + 100, rectY + 100, 600, 100);

	//TODO Set correct color according to Theme
	frequencySlider.setColour(Slider::rotarySliderFillColourId, Colours::aqua);
	frequencySlider.setColour(Slider::backgroundColourId, Colours::red);
	frequencySlider.setColour(Slider::rotarySliderOutlineColourId, Colours::green);
	frequencySlider.setColour(Slider::thumbColourId, Colours::pink);
	frequencySlider.setColour(Slider::trackColourId, Colours::indigo);
}

void MainContentComponent::sliderValueChanged(Slider *slider)
{
	if (slider->getName() == "BPM")
	{
		this->us.setBPM(slider->getValue());
	}

}


void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
	const int sliderLeft = 120;
	//	int w = (getWidth() / 2) - 150;
	frequencySlider.setBounds(sliderLeft, getHeight() - 300, getWidth() - sliderLeft - 10, 20);
}

void MainContentComponent::buttonClicked(Button* button)
{
	if (button == params)
	{
		changeView("UserParams");
	}
	else if (button == blues)
	{
		_threadPlayer = std::thread(&Player::Play, &_player);
		_threadPlayer.detach();
	}
}
