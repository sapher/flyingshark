#ifndef GAME_STATE_PAUSE_H
#define GAME_STATE_PAUSE_H

/*=INCLUSION=================================================================*/
#include "define.h"
#include "state/game/game_state.h"
#include "state/menu/menu.h"

/*=CONSTANTES================================================================*/

/*=VARIABLES=================================================================*/
SDL_Surface* pauseTextSurface;

Mix_Chunk* SFX_game_pause;

/*=PROTOTYPES================================================================*/
//Charge le state
bool pauseOnLoad();

//Lorsque l'on active l'�tat
void pauseOnActivate();

//Gestion des �v�nements
void pauseOnEvent(SDL_Event* event);

//Effectue le rendu
void pauseOnRender();

//Boucle de mise � jour des donn�es
void pauseOnLoop();

//Lib�re la m�moire
void pauseOnQuit();

#endif /*GAME_STATE_PAUSE_H*/
