/*
  ==============================================================================

    Theme.cpp
    Created: 15 Jul 2017 2:22:21pm
    Author:  Oreo

  ==============================================================================
*/

#include "Theme.h"



Theme::Theme()
{
	_buttonColor = 0xFFD2005F;
	_backgroundColor = 0xFFFFFFFF;
	_fontColor = 0xFF304B69; 
	_buttonFontColor = 0xFFFFFFFF;
	_name = "Default";
}

Theme::Theme(int buttonColor, int backgroundColor, int fontColor, int buttonFontColor, std::string name)
{
	_buttonColor = buttonColor;
	_backgroundColor = backgroundColor;
	_fontColor = fontColor;
	_buttonFontColor = buttonFontColor;
	_name = name;
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

void Theme::setName(std::string name)
{
	_name = name;
}

Theme parseTheme(std::string fileName)
{
	Theme tmp;
	std::string line;
	std::string name;
	std::string button;
	std::string background;
	std::string font;
	std::string buttonFont;
	std::ifstream myfile;
	myfile.open(fileName, std::ifstream::in);

	std::cout << "Reading Theme File :" << fileName << std::endl;
	if (myfile.is_open())
	{
		getline(myfile, name);
		getline(myfile, button);
		getline(myfile, background);
		getline(myfile, font);
		getline(myfile, buttonFont);
		std::cout << name << " " << button << " " << background << " " << font << " " << buttonFont << std::endl;
		myfile.close();
	}
	else
	{
		std::cout << "MDR DIDNT WORKED" << std::endl;
		return Theme();
	}
	
	int iButton = static_cast<int>(std::stoll(button, nullptr, 16));
	int iBackground = static_cast<int>(std::stoll(background,0,0));
	int iFont = static_cast<int>(std::stoll(font,0,0));
	int iButtonFont = static_cast<int>(std::stoll(buttonFont, 0, 16));
	tmp = Theme(iButton, iBackground, iFont, iButtonFont, name);
	return tmp;
}

