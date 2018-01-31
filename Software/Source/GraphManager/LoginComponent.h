/*
  ==============================================================================

    LoginComponent.h
    Created: 13 Jan 2018 2:36:43pm
    Author:  Oreo

  ==============================================================================
*/


#ifndef LOGINCOMPONENT_H_INCLUDED
#define LOGINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Theme.h"

#define LOGO_WIDTH 1024 / 3
#define LOGO_HEIGHT 927 / 3
#define BOX_WIDTH 400
#define BOX_HEIGHT 30
#define SPACE_BETWEEN 50
//==============================================================================
/*
This component lives inside our window, and this is where you should put all
your controls and content.
*/
class LoginComponent : public Component, private TextEditor::Listener, public Button::Listener
{
public:
	//==============================================================================
	LoginComponent();
	~LoginComponent();

	void paint(Graphics&) override;
	void resized() override;
	void buttonClicked(Button* button) override;

private:
	TextEditor textEditor1, textEditor2;
	Label inputLabel1, inputLabel2;
	ComboBox comboBox;
	Label errorText;
	TextButton loginButton;
	Theme currentTheme;
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LoginComponent)
};


#endif  // LOGINCOMPONENT_H_INCLUDED
