/*
  ==============================================================================

    GuiFactory.h
    Created: 25 May 2018 12:45:54am
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "../GraphManager/SimpleLabel.hh"
#include "../GraphManager/FlexGroup.hh"
#include "../GraphManager/Theme.h"

#define BIG_TITLE_SIZE	50
#define MEDIUM_TITLE_SIZE	30
#define LITTLE_TITLE_SIZE	20
#define LABEL_HEIGHT_PADDING 5
#define LABEL_WIDTH_PADDING 5

class GuiFactory
{
public:
	static FlexBox createFlexBox(const FlexBox::JustifyContent & justifyContent, const FlexBox::AlignContent & alignContent,
							const FlexBox::AlignItems & alignItems, const FlexBox::Direction & direction,
							const std::vector<FlexItem> & items,
							const FlexBox::Wrap & wrap = FlexBox::Wrap::noWrap);

	static FlexBox createRowCenterFlexBox(const std::vector<FlexItem> & items);
	
	
	
	static FlexItem createFlexItem(Component & component, const float minWidth = 0.f, const float minHeight = 0.f,
										const FlexItem::AlignSelf & alignSelf = FlexItem::AlignSelf::autoAlign, const float flexGrow = 0.f);
	static FlexItem createFlexItem(Component & component, const float maxWidth, const float maxHeight,
										const float minWidth, const float minHeight,
										const FlexItem::AlignSelf & alignSelf = FlexItem::AlignSelf::autoAlign, const float flexGrow = 0.f);


	static void initBigTitle(const std::string & text, SimpleLabel & label);
	static void initMediumTitle(const std::string & text, SimpleLabel & label);
	static void initLittleTitle(const std::string & text, SimpleLabel & label);
	static float getBoxLabelHeight(const SimpleLabel & label);
	static float getBoxLabelWidth(const SimpleLabel & label);

	static void initToggleButton(const std::string & text, const std::string & name, ToggleButton & button);

	static void initFlexGroup(const FlexBox::JustifyContent & justifyContent, const FlexBox::AlignContent & alignContent,
									const FlexBox::AlignItems & alignItems, const FlexBox::Direction & direction,
									const std::vector<FlexItem> & items,
									FlexGroup & group);
	static void initVerticalFlexGroup(const std::vector<FlexItem>& items, FlexGroup & group);
	static void initHoryzontalFlexGroup(const std::vector<FlexItem> & items,
											FlexGroup & group);
};