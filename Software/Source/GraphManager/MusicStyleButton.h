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

class MusicStyleButton : public Button
{
public:
	MusicStyleButton(const String &buttonName);
	~MusicStyleButton();
	
	void paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown);
};

#endif  // MUSICSTYLEBUTTON_H_INCLUDED
