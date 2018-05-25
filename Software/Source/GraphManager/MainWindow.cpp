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
	setFullScreen(true);
	setSize(getWidth(), getHeight());

	//Init all the components
	_mainComponent = new MainContentComponent();
	_userParamsComponent = new UserParamsComponent();
	_loginComponent = new LoginComponent(_cmdManager);
	_userRegistration = new UserRegistration(_cmdManager);
	_mainComponent->setChangeViewCallback(std::bind(&MainWindow::changeViewCallback, this, std::placeholders::_1));
	_userParamsComponent->setChangeViewCallback(std::bind(&MainWindow::changeViewCallback, this, std::placeholders::_1));
	_loginComponent->setChangeViewCallback(std::bind(&MainWindow::changeViewCallback, this, std::placeholders::_1));
	_userRegistration->setChangeViewCallback(std::bind(&MainWindow::changeViewCallback, this, std::placeholders::_1));

	setContentNonOwned(_mainComponent, true);
	//setContentNonOwned(_loginComponent, true);
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
	delete _mainComponent;
	delete _userParamsComponent;
	delete _loginComponent;

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
		//clearContentComponent();
		//setContentNonOwned(_userParamsComponent, true);
	}
	else if (viewName == "Login")
	{
		clearContentComponent();
		setContentNonOwned(_loginComponent, true);
	}
	else if (viewName == "Signin")
	{
		clearContentComponent();
		setContentNonOwned(_userRegistration, true);
	}
}
