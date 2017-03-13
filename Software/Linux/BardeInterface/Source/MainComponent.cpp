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
}

void MainContentComponent::paint (Graphics& g)
{
  int imgX;
  int imgY;
  int imgH;
  int imgW;
  int ratio;

  ratio = 5;
  imgH = 1024 / ratio;
  imgW = 927 / ratio;
  imgX = (getWidth() / 2) - (imgW / 2);
  imgY = (getHeight() / 15);

    g.fillAll (Colour (0xff001F36));
    g.setColour (Colours::white);
    Image logo = ImageCache::getFromMemory (BinaryData::logo_png,    
					      BinaryData::logo_pngSize);
    Image background = ImageCache::getFromMemory(BinaryData::back_png, BinaryData::back_pngSize);
    g.drawImage(background, 0, 0, 1000, 1000, 0, 0, 2050, 1600, false);
    g.drawImage(logo, imgX, imgY, imgH, imgW, 0, 0, 1024, 927, false);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
