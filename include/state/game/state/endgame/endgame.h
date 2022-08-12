#ifndef GAME_STATE_ENDGAME_H
#define GAME_STATE_ENDGAME_H

/*=INCLUSION=================================================================*/
#include "define.h"
#include "tool/file.h"
#include "state/game/game_state.h"

/*=CONSTANTES================================================================*/

/*=VARIABLES=================================================================*/
SDL_Surface* endgameTextSurface;

/*=PROTOTYPES================================================================*/
//Charge le state
bool endgameOnLoad();

//Lorsque l'on active l'�tat
void endgameOnActivate();

//Gestion des �v�nements
void endgameOnEvent(SDL_Event* event);

//Effectue le rendu
void endgameOnRender();

//Boucle de mise � jour des donn�es
void endgameOnLoop();

//Lib�re la m�moire
void endgameOnQuit();

#endif /*GAME_STATE_ENDGAME_H*/
