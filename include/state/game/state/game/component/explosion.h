#ifndef EXPLOSION_H
#define EXPLOSION_H

/*=INCLUSION=================================================================*/
#include "define.h"
#include "level.h"

/*=CONSTANTES================================================================*/
#define EXPLOSION_HEIGHT	125
#define EXPLOSION_WIDTH		125
#define MAX_EXPLOSION		20
#define EXPLOSION_INTERVAL	50

/*=STRUCTURES================================================================*/
struct elementExplosion {
	struct Coordinates position;
	int animState;
	unsigned int lastChangeState;
	bool isPlayer;	//rarely used (maybe)
	bool isExist;
};

//Liste des �l�ments d�truit
struct elementExplosion listExploded[MAX_EXPLOSION];

/*=VARIABLES=================================================================*/
//Surface explosion
SDL_Surface* explosionSurface;

/*=PROTOTYPE=================================================================*/
//Initialise les donn�es relatives aux explosions
bool explosionInit();

//Mise � jour des donn�es des explosions
void explosionLoop();

//Affiche les explosions
void explosionRender();

//Nettoie la m�moire
void opponentQuit();

//Lib�re la m�moire
void explosionQuit();

//Ajoute une explosion
void addExplosion(int x, int y, bool isPLayer);

#endif /*EXPLOSION_H*/
