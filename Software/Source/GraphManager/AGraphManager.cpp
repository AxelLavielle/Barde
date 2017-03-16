/*
  ==============================================================================

    AGraphManager.cpp
    Created: 6 Mar 2017 12:09:17pm
    Author:  Anthony

  ==============================================================================
*/

#include "AGraphManager.hh"

AGraphManager::AGraphManager()
{
	_winHeight = 10;
	_winHeight = 10;
}

AGraphManager::~AGraphManager()
{
}

void AGraphManager::setWinHeight(const unsigned int height)
{
	_winHeight = height;
}

void AGraphManager::setWinWidth(const unsigned int width)
{
	_winWidth = width;
}

void AGraphManager::setWinName(const std::string &name)
{
		_winName = name;
}
