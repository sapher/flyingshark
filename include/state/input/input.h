#ifndef APP_STATE_INPUT_H
#define APP_STATE_INPUT_H

/*=INCLUSIONS================================================================*/
#include "define.h"
#include "state.h"
#include <SDL_gfxPrimitives.h>
#include <SDL_framerate.h>
/*=CONSTANTES================================================================*/
//Longueur du texte
#define INPUT_PADDING 5
#define TEXT_SIZE	18
#define POSITION_INPUT_Y	250
/*La position X de l'input texte est calculer pour �tre centr�e*/

/*=VARIABLES================================================================*/
//Texte de l'utilisateur
char buffer;

//Watcher
bool isDelete;
bool isSelect;

//Surface texte
SDL_Surface* textSurface;

//Surface Label
SDL_Surface* labelSurface;

//Couleur
SDL_Color textColor;

//Police charg� du texte
TTF_Font* police;

//Charge le background
SDL_Surface* menuBackground;

/*=PROTOTYPES===============================================================*/
bool inputOnLoad();
void inputOnRender();
void inputOnLoop();
void inputOnEvent(SDL_Event* event);
bool inputOnQuit();

#endif /*APP_STATE_INPUT_H*/
