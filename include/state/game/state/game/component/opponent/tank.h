#ifndef TANK_H
#define TANK_H

/*=INCLUSION=================================================================*/
#include "define.h"
#include "state/game/state/game/component/opponent.h"
#include "state/game/state/game/component/explosion.h"
#include "state/game/state/game/component/level.h"
#include "fireball.h"

/*=CONSTANTES================================================================*/
enum ANIM_STATE_TANK {
	TANK_FRONT,
	TANK_FRONT_RIGHT,
	TANK_RIGHT,
	TANK_BACK_RIGHT,
	TANK_BACK,
	TANK_BACK_LEFT,
	TANK_LEFT,
	TANK_FRONT_LEFT
};

#define	TANK_WIDTH		39
#define	TANK_HEIGHT		39
#define TANK_SPEED		0.3
#define TANK_POINT		60
#define TANK_RELOAD_SPEED	800
#define TANK_LIFE_POINT 80

/*=VARIABLES=================================================================*/
//Liste des bombardiers
struct Opponent tankList[MAXIMUM_OPPONENT_LIST];

//Surface qui contiendra les tanks charg�s
SDL_Surface* tankSurface;

/*=PROTOTYPE=================================================================*/
//Initialise les donn�es relatives aux tanks
bool tankInit();

//Mise � jour des donn�es des tanks
void tankLoop();

//Affiche les tanks
void tankRender();

//Lib�re la m�moire
void tankQuit();

#endif /*TANK_H*/
