/*
  ==============================================================================

    GraphManager.cpp
    Created: 6 Mar 2017 12:10:26pm
    Author:  Anthony

  ==============================================================================
*/

#include "JuceManager.hh"

JuceManager::JuceManager() : AGraphManager()
{
	_mainWindow = nullptr;
}

JuceManager::~JuceManager()
{
	_mainWindow = nullptr;
}

int JuceManager::init(void)
{
	_mainWindow = new MainWindow(_winName);
	return (0);
}

int JuceManager::init(const std::string &winName,
											const unsigned int width,
											const unsigned int height)
{
	_winName = winName;
	_winWidth = width;
	_winHeight = height;
	_mainWindow = new MainWindow(_winName);
}
