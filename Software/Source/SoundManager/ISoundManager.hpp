/*
  ==============================================================================

    ISoundManager.hpp
    Created: 13 Mar 2017 1:41:42pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef ISOUNDMANAGER_HPP_INCLUDED
#define ISOUNDMANAGER_HPP_INCLUDED
#include <iostream>

class ISoundManager
{
public:
	virtual ~ISoundManager() {};
	virtual bool play(std::string midi) = 0;
	virtual bool stop(std::string midi) = 0;
	virtual bool pause(std::string midi) = 0;
	virtual bool setVolume(const int volume) = 0;
	virtual bool stopAll() = 0;
};



#endif  // ISOUNDMANAGER_HPP_INCLUDED
