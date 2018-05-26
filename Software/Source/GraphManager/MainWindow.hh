/*
  ==============================================================================

    MainWindow.h
    Created: 6 Mar 2017 1:48:11pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef MAINWINDOW_HH_INCLUDED
#define MAINWINDOW_HH_INCLUDED

#include "JuceHeader.h"
#include <sstream> 
#include "MainComponent.h"
#include "LoginComponent.h"
#include "UserRegistration.h"

class MainWindow : public  DocumentWindow, public ComponentListener
{
public:
	MainWindow(const std::string &name);
	void closeButtonPressed() override;
	~MainWindow();
	void changeViewCallback(std::string viewName);

private:
	MainContentComponent	*_mainComponent;
	LoginComponent			*_loginComponent;
	UserRegistration		*_userRegistration;
	CmdManager				_cmdManager;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};



#endif  // MAINWINDOW_HH_INCLUDED
