/*
  ==============================================================================

    ViewManager.cpp
    Created: 21 Mar 2017 2:05:39pm
    Author:  Anthony

  ==============================================================================
*/

#include "ViewManager.hh"

ViewManager::ViewManager()
{
	_graph = new JuceManager();

}

ViewManager::~ViewManager()
{
	delete _graph;
}

bool ViewManager::init()
{
	_graph->setWinName("Barde");
	_graph->init();
	return (true);
}
