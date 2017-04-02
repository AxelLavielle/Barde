/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MusicStyleButton.h"


#define LOGO_WIDTH 1024 / 2
#define LOGO_HEIGHT 927 / 2
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

/*! \class MainContentComponent
* \brief classe representant le composant principal du client graphique
*
*  La classe gere tous les sous composants représentant la fenêtre graphique du client
*/

class MainContentComponent   : public Component
{
public:
    //==============================================================================
	MusicStyleButton *blues;  /*!< bouton pour générer le blues*/

	/*!
	*  \brief Constructeur
	*
	*  Constructeur de la classe MainContentComponent
	*
	*/
	MainContentComponent();

	/*!
	*  \brief Destructeur
	*
	*  Destructeur de la classe MusicStyleButton
	*/
    ~MainContentComponent();

	/*!
	*  \brief Affichage
	*
	* Fonction appelée pour l'affichage de la fenêtre
	*/
    void paint (Graphics&) override;

	/*!
	*  \brief Resized
	*
	* Fonction appelée lors du changement de taille de la fenêtre
	*/
    void resized() override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
