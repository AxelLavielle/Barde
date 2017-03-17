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
}

AGraphManager::~AGraphManager()
{
}

void AGraphManager::setWinName(const std::string & name)
{
	_winName = name;
}

std::string AGraphManager::getWinName() const
{
	return (_winName);
}

void AGraphManager::setWinHeight(const int height)
{
	_winHeight = height;
}

void AGraphManager::setWinWidth(const int width)
{
	_winWidth = width;
}
