/*
  ==============================================================================

    GuiFactory.h
    Created: 25 May 2018 12:45:54am
    Author:  Anthony

  ==============================================================================
*/

#ifndef __GUIFACTORY__
#define __GUIFACTORY__

#include "../GraphManager/SimpleLabel.hh"
#include "../GraphManager/FlexGroup.hh"
#include "../GraphManager/Theme.h"
#include "../GraphManager/LabeledTextBox.hh"

#define BIG_TITLE_SIZE	50
#define MEDIUM_TITLE_SIZE	30
#define LITTLE_TITLE_SIZE	20
#define LEGEND_LABEL_SIZE	10
#define LABEL_HEIGHT_PADDING 5
#define LABEL_WIDTH_PADDING 10

class GuiFactory
{
public:
	static FlexBox createFlexBox(const FlexBox::JustifyContent & justifyContent, const FlexBox::AlignContent & alignContent,
							const FlexBox::AlignItems & alignItems, const FlexBox::Direction & direction,
							const std::vector<FlexItem> & items,
							const FlexBox::Wrap & wrap = FlexBox::Wrap::noWrap);
	static FlexBox createFlexBox(const FlexBox::JustifyContent & justifyContent, const FlexBox::AlignContent & alignContent,
							const FlexBox::AlignItems & alignItems, const FlexBox::Direction & direction,
							std::vector<FlexItem> & items,
							const float maxWidth, const float maxHeight, const FlexBox::Wrap & wrap = FlexBox::Wrap::noWrap);

	static FlexBox createRowCenterFlexBox(const std::vector<FlexItem> & items);
	
	
	
	static FlexItem createFlexItem(Component & component, const float minWidth = 0.f, const float minHeight = 0.f,
										const FlexItem::AlignSelf & alignSelf = FlexItem::AlignSelf::autoAlign, const float flexGrow = 0.f);
	static FlexItem createFlexItemLabel(SimpleLabel & label, const FlexItem::AlignSelf & alignSelf = FlexItem::AlignSelf::autoAlign, const float flexGrow = 0.f);
	static FlexItem createFlexItem(Component & component, const float maxWidth, const float maxHeight,
										const float minWidth, const float minHeight,
										const FlexItem::AlignSelf & alignSelf = FlexItem::AlignSelf::autoAlign, const float flexGrow = 0.f);



	static void initBigTitle(const std::string & text, SimpleLabel & label);
	static void initMediumTitle(const std::string & text, SimpleLabel & label);
	static void initLittleTitle(const std::string & text, SimpleLabel & label);
	static void initLegendLabel(const std::string & text, SimpleLabel & label);
	static float getBoxLabelHeight(const SimpleLabel & label);
	static float getBoxLabelWidth(const SimpleLabel & label);


	static void initToggleButton(const std::string & text, const std::string & name, ToggleButton & button, const bool state = false);

	static void initFlexGroup(const FlexBox::JustifyContent & justifyContent, const FlexBox::AlignContent & alignContent,
									const FlexBox::AlignItems & alignItems, const FlexBox::Direction & direction,
									const std::vector<FlexItem> & items,
									FlexGroup & group);
	static void initVerticalFlexGroup(const std::vector<FlexItem>& items, FlexGroup & group);
	static void initHoryzontalFlexGroup(const std::vector<FlexItem> & items,
											FlexGroup & group);

	static void initSlider(const float min, const float max, const float value, Slider & slider);

	static void initLabeledTextBox(const std::string & labelText, const std::string &boxText, LabeledTextBox & textBox);
	static void initLabeledTextBoxPassword(const std::string & labelText, const std::string & boxText, const juce_wchar &character, LabeledTextBox & textBox);
};

#endif