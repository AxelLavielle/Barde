/*
  ==============================================================================

    MainWindow.cpp
    Created: 6 Mar 2017 1:48:11pm
    Author:  Anthony

  ==============================================================================
*/

#include "MainWindow.hh"

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
	_mainComponent = new MainContentComponent();
	_userParamsComponent = new UserParamsComponent();
	_loginComponent = new LoginComponent();
	//_userRegistration = new UserRegistration();

	_mainComponent->setChangeViewCallback(std::bind(&MainWindow::changeViewCallback, this, std::placeholders::_1));

	setContentNonOwned(_mainComponent, true);

	//setContentOwned(new LoginComponent(), true);
	//setContentOwned(new MainContentComponent(), true);
	//setContentOwned(new UserParamsComponent(), true);
	//setContentOwned(new UserRegistration(), true);
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

void MainWindow::changeViewCallback(std::string viewName)
{
	if (viewName == "Main")
	{
		clearContentComponent();
		setContentNonOwned(_mainComponent, true);
	}
	else if (viewName == "UserParams")
	{
		clearContentComponent();
		setContentNonOwned(_userParamsComponent, true);
	}
}
