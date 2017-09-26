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
	_fontColor = 0xFFFFFFFF;
	_name = "Default";
}

Theme::Theme(int buttonColor, int backgroundColor, int fontColor, std::string name)
{
	_buttonColor = buttonColor;
	_backgroundColor = backgroundColor;
	_fontColor = fontColor;
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
	std::ifstream myfile;
	myfile.open(fileName, std::ifstream::in);

	std::cout << "Reading Theme File :" << fileName << std::endl;
	if (myfile.is_open())
	{
	  getline(myfile, name);
	  getline(myfile, button);
	  getline(myfile, background);
	  getline(myfile, font);
	  std::cout << name << " " << button << " " << background << " " << font << std::endl;
	  myfile.close();
	}
	else
	  return Theme();
	
	unsigned int iButton = std::stol (button,0,16);
	unsigned int iBackground = std::stol (background,0,16);
	unsigned int iFont = std::stol (font,0,16);
	tmp = Theme(iButton, iBackground, iFont, name);
	return tmp;
}

