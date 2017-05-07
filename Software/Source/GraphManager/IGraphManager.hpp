/*
  ==============================================================================

    IGraphManager.hpp
    Created: 6 Mar 2017 12:08:36pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef IGRAPHMANAGER_HPP_INCLUDED
#define IGRAPHMANAGER_HPP_INCLUDED

class IGraphManager
{
public:
	virtual ~IGraphManager() {};
	virtual int init(void) = 0;
	virtual int init(const std::string &winName, const unsigned int width, const unsigned int height) = 0;
	virtual void setWinHeight(const unsigned int height) = 0;
	virtual void setWinWidth(const unsigned int width) = 0;
	virtual void setWinName(const std::string &name) = 0;
};



#endif  // IGRAPHMANAGER_HPP_INCLUDED
