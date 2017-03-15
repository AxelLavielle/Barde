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
}

JuceManager::~JuceManager()
{
}

int JuceManager::init(void)
{
	_mainWindow = new MainWindow("Barde");
	return (0);
}
