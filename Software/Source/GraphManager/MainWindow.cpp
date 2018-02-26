/*
  ==============================================================================

    MainWindow.cpp
    Created: 6 Mar 2017 1:48:11pm
    Author:  Anthony

  ==============================================================================
*/

#include "MainWindow.hh"
#include "MainComponent.h"
#include "LoginComponent.h"
#include "UserParamsComponent.h"
#include <sstream> 

MainWindow::MainWindow(const std::string &name) : DocumentWindow(name,
																Colours::lightgrey,
																DocumentWindow::allButtons)
{
	setUsingNativeTitleBar(true);
	setResizable(true, false);

#if JUCE_IOS || JUCE_ANDROID
	setFullScreen(true);
#endif
	setFullScreen(true);
	setSize(getWidth(), getHeight());
	//setContentOwned(new LoginComponent(), true);
	setContentOwned(new MainContentComponent(), true);
	//setContentOwned(new UserParamsComponent(), true);
	//centreWithSize(getWidth(), getHeight());
	setVisible(true);
}

void MainWindow::closeButtonPressed()
{
	// This is called when the user tries to close this window. Here, we'll just
	// ask the app to quit when this happens, but you can change this to do
	// whatever you need.
	JUCEApplication::getInstance()->systemRequestedQuit();
}

MainWindow::~MainWindow()
{
	//deleteAllChildren();
}
