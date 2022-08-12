#ifndef APP_STATE_INTRO_H
#define APP_STATE_INTRO_H

/*=INCLUSION=================================================================*/
#include "define.h"
#include "state.h"

/*=CONSTANTES================================================================*/
#define SPEED_EFFECT 1
#define MAX_IMAGE 2

enum FADE_STATE {
	FADE_IN,
	FADE_OUT
};

enum INTRO_IMAGE {
	EDITOR,
	GAME
};

/*=VARIABLES=================================================================*/
//Permet de quitter l'animation en appuyrant sur une touche
bool continueAnimation;

//Arri�re-fond de d�marrage
SDL_Surface* backgroundSurface;
SDL_Surface* editorSurface;

//Permet de connaitre dans quelle �tat de fondu on se trouve
int fadeState;

//Image de fond courant
int currentImage;

/*=PROTOTYPES================================================================*/
//Valeur de transparence
unsigned int alpha;

//Charge le state
void introOnLoad();

//Gestion des �v�nements
void introOnEvent(SDL_Event* event);

//Effectue le rendu
void introOnRender();

//Boucle de mise � jour des donn�es
void introOnLoop();

//Lib�re la m�moire
void introOnQuit();

#endif /*APP_STATE_INTRO_H*/
