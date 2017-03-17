/*
  ==============================================================================

    GraphManager.h
    Created: 6 Mar 2017 12:10:26pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef GRAPHMANAGER_HH_INCLUDED
#define GRAPHMANAGER_HH_INCLUDED

#include "AGraphManager.hh"
#include "MainWindow.hh"

class JuceManager : public AGraphManager
{
public:
	JuceManager();
	virtual ~JuceManager();

	virtual int init(void);
	virtual int init(const std::string &winName, const unsigned int width, const unsigned int height);

private:
	ScopedPointer<MainWindow> _mainWindow;
};



#endif  // GRAPHMANAGER_HH_INCLUDED
