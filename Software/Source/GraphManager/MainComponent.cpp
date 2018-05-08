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
	
	setSize(getParentWidth(), getParentHeight() - 10);
	_currentTheme = parseTheme("../Themes/Dark");

	addAndMakeVisible(_blues = new MusicStyleButton("Generate some blues", 400, 50, _currentTheme));
	addAndMakeVisible(_params = new MusicStyleButton("User params (TEST)", 400, 50, _currentTheme));
	
	rectX = (600 / 2) - (400 / 2);
	rectY = (400 / 15) + (LOGO_WIDTH) + 100;
	_blues->setBounds(rectX, rectY, 400, 50);
	_params->setBounds(rectX + 100, rectY + 100, 600, 100);
	_blues->addListener(this);
	_params->addListener(this);

	addAndMakeVisible(_frequencySlider);
	_frequencySlider.setRange(20, 200, 1);
	_frequencySlider.setValue(105);
	_frequencySlider.setTextValueSuffix(" BPM");
	addAndMakeVisible(_frequencyLabel);
	_frequencySlider.addListener(this);
	_frequencySlider.setName("BPM");
	_frequencyLabel.setText("BPM : 105", dontSendNotification);
	_frequencyLabel.attachToComponent(&_frequencySlider, true);

	initArpegeList();

	initMusicParameters();
}

MainContentComponent::~MainContentComponent()
{
	delete _blues;
	delete _params;
	//deleteAllChildren();
}

void MainContentComponent::paint (Graphics& g)
{
  int imgX;
  int imgY;
  int imgH;
  int imgW;
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
	g.fillAll(Colour(_currentTheme.getBackgroundColor()));
    g.drawImage(logo, imgX, imgY, (int) imgW, (int) imgH, 0, 0, 1024, 927, false);

	_blues->setBounds(rectX, rectY, 400, 50);
	_params->setBounds(rectX + 100, rectY + 100, 600, 100);

	//TODO Set correct color according to Theme
	_frequencySlider.setColour(Slider::rotarySliderFillColourId, Colours::aqua);
	_frequencySlider.setColour(Slider::backgroundColourId, Colours::red);
	_frequencySlider.setColour(Slider::rotarySliderOutlineColourId, Colours::green);
	_frequencySlider.setColour(Slider::thumbColourId, Colours::pink);
	_frequencySlider.setColour(Slider::trackColourId, Colours::indigo);
}

void MainContentComponent::sliderValueChanged(Slider *slider)
{
	if (slider->getName() == "BPM")
	{
		_musicParameters.setBpm(static_cast<int>(slider->getValue()));
	}

}

void MainContentComponent::initArpegeList()
{
	_arpegesList.setBounds(10, 10, 100, 100);
	//_arpegesList.
	addAndMakeVisible(_arpegesList);
}

void MainContentComponent::initMusicParameters()
{
	_musicParameters.setBpm(105);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

	const int sliderLeft = 120;
	//	int w = (getWidth() / 2) - 150;
	_frequencySlider.setBounds(sliderLeft, getHeight() - 300, getWidth() - sliderLeft - 10, 20);
}

void MainContentComponent::buttonClicked(Button* button)
{
	if (button == _params)
	{
		changeView("UserParams");
	}
	else if (button == _blues)
	{
		_player.Play(_musicParameters);
	}
}
