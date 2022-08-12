#ifndef FIGHTER_H
#define FIGHTER_H

/*=INCLUSION=================================================================*/
#include "define.h"
#include "state/game/state/game/component/opponent.h"
#include "state/game/state/game/component/explosion.h"
#include "state/game/state/game/component/level.h"
#include "fireball.h"

/*=CONSTANTES================================================================*/
enum ANIM_STATE_FIGHTER {
	FIGHTER_HELIX_RIGHT,
	FIGHTER_HELIX_LEFT,
	FIGHTER_NORMAL,
	FIGHTER_LEFT,
	FIGHTER_RIGHT,
	FIGHTER_SHADOW_NORMAL,
	FIGHTER_SHADOW_LEFT,
	FIGHTER_SHADOW_RIGHT
};

#define SPACE_BETWEEN_OPPONENT 200
#define	FIGHTER_WIDTH		32
#define	FIGHTER_HEIGHT		34
#define FIGHTER_SPEED		0.4
#define FIGHTER_POINT		50
#define FIGHTER_INCLUSION_ANGLE	135
#define FIGHTER_RELOAD_SPEED	1400
#define FIGHTER_LIFE_POINT	90

/*=VARIABLES=================================================================*/
//Liste des bombardiers
struct Opponent fighterList[MAXIMUM_OPPONENT_LIST];

//Surface qui contiendra les fighters charg�s
SDL_Surface* fighterWhiteSurface;
SDL_Surface* fighterGoldSurface;
SDL_Surface* fighterBlueSurface;
SDL_Surface* fighterGreenSurface;

/*=PROTOTYPE=================================================================*/
//Initialise les donn�es relatives aux fighters
bool fighterInit();

//Mise � jour des donn�es des fighters
void fighterLoop();

//Affiche les fighters
void fighterRender();

//Lib�re la m�moire
void fighterQuit();

#endif /*FIGHTER_H*/
