/*
  ==============================================================================

    ForgotComponent.h
    Created: 26 Sep 2018 11:48:34pm
    Author:  Oreo

  ==============================================================================
*/



#ifndef FORGOTOMPONENT_H_INCLUDED
#define FORGOTCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Theme.h"
#include "../CmdManager.hh"
#include "AComponent.hh"

#define BOX_WIDTH 400
#define BOX_HEIGHT 30
#define SPACE_BETWEEN 50
//==============================================================================
/*
This component lives inside our window, and this is where you should put all
your controls and content.
*/
class ForgotComponent : public AComponent, private TextEditor::Listener, private Button::Listener, private ComboBox::Listener
{
public:
	//==============================================================================
	ForgotComponent(CmdManager & cmdManager);
	~ForgotComponent();

private:
	void paint(Graphics&) override;
	void resized() override;
	void buttonClicked(Button* button) override;
	void comboBoxChanged(ComboBox * comboBoxThatHasChanged) override;
	void ThemeChanged();
	void forgot(const std::string & login, const std::string & password);

	CmdManager	&_cmdManager;
	TextEditor	_textEditor1, _textEditor2;
	Label		_inputLabel1, _inputLabel2;
	ComboBox	_comboBox;
	Label		_errorText;
	TextButton	_loginButton;
	TextButton	_signinButton;
	TextButton	_forgotPasswordButton;
	ImageComponent _logo;
	//static Theme		_currentTheme;
	ComboBox	_themeChoice;
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ForgotComponent)
};


#endif  // FORGOTCOMPONENT_H_INCLUDED