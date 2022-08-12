#ifndef MISSILE_H
#define MISSILE_H

/*=INCLUSION=================================================================*/
#include "define.h"
#include "player.h"
#include "level.h"
#include "state/game/state/game/component/opponent/bomber.h"

/*=CONSTANTES================================================================*/
#define MISSILE_SPEED	2
#define MISSILE_SPACING	5
//#define MISSILE_ROTATE_ANGLE 90
#define MISSILE_SHIFT	0.02
#define MISSILE_HEIGHT	18
#define MISSILE_WIDTH	8
#define MISSILE_DAMAGE_POINT	50
#define NUMBER_MISSILE	50

/*=STRUCTURE================================================================*/
struct missileElement {
	struct Coordinates position;
	bool isAlive;
	struct Coordinates velocity;
};

struct missileStruct {
	struct missileElement missile[MAXIMUM_NUMBER_WEAPON];
	bool isExist;
};

/*=VARIABLES=================================================================*/
//Surface de la boule de feu
SDL_Surface* missileSurface;

//Date dernier missile [permet d'�viter le spamming]
unsigned int lastFireball;

//Liste des missiles
struct missileStruct missileList[NUMBER_MISSILE];

//Son lancement missile
Mix_Chunk* SFX_missile_launch;

//Son Missile atteint la cible
Mix_Chunk* SFX_missile_explosion;

/*=PROTOTYPE=================================================================*/
//Charge les donn�es des missiles
bool missileInit();

//Lance une attaque
void missileLaunch(Coordinates origin);

//Mise � jour des emplacements des missiles � l'image
void missileLoop();

//Affiche les missiles
void missileRender();

//Lib�re la m�moire
bool missileQuit();

#endif /*MISSILE_H*/
