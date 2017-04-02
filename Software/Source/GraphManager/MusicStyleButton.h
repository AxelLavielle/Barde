/*
  ==============================================================================

    MusicStyleButton.h
    Created: 14 Mar 2017 3:21:14pm
    Author:  Oreo

  ==============================================================================
*/

#ifndef MUSICSTYLEBUTTON_H_INCLUDED
#define MUSICSTYLEBUTTON_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Player.hh"


/*! \class MusicStyleButton
* \brief classe representant un bouton de style musical
*
*  La classe gere la cr�ation de bouton pour un style musical
*/
class MusicStyleButton : public Button
{
public:
	int width; /*!< largeur du bouton*/
	int height; /*!< hauteur du bouton*/

	/*!
	*  \brief Constructeur
	*
	*  Constructeur de la classe MusicStyleButton
	*
	*  \param buttonName : nom du bouton / texte � afficher
	*  \param w : largeur du bouton
	*  \param h : heuteur du bouton
	*/
	MusicStyleButton(const String &buttonName, const int w, const int h);
	/*!
	*  \brief Destructeur
	*
	*  Destructeur de la classe MusicStyleButton
	*/
	~MusicStyleButton();
	
	/*!
	*  \brief Affichage du bouton
	*
	*  Fonction qui s'occupe de l'affichage du bouton en fonctions de diff�rents �v�nements
	*
	*  \param g : graphique o� le bouton sera affich�
	*  \param isMouseOverButton : bool�en correspondant � l'�v�nement de la souris sur le bouton
	*  \param isButtonDown : bool�en correspondant � l'enfoncement du bouton
	*/
	void paintButton(Graphics& g, const bool isMouseOverButton, const bool isButtonDown);
};

#endif  // MUSICSTYLEBUTTON_H_INCLUDED
