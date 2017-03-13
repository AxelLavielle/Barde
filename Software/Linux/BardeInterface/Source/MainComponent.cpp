/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (600, 400);
}

MainContentComponent::~MainContentComponent()
{
	startJazzButton.removeListener(this);
}

void MainContentComponent::paint (Graphics& g)
{
  int imgX;
  int imgY;
  int imgH;
  int imgW;
  int ratio;
  
  ratio = 5;
  imgH = 927 / ratio;
  imgW = 1024 / ratio;
  imgX = (getWidth() / 2) - (imgW / 2);
  imgY = (getHeight() / 15);

    g.setColour (Colours::white);
    Image logo = ImageCache::getFromMemory (BinaryData::logo_png,    
					      BinaryData::logo_pngSize);
    Image background = ImageCache::getFromMemory(BinaryData::back_png, BinaryData::back_pngSize);
    g.drawImage(background, 0, 0, getWidth(), getHeight(), 0, 0, 2050, 1600, false);
    g.drawImage(logo, imgX, imgY, imgW, imgH, 0, 0, 1024, 927, false);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

