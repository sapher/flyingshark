#ifndef POWERUP_H
#define POWERUP_H

/*=INCLUSION=================================================================*/
#include "define.h"
#include "player.h"
#include "interface.h"

/*=CONSTANTES================================================================*/
#define MAX_POWERUP					6
#define POWERUP_HEIGHT				22
#define POWERUP_WIDTH				22
#define POWERUP_LIFETIME			25000
#define POWER_UP_MOVEMENT_INTERVAL	15
#define SCORE_POWERUP				500

enum POWERUP_TYPE {
	POWERUP_LIFE = 0,		//Donne une vie en plus
	POWERUP_SPECIAL_WEAPON,	//+1 Arme Sp�cial
	POWERUP_WEAPON,			//+1 le nombre de missile lancer en m�me temps
	POWERUP_1000			//+1000pts
};

/*=STRUCTURES================================================================*/
typedef struct elementPowerUp {
	struct Coordinates position;
	int type;
	int appearAt;
	unsigned int lastMovementChange;
	bool isExist;
	struct Coordinates velocity;
} elementPowerUp;

/*=VARIABLES=================================================================*/
//Gere l'apparition des powerups
int scorePowerUp;

//Liste des powerUps
struct elementPowerUp listPowerUp[MAX_POWERUP];

//Surface qui contiendra une sprite de powerUp
SDL_Surface* powerUpSurface;

//Son � jouer lorsque l'on r�cup�re un powerup
Mix_Chunk* SFX_get_powerup;

/*=PROTOTYPE=================================================================*/
//Initialise les donn�es relatives aux powerUps
bool powerUpInit();

//Mise � jour des donn�es des powerUps
void powerUpLoop();

//Affiche les powerUps
void powerUpRender();

//Lib�re la m�moire
void powerUpQuit();

//Ajoute une powerUp
void addPowerUp(int x, int y, int type);

//D�fini un mouvement pour le powerup
void movementElection(elementPowerUp* powerup);

#endif /*POWERUP_H*/
