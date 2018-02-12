/*
  ==============================================================================

    ISockerManager.hpp
    Created: 13 Mar 2017 1:51:42pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef ISOCKERMANAGER_HPP_INCLUDED
#define ISOCKERMANAGER_HPP_INCLUDED

#include <string>

class IRestTClient
{
public:
	virtual void setAddr(const std::string & address, const unsigned int port, unsigned int timeOut) = 0;
	virtual std::string get(const std::string &uri) = 0;
};


#endif  // ISOCKERMANAGER_HPP_INCLUDED
