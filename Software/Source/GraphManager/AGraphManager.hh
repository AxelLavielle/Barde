/*
  ==============================================================================

    AGraphManager.h
    Created: 6 Mar 2017 12:09:17pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef AGRAPHMANAGER_HH_INCLUDED
#define AGRAPHMANAGER_HH_INCLUDED

#include <string>
#include "IGraphManager.hpp"

class AGraphManager : public IGraphManager
{
public:
	AGraphManager();
	virtual ~AGraphManager();

	virtual int init(void) = 0;
	virtual int init(const std::string &winName, const unsigned int width, const unsigned int height) = 0;
	virtual void setWinHeight(const unsigned int height);
	virtual void setWinWidth(const unsigned int width);
	virtual void setWinName(const std::string &name);

protected:
	int 						_winHeight;
	int 						_winWidth;
	std::string					_winName;
};



#endif  // AGRAPHMANAGER_HH_INCLUDED
