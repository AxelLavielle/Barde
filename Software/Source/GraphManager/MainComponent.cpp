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
	

	//TO DO CHANGE THIS
	_instrusChoice = { "ACOUSTICGRANDPIANO", "LOWCONGA", "MARACAS" };



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
	_frequencyLabel.setText("BPM :", dontSendNotification);
	_frequencyLabel.attachToComponent(&_frequencySlider, true);


	_drumsButton = new ToggleButton("Drums");
	_drumsButton->setName("Drums");
	_drumsButton->addListener(this);
	_drumsButton->setBounds(10, 50, 600, 600);
	addAndMakeVisible(_drumsButton);


	initArpegeList();
	initChordsList();

	initMusicParameters();

	_player.Init();
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
	_params->setBounds(rectX, rectY + 70, 600, 100);

	
	_frequencyLabel.setColour(Label::textColourId, Colour(_currentTheme.getFontColor()));
	_frequencySlider.setColour(Slider::backgroundColourId, Colour(_currentTheme.getFontColor()));
	_frequencySlider.setColour(Slider::thumbColourId, Colours::pink);
	_frequencySlider.setColour(Slider::trackColourId, Colour(_currentTheme.getButtonColor()));
	_frequencySlider.setColour(Slider::textBoxBackgroundColourId, Colour(_currentTheme.getBackgroundColor()));
	_frequencySlider.setColour(Slider::textBoxTextColourId, Colour(_currentTheme.getFontColor()));


	_drumsButton->setColour(ToggleButton::textColourId, Colour(_currentTheme.getFontColor()));
	_drumsButton->setColour(ToggleButton::tickColourId, Colour(_currentTheme.getFontColor()));
	_drumsButton->setColour(ToggleButton::tickDisabledColourId, Colour(_currentTheme.getFontColor()));
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
	for (int i = 0; i < _instrusChoice.size(); i++)
	{
		String buttonText = _instrusChoice[i];
		ToggleButton *btn = new ToggleButton(buttonText);
		btn->setName("Arpeges");
		btn->addListener(this);
		btn->setBounds(10, 100 * i, 100, 100);
		addAndMakeVisible(btn);
		btn->setColour(ToggleButton::textColourId, Colour(_currentTheme.getFontColor()));
		btn->setColour(ToggleButton::tickColourId, Colour(_currentTheme.getFontColor()));
		btn->setColour(ToggleButton::tickDisabledColourId, Colour(_currentTheme.getFontColor()));
		_arpegesList.add(btn);
	}
}



void MainContentComponent::initChordsList()
{
	for (int i = 0; i < _instrusChoice.size(); i++)
	{
		String buttonText = _instrusChoice[i];
		ToggleButton *btn = new ToggleButton(buttonText);
		btn->setName("Chords");
		btn->addListener(this);
		btn->setBounds(100 * i, 10, 100, 100);
		addAndMakeVisible(btn);
		btn->setColour(ToggleButton::textColourId, Colour(_currentTheme.getFontColor()));
		btn->setColour(ToggleButton::tickColourId, Colour(_currentTheme.getFontColor()));
		btn->setColour(ToggleButton::tickDisabledColourId, Colour(_currentTheme.getFontColor()));
		_chordsList.add(btn);
	}
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
		_player.newParams(_musicParameters);
		_player.Play(_musicParameters);
	}

	else if (button->getName() == "Arpeges")
	{
		std::cout << "Arpeges: " << button->getButtonText() << " " << button->getToggleState() << std::endl;
		Instrument instru;
		//TODO Set Instrument
		instru.name = button->getButtonText().toStdString();
		instru.nb = instrumentList.at(instru.name);
		instru.channel = instru.nb;
		instru.velocity = 100; //Need change
		if (button->getToggleState())
			_musicParameters.addInstrumentArpeggios(instru);
		else
			_musicParameters.delInstrumentArpeggios(instru);
	}

	else if (button->getName() == "Chords")
	{
		std::cout << "Chords: " << button->getButtonText() << " " << button->getToggleState() << std::endl;
		Instrument instru;
		//TODO CHECK THIS 
		instru.name = button->getButtonText().toStdString();
		instru.nb = instrumentList.at(instru.name);
		instru.channel = instru.nb;
		instru.velocity = 100; //Need change
		if (button->getToggleState())
			_musicParameters.addInstrumentChords(instru);
		else
			_musicParameters.delInstrumentChords(instru);

	}

	else if (button->getName() == "Drums")
	{
		_musicParameters.setInstrumentDrums(button->getToggleState());
	}

	
}

