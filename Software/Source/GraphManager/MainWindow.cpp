/*
  ==============================================================================

    MainWindow.cpp
    Created: 6 Mar 2017 1:48:11pm
    Author:  Anthony

  ==============================================================================
*/

#include "MainWindow.hh"

MainWindow::MainWindow(const std::string &name) : _cmdManager(CmdManager::getInstance()), DocumentWindow(name,
																Colours::lightgrey,
																DocumentWindow::allButtons)
{
	setUsingNativeTitleBar(true);
	setResizable(true, false);
	//setResizable(false, false);
	setFullScreen(true);
	//setSize(getWidth(), getHeight() - 100);
	//setSize(getWidth(), getHeight()-10);


	_cmdManager.connectToServer();

#ifdef DEBUG
	//_cmdManager.login("micha@barde.io", "Micha@barde.io1");
	//_cmdManager.login("aot@aot.com", "-aMmvqHy42");
	//Init all the components
	_mainComponent = new MainContentComponent();
	_loginComponent = new LoginComponent(_cmdManager);
	_userRegistration = new UserRegistration(_cmdManager);
	_forgotComponent = new ForgotComponent(_cmdManager);
	_forgotComponent->setChangeViewCallback(std::bind(&MainWindow::changeViewCallback, this, std::placeholders::_1));
	_mainComponent->setChangeViewCallback(std::bind(&MainWindow::changeViewCallback, this, std::placeholders::_1));
	_loginComponent->setChangeViewCallback(std::bind(&MainWindow::changeViewCallback, this, std::placeholders::_1));
	_userRegistration->setChangeViewCallback(std::bind(&MainWindow::changeViewCallback, this, std::placeholders::_1));
	//setContentNonOwned(_mainComponent, true);
	setContentNonOwned(_loginComponent, true);
#else
	//Init all the components
	_mainComponent = new MainContentComponent();
	_loginComponent = new LoginComponent(_cmdManager);
	_userRegistration = new UserRegistration(_cmdManager);
	_forgotComponent = new ForgotComponent(_cmdManager);
	_mainComponent->setChangeViewCallback(std::bind(&MainWindow::changeViewCallback, this, std::placeholders::_1));
	_loginComponent->setChangeViewCallback(std::bind(&MainWindow::changeViewCallback, this, std::placeholders::_1));
	_userRegistration->setChangeViewCallback(std::bind(&MainWindow::changeViewCallback, this, std::placeholders::_1));
	setContentNonOwned(_loginComponent, true);
#endif // DEBUG


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
	delete _loginComponent;

	//deleteAllChildren();
}

void MainWindow::changeViewCallback(std::string viewName)
{
	if (viewName == "Player")
	{
		clearContentComponent();
		_mainComponent->refresh();
		setContentNonOwned(_mainComponent, true);
	}
	else if (viewName == "Login")
	{
		clearContentComponent();
		_loginComponent->refresh();
		setContentNonOwned(_loginComponent, true);
	}
	else if (viewName == "Signup")
	{
		clearContentComponent();
		_userRegistration->refresh();
		setContentNonOwned(_userRegistration, true);
	}
	else if (viewName == "Forgot")
	{
		clearContentComponent();
		_forgotComponent->refresh();
		setContentNonOwned(_forgotComponent, true);
	}
	else if (viewName == "Logout")
	{
		_cmdManager.logout();
		clearContentComponent();
		_loginComponent->refresh();
		setContentNonOwned(_loginComponent, true);
	}
}
