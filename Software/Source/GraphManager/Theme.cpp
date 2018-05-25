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
	_buttonColor = 0xFFD2005F;
	_backgroundColor = 0xFFFFFFFF;
	_fontColor = 0xFF304B69; 
	_buttonFontColor = 0xFFFFFFFF;
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
		int iButton = static_cast<int>(std::stoll(button, nullptr, 16));
		int iBackground = static_cast<int>(std::stoll(background, 0, 0));
		int iFont = static_cast<int>(std::stoll(font, 0, 0));
		int iButtonFont = static_cast<int>(std::stoll(buttonFont, 0, 16));
		setBackgroundColor(iBackground);
		setButtonColor(iButton);
		setButtonFontColor(iButtonFont);
		setFontColor(iFont);
		setName(name);
	}
	else
	{
		//throw std::runtime_error("Couldn't find or read file [" + fileName + "]");
	}
	
	
}

