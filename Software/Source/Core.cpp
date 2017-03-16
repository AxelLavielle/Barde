/*
  ==============================================================================

    Core.cpp
    Created: 6 Mar 2017 11:21:32am
    Author:  Anthony

  ==============================================================================
*/

#include "Core.hh"

Core::Core()
{
	_graph = new JuceManager();
}

Core::~Core()
{
}

int Core::launch(void)
{
	return (0);
}

void Core::initialise(const String& commandLine)
{
	MidiManager test;
	MusicGenerator gen;
	MusicParameters param;
	
	test.changeInstrument(1, 5, 0);
	test.noteOn(1, 38, 100, 0);
	test.noteOff(1, 38, 100, 500);
	//test.changeInstrument(4, 25, 200);
	//test.noteOn(4, 38, 100, 400);
	//test.noteOff(4, 38, 100, 700);
	//test.changeInstrument(4, 27, 700);
	//test.noteOn(4, 38, 100, 800);
	//test.noteOff(4, 38, 100, 1200);

	//test.changeInstrument(16, 128, 1300);	
	//test.noteOn(16, 38, 100, 1400);
	//test.noteOff(16, 38, 100, 1800);

	test.createMidi();
	test.writeToFile("./test.mid");
	gen.createMusic(param);

	_graph->init();
	// This method is where you should put your application's initialisation code..
	ignoreUnused(commandLine);
	//mainWindow = new MainWindow(getApplicationName());
}

void Core::shutdown()
{
	// Add your application's shutdown code here..

	//mainWindow = nullptr; // (deletes our window)
}

//==============================================================================
void Core::systemRequestedQuit()
{
	// This is called when the app is being asked to quit: you can ignore this
	// request and let the app carry on running, or call quit() to allow the app to close.
	quit();
}

void Core::anotherInstanceStarted(const String& commandLine)
{
	// When another instance of the app is launched while this one is running,
	// this method is invoked, and the commandLine parameter tells you what
	// the other instance's command-line arguments were.
	ignoreUnused(commandLine);
}

const String Core::getApplicationName()
{
	return (ProjectInfo::projectName);
}

const String Core::getApplicationVersion()
{
	return (ProjectInfo::versionString);
}

bool Core::moreThanOneInstanceAllowed() const
{
	return (true);
}