#ifndef FIREBALL_H
#define FIREBALL_H

/*=INCLUSION=================================================================*/
#include "define.h"
#include "state/game/state/game/component/player.h"

/*=CONSTANTES================================================================*/
#define MAXIMUM_FIREBALL	40
#define FIREBALL_WIDTH	11
#define FIREBALL_HEIGHT	11
#define FIREBALL_ANIM_INTERVAL	70
#define FIREBALL_SPEED 0.9

enum FIREBALL_ANIM_STATE {
	FIREBALL_LITTLE,
	FIREBALL_MEDIUM,
	FIREBALL_BIG
};

/*=STRUCTURES================================================================*/
struct fireballStruct {
	struct Coordinates position;
	float velX;
	float velY;
	int animState;
	unsigned int lastAnimStateChange;
	bool isExist;
};

/*=VARIABLES=================================================================*/
//Liste des missiles
struct fireballStruct fireballList[MAXIMUM_FIREBALL];

//Surface de la boule de feu
SDL_Surface* fireballSurface;

/*=PROTOTYPE=================================================================*/
//Initialise les donn�es relatives aux fireballs
bool fireballInit();

//Mise � jour des donn�es des fireballs
void fireballLoop();

//Affiche les fireballs
void fireballRender();

//Nettoie la m�moire
void fireballQuit();

//Lance une boule de feu
void launchFireball(Coordinates origin, Coordinates target);

#endif /*FIREBALL_H*/
