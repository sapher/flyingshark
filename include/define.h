#ifndef DEFINE_H
#define DEFINE_H

/*=INCLUSIONS================================================================*/
//Les librairies standards
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

//Les librairies externes
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_framerate.h>
#include <SDL_rotozoom.h>

//Les ressources
#include "resource.h"

//Les outils
#include "tool/tool.h"

/*=CONSTANTES================================================================*/

//Tweak permettant d'utiliser un bool en C != C99
typedef enum {
	FALSE = 0,
	TRUE
} bool;

//Angle d'attaque
enum ANGLE {
	ANGLE_FRONT			= 90,
	ANGLE_FRONT_RIGHT 	= 45,
	ANGLE_RIGHT			= 0,
	ANGLE_BACK_RIGHT	= 315,
	ANGLE_BACK			= 270,
	ANGLE_BACK_LEFT		= 225,
	ANGLE_LEFT			= 180,
	ANGLE_FRONT_LEFT	= 135
};

//Etat possible du programme
enum APP_STATE {
	APP_STATE_INTRO,
	APP_STATE_MENU,
	APP_STATE_GAME,
	APP_STATE_SCORE,
	APP_STATE_INPUT,
	APP_STATE_QUIT
};

//Fen�tre
#define DEBUG				TRUE

#define SCREEN_WIDTH		640
#define SCREEN_HEIGHT		480
#define SCREEN_PIXEL_FORMAT	32

#define GAME_TITLE			"Flying Shark"

#define FRAME_RATE			200

#define PLAYERNAME_LENGTH	10
#define MAX_PLAYER_SCORE	10

#define DEFAULT_NUMBER_LIFE	3
#define DEFAULT_NUMBER_SPECIAL_WEAPON	3
#define DEFAULT_MAXIMUM_SPECIAL_WEAPON	4
#define DEFAULT_NUMBER_WEAPON	2
#define MAXIMUM_NUMBER_WEAPON	8
#define DEFAULT_MAXIMUM_NUMBER_LIFE		4

#define HELIX_CHANGE_INTERVAL	25

#define MAXIMUM_OPPONENT_LIST 10

/*=STRUCTURES================================================================*/
struct gameState {
	int stateCurrent;	//Etat courant
} state;

//Structure d'une entit� � l'�cran
typedef struct Coordinates {
	float x;	//Position pixel pr�s en abscisse
	float y;	//Position pixel pr�s en ordonn�e
	int h;		//Hauteur, peut ne pas �tre utilis�
	int w;		//Largeur, peut ne pas �tre utilis�
} Coordinates;

//BUG incompr�hensible si plac� dans opponent.h
typedef struct Opponent {
	struct Coordinates position;
	struct Coordinates velocity;
	int type;
	int direction;
	bool alive;
	int animState;
	int shadowAnimState;				//Is NULL for terrestrial opponent
	unsigned int lastAnimStateChange;
	unsigned int lastAttack;
	bool isExist;
	int lifePoint;
	SDL_Surface* opponentSurface;
} Opponent;

//Contient un opposant composant le sc�nario
typedef struct opponentScenario {
    int appearAt;
    int typeOpponent;
    int direction;
    struct Coordinates position;
    int to;
    bool isAppear;
    struct Coordinates velocity;
} opponentScenario;

/*=VARIABLES================================================================*/
//Etat d'�x�cution du programme
bool isRunning;

#endif /* DEFINE_H */
