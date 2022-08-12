/*
 ============================================================================
 Name        : FlyingShark.c
 Author      : Arnaud Boyer
 Version     : Beta
 Copyright   : School project
 Description : G�re tout ce qui est rattach� � l'avion du joueur
 Note:		 : -Cr�� une surface shadow en rechargeant la m�me image que pour
 	 	 	   la surface aircraft est la solution la plus simple pour dupli-
 	 	 	   quer une surface
 ============================================================================
 */

#ifndef PLAYER_H
#define PLAYER_H

/*=INCLUSION=================================================================*/
#include "define.h"
#include "level.h"
/* #ifdef _WIN32
#include <windows.h>
#endif */
#include "explosion.h"

#include "state/game/state/game/component/opponent/boat.h"
#include "state/game/state/game/component/opponent/bomber.h"
#include "state/game/state/game/component/opponent/fighter.h"
#include "state/game/state/game/component/opponent/tank.h"

/*=CONSTANTES================================================================*/
#define AIRCRAFT_SPEED		1.7
#define AIRCRAFT_WIDTH		50
#define AIRCRAFT_HEIGHT		40
#define AIRCRAFT_RELOAD_SPEED 180
#define AIRCRAFT_KAMIKAZE_DAMAGE_POINT 500

#define AUTO_PILOT_DURATION 50
#define AUTO_PILOT_SPEED	1.2

#define SCALE_DEFAULT		1
#define SCALE_DEFAULT_SHADOW 0.9
#define SCALE_DOWN_MAX		0.8
#define SCALE_STEP			0.02
#define SCALE_SHADOW_STEP 	0.015
#define SCALE_STEP_INTERVAL	200
#define MARGIN 30

float mar;
double scaleFactor;
double scaleFactorShadow;
unsigned int lastScaleFactorChange;

//Les diff�rents �tat de pilotage [permet � l'ordinateur de prendre le controle de l'avion pour l'atterissage et le d�collage]
enum pilotingState {
	LANDING = 0,//Att�rissage
	TAKEOFF,	//D�collage
	PLAYER,		//Le joueur � le contr�le
	SCORING,	//Calcul le score
	DESTROY,	//Entrain d'�tre d�truit
	DESTROYED,	//Avion d�truit
	GAME_OVER	//Mort d�finitivement
};

//Les diff�rentes animations de l'avion
enum animationState {
	ANIM_STATE_NORMAL = 0,
	ANIM_STATE_NORMAL_HELIX_RIGHT,
	ANIM_STATE_NORMAL_HELIX_LEFT,
	ANIM_STATE_NORMAL_RIGHT,
	ANIM_STATE_NORMAL_LEFT,
	ANIM_STATE_SHADOW,
	ANIM_STATE_SHADOW_RIGHT,
	ANIM_STATE_SHADOW_LEFT,
	ANIM_STATE_DESTROYED
};

/*=VARIABLES=================================================================*/
//Avion du joueur
struct player {
	//Position & Dimension
	struct Coordinates position;		//Position du joueur � l'�cran et dimension [largeur, hauteur]
	//Animation
	int animState;						//Etat d'animation courant
	unsigned int lastAnimStateChange;	//Dernier timestamp ou l'animation � chang�
	//Attributs
	short int life;						//Nombre de vie
	short int numWeapon;				//Nombre d'arme de base qui peuvent �tre tir� en une seule fois
	short int numSpecialWeapon;			//Nombre d'arme sp�cial
	//Nom & Score
	unsigned int score;					//Score actuelle du joueur
	char name[PLAYERNAME_LENGTH];		//Nom du joueur
	int scorePowerUp;
} player;

//Etat de pilotage de l'avion
int currentPilotingState;

//Permet d'�ff�ctu� une action une seule fois lorsque l'�tat de pilotage change
bool OneTimeByChangeState;

//Surface de l'avion � l'�cran
SDL_Surface* aircraftSurface;

//Gestion des mouvements
bool isMoveUp;
bool isMoveDown;
bool isMoveLeft;
bool isMoveRight;

//Timer autopilote
int timerAutoPilot;

//Effets avion d�truit
Mix_Chunk* SFX_player_destroy;
Mix_Chunk* SFX_player_landing;
Mix_Chunk* SFX_player_takeoff;
Mix_Chunk* SFX_player_flight;

//Position du joueur sur la Map
int positionPlayerOnMap;

/*=PROTOTYPE=================================================================*/
//Charge le joueur
bool playerInit();

bool playerLoad();

//Mise � jour des donn�es du niveau
void playerLoop();

//Affiche le niveau
void playerRender();

//D�truit l'avion du joueur
void playerDestroy();

//Lib�re la m�moire
void playerQuit();

//Permet de chang� l'�tat de pilotage simplement
void changePilotingState(const int newState);

//Permet de replacer l'avion au dernier checkpoint
void startCheckpoint();

#endif /*PLAYER_H*/
