/*
  ==============================================================================

    MusicStyleButton.h
    Created: 14 Mar 2017 3:21:14pm
    Author:  Oreo

  ==============================================================================
*/

#ifndef MUSICSTYLEBUTTON_H_INCLUDED
#define MUSICSTYLEBUTTON_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Player.hh"

class MusicStyleButton : public Button
{
public:
	int width;
	int height;
	MusicStyleButton(const String &buttonName, const int w, const int h);
	~MusicStyleButton();
	
	void paintButton(Graphics& g, const bool isMouseOverButton, const bool isButtonDown);
};

#endif  // MUSICSTYLEBUTTON_H_INCLUDED
