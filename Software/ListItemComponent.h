/*
  ==============================================================================

    ListItemComponent.h
    Created: 29 Apr 2018 3:47:39pm
    Author:  Oreo

  ==============================================================================
*/

#ifndef LISTITEMCOMPONENT_H_INCLUDED
#define LISTITEMCOMPONENT_H_INCLUDED


#include "../JuceLibraryCode/JuceHeader.h"

class ListItemComponent : public Component
{
public:
	//==============================================================================
	ListItemComponent();
	~ListItemComponent();

	void paint(Graphics&) override;
	String getText();
	void setText(String text);
	bool isSelected();
	void setSelected(bool selected);
private:
	String _text;
	bool _isSelected;
	int rowNumber;
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ListItemComponent)
};


#endif  // LISTITEMCOMPONENT_H_INCLUDED
