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

class MainWindow : public  DocumentWindow
{
public:
	MainWindow(const std::string &name);
	void closeButtonPressed() override;
	~MainWindow();

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};



#endif  // MAINWINDOW_HH_INCLUDED
