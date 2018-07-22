/*
  ==============================================================================

    Theme.cpp
    Created: 15 Jul 2017 2:22:21pm
    Author:  Oreo

  ==============================================================================
*/

#include "Theme.h"

Theme Theme::_theme;

Theme &Theme::getInstance()
{
	return _theme;
}


Theme::Theme()
{
	_buttonColor = 0xFFFFFFFF;
	_backgroundColor = 0xFFCA5E85;
	_fontColor = 0xFFFFFFFF;
	_buttonFontColor = 0xFFD2005F;
	_sliderOnColor = 0xFFD2005F;
	_sliderOffColor = 0xFFFFFFFF;
	_sliderPointerColor = 0xFFD2005F;
	_clueColor = 0xFFB7B7B7;
	_errorTextColor = 0xFF770000;
	//_buttonColor = 0xFFD2005F;
	//_backgroundColor = 0xFFFFFFFF;
	//_fontColor = 0xFF304B69; 
	//_buttonFontColor = 0xFFFFFFFF;
	_name = "Default";
}

Theme::~Theme()
{

}

int Theme::getButtonColor()
{
	return (_buttonColor);
}

int Theme::getBackgroundColor()
{
	return (_backgroundColor);
}

int Theme::getFontColor()
{
	return (_fontColor);
}

int Theme::getButtonFontColor()
{
	return (_buttonFontColor);
}



int Theme::getSliderOnColor()
{
	return _sliderOnColor;
}

int Theme::getSliderOffColor()
{
	return _sliderOffColor;
}

int Theme::getSliderPointerColor()
{
	return _sliderPointerColor;
}

int Theme::getClueColor()
{
	return _clueColor;
}

int Theme::getErrorTextColor()
{
	return _errorTextColor;
}



std::string Theme::getName()
{
	return (_name);
}

void Theme::setButtonColor(int color)
{
	_buttonColor = color;
}

void Theme::setBackgroundColor(int color)
{
	_backgroundColor = color;
}

void Theme::setFontColor(int color)
{
	_fontColor = color;
}

void Theme::setButtonFontColor(int color)
{
	_buttonFontColor = color;
}

void Theme::setSliderOnColor(int color)
{
	_sliderOnColor = color;
}

void Theme::setSliderOffColor(int color)
{
	_sliderOffColor = color;
}


void Theme::setSliderPointerColor(int color)
{
	_sliderPointerColor = color;
}

void Theme::setClueColor(int color)
{
	_clueColor = color;
}

void Theme::setErrorTextColor(int color)
{
	_errorTextColor = color;
}


void Theme::setName(const std::string &name)
{
	_name = name;
}

void Theme::parseTheme(const std::string &fileName)
{
	std::ifstream myfile(fileName.c_str());
	std::string line;
	std::string name;
	std::string button;
	std::string background;
	std::string font;
	std::string buttonFont;
	std::string sliderOn;
	std::string sliderOff;
	std::string sliderPointer;
	std::string clue;
	std::string errorText;

	std::cout << "Reading Theme File :" << fileName << std::endl;
	if (myfile.is_open())
	{
		getline(myfile, name);
		getline(myfile, button);
		getline(myfile, background);
		getline(myfile, font);
		getline(myfile, buttonFont);
		getline(myfile, sliderOn);
		getline(myfile, sliderOff);
		getline(myfile, sliderPointer);
		getline(myfile, clue);
		getline(myfile, errorText);

		std::cout << "Theme name: "<< name << " Button color: " << button << " Background color: " << background << " Font color: " << font << " Button Font: " << buttonFont << std::endl;
		myfile.close();
		int iButton = static_cast<int>(std::stoll(button, nullptr, 16));
		int iBackground = static_cast<int>(std::stoll(background, 0, 0));
		int iFont = static_cast<int>(std::stoll(font, 0, 0));
		int iButtonFont = static_cast<int>(std::stoll(buttonFont, 0, 16));
		int iSliderOn = static_cast<int>(std::stoll(sliderOn, 0, 16));
		int iSliderOff = static_cast<int>(std::stoll(sliderOff, 0, 16));
		int iSliderPointer = static_cast<int>(std::stoll(sliderPointer, 0, 16));
		int iClue = static_cast<int>(std::stoll(clue, 0, 16));
		int iErrorText = static_cast<int>(std::stoll(errorText, 0, 16));
		setBackgroundColor(iBackground);
		setButtonColor(iButton);
		setButtonFontColor(iButtonFont);
		setFontColor(iFont);
		setSliderOnColor(iSliderOn);
		setSliderOffColor(iSliderOff);
		setSliderPointerColor(iSliderPointer);
		setClueColor(iClue);
		setErrorTextColor(iErrorText);
		setName(name);
	}
	else
	{
		//throw std::runtime_error("Couldn't find or read file [" + fileName + "]");
	}
	
	
}

