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
#include "../CmdManager.hh"
#include "AComponent.hh"

#ifndef  LOGO_WIDTH
#define LOGO_WIDTH 1024 / 3
#endif
#ifndef  LOGO_HEIGHT
#define LOGO_HEIGHT 927 / 3
#endif
#define BOX_WIDTH 400
#define BOX_HEIGHT 30
#define SPACE_BETWEEN 50
//==============================================================================
/*
This component lives inside our window, and this is where you should put all
your controls and content.
*/
class LoginComponent : public Component, public AComponent, private TextEditor::Listener, private Button::Listener, private ComboBox::Listener
{
public:
	//==============================================================================
	LoginComponent();
	~LoginComponent();

	void paint(Graphics&) override;
	void resized() override;
	void buttonClicked(Button* button) override;
	void comboBoxChanged(ComboBox * comboBoxThatHasChanged) override;
	void ThemeChanged();

private:
	CmdManager	_cmdManager;
	TextEditor	_textEditor1, _textEditor2;
	Label		_inputLabel1, _inputLabel2;
	ComboBox	_comboBox;
	Label		_errorText;
	TextButton	_loginButton;
	Theme		_currentTheme;
	ComboBox	_themeChoice;
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LoginComponent)
};


#endif  // LOGINCOMPONENT_H_INCLUDED
