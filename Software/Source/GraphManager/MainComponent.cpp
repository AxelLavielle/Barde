/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "Theme.h"

//==============================================================================
MainContentComponent::MainContentComponent()
{
	int rectX;
	int rectY;
	Theme currentTheme;

	setSize(getParentWidth(), getParentHeight() - 10);
	currentTheme = parseTheme("../Themes/Dark");
	addAndMakeVisible(blues = new MusicStyleButton("Generate some blues", 400, 50));
	rectX = (600 / 2) - (400 / 2);
	rectY = (400 / 15) + (LOGO_WIDTH) + 100;
	blues->setBounds(rectX, rectY, 400, 50);
}

MainContentComponent::~MainContentComponent()
{
	deleteAllChildren();
}

void MainContentComponent::paint (Graphics& g)
{
  int imgX;
  int imgY;
  float imgH;
  float imgW;
  int rectX;
  int rectY;

  imgH = (LOGO_HEIGHT);
  imgW = (LOGO_WIDTH);

  imgX = (getWidth() / 2) - (imgW / 2);
  imgY = (getHeight() / 15);
  rectX = (getWidth() / 2) - (400 / 2);
  rectY = (getHeight() / 15) + (LOGO_HEIGHT) + 50;

	g.setColour (Colours::white);
    Image logo = ImageCache::getFromMemory (BinaryData::logo_png,    
					      BinaryData::logo_pngSize);
    Image background = ImageCache::getFromMemory(BinaryData::back_png, BinaryData::back_pngSize);
    g.drawImage(background, 0, 0, getWidth(), getHeight(), 0, 0, 2050, 1600, false);
    g.drawImage(logo, imgX, imgY, (int) imgW, (int) imgH, 0, 0, 1024, 927, false);
	blues->setBounds(rectX, rectY, 400, 50);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

