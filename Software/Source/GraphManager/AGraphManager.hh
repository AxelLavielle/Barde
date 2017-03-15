/*
  ==============================================================================

    AGraphManager.h
    Created: 6 Mar 2017 12:09:17pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef AGRAPHMANAGER_HH_INCLUDED
#define AGRAPHMANAGER_HH_INCLUDED

#include "IGraphManager.hpp"

class AGraphManager : public IGraphManager
{
public:
	AGraphManager();
	virtual ~AGraphManager();

	virtual int init(void) = 0;
	void setWinHeight(const int height);
	void setWinWidth(const int width);

private:
	int _winHeight;
	int _winWidth;
};



#endif  // AGRAPHMANAGER_HH_INCLUDED
