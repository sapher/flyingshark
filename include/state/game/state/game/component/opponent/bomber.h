#ifndef BOMBER_H
#define BOMBER_H

/*=INCLUSION=================================================================*/
#include "define.h"
#include "state/game/state/game/component/opponent.h"
#include "state/game/state/game/component/explosion.h"

/*=CONSTANTES================================================================*/
enum ANIM_STATE_BOMBER_GRAY {
	BOMBER_GRAY_NORMAL,
	BOMBER_GRAY_HELIX_LEFT,
	BOMBER_GRAY_HELIX_RIGHT,
	BOMBER_GRAY_SHADOW
};

enum ANIM_STATE_BOMBER_BLACK {
	BOMBER_BLACK_NORMAL,
	BOMBER_BLACK_HELIX_LEFT,
	BOMBER_BLACK_HELIX_RIGHT,
	BOMBER_BLACK_SHADOW
};

#define	BOMBER_GRAY_WIDTH	60
#define	BOMBER_GRAY_HEIGHT	45
#define BOMBER_GRAY_SPEED	0.3
#define BOMBER_GRAY_POINT	150
#define BOMBER_GRAY_LIFE_POINT	150

#define	BOMBER_BLACK_WIDTH	93
#define	BOMBER_BLACK_HEIGHT	73
#define BOMBER_BLACK_LIFE_POINT	200

#define BOMBER_RELOAD_SPEED	3200

/*=VARIABLES=================================================================*/
//Liste des bombardiers
struct Opponent bomberList[MAXIMUM_OPPONENT_LIST];

//Surface qui contiendra les bombardiers charg�s
SDL_Surface* bomberGraySurface;
SDL_Surface* bomberBlackSurface;

/*=PROTOTYPE=================================================================*/
//Initialise les donn�es relatives aux bombers
bool bomberInit();

//Mise � jour des donn�es des bombers
void bomberLoop();

//Affiche les bombers
void bomberRender();

//Lib�re la m�moire
void bomberQuit();

#endif /*BOMBER_H*/
