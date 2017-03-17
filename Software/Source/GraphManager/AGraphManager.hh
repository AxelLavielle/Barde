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
	virtual void setWinName(const std::string &name);
	virtual std::string getWinName() const;
	virtual void setWinHeight(const int height);
	virtual void setWinWidth(const int width);


private:
	int				_winHeight;
	int				_winWidth;
	std::string		_winName;
};



#endif  // AGRAPHMANAGER_HH_INCLUDED
