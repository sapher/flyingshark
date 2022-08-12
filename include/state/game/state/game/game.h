#ifndef GAME_STATE_GAME_H
#define GAME_STATE_GAME_H

/*=INCLUSION=================================================================*/
#include "define.h"

#include "state/game/state/game/component/player.h"
#include "state/game/state/game/component/level.h"
#include "state/game/state/game/component/missile.h"
#include "state/game/state/game/component/explosion.h"
#include "state/game/state/game/component/interface.h"
#include "state/game/state/game/component/powerup.h"
#include "state/game/state/game/component/opponent.h"
#include "state/game/state/game/component/opponent/bomber.h"

/*=CONSTANTES================================================================*/
//Canaux r�serv�s
enum RESERVED_CHANNEL {
	CH_PLAYER_DESTROY = 0,
	CH_FLIGHT,
	CH_LANDING,
	CH_TAKEOFF,
	CH_MISSION_COMPLETE,
	CH_GAME_OVER
};

/*=VARIABLES=================================================================*/

/*=PROTOTYPES================================================================*/
//Charge le state
bool gameOnLoad();

//Lorsque l'�tat de jeu "jeu" devient actif
void gameOnActivate();

//Gestion des �v�nements
void gameOnEvent(SDL_Event* event);

//Effectue le rendu
void gameOnRender();

//Boucle de mise � jour des donn�es
void gameOnLoop();

//Lib�re la m�moire
void gameOnQuit();

#endif /*GAME_STATE_GAME_H*/
