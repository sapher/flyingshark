#ifndef BOAT_H
#define BOAT_H

/*=INCLUSION=================================================================*/
#include "define.h"
#include "state/game/state/game/component/opponent.h"
#include "state/game/state/game/component/explosion.h"
#include "state/game/state/game/component/level.h"
#include "fireball.h"

/*=CONSTANTES================================================================*/
enum ANIM_STATE_BOAT {
	BOAT_FRONT,
	BOAT_FRONT_RIGHT,
	BOAT_RIGHT,
	BOAT_BACK_RIGHT,
	BOAT_BACK,
	BOAT_BACK_LEFT,
	BOAT_LEFT,
	BOAT_FRONT_LEFT
};

#define	BOAT_WIDTH		74
#define	BOAT_HEIGHT		74
#define BOAT_SPEED		0.3
#define BOAT_POINT		90
#define BOAT_RELOAD_SPEED	800
#define BOAT_LIFE_POINT 70

/*=VARIABLES=================================================================*/
//Liste des bombardiers
struct Opponent boatList[MAXIMUM_OPPONENT_LIST];

//Surface qui contiendra les boats charg�s
SDL_Surface* boatSurface;

/*=PROTOTYPE=================================================================*/
//Initialise les donn�es relatives aux boats
bool boatInit();

//Mise � jour des donn�es des boats
void boatLoop();

//Affiche les boats
void boatRender();

//Lib�re la m�moire
void boatQuit();

#endif /*BOAT_H*/
