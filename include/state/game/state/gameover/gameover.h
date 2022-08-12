#ifndef GAME_STATE_GAME_OVER_H
#define GAME_STATE_GAME_OVER_H

/*=INCLUSION=================================================================*/
#include "define.h"

/*=CONSTANTES================================================================*/

/*=VARIABLES=================================================================*/

/*=PROTOTYPES================================================================*/
//Charge le state
bool gameOverOnLoad();

//Gestion des �v�nements
void gameOverOnEvent(SDL_Event* event);

//Effectue le rendu
void gameOverOnRender();

//Boucle de mise � jour des donn�es
void gameOverOnLoop();

//Lib�re la m�moire
void gameOverOnQuit();

#endif /*GAME_STATE_GAME_OVER_H*/
