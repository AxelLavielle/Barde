/*
  ==============================================================================

    ViewManager.h
    Created: 21 Mar 2017 2:05:39pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef VIEWMANAGER_HH_INCLUDED
#define VIEWMANAGER_HH_INCLUDED

#include "../GraphManager/JuceManager.hh"

class ViewManager
{
public:
	ViewManager();
	~ViewManager();
	bool init();
private:
	IGraphManager	*_graph;
};

#endif  // VIEWMANAGER_HH_INCLUDED
