#ifndef OPPONENT_H
#define OPPONENT_H

/*=INCLUSION=================================================================*/
#include "define.h"
#include "level.h"
#include "state/game/state/game/component/opponent/bomber.h"
#include "state/game/state/game/component/opponent/tank.h"
#include "state/game/state/game/component/opponent/boat.h"
#include "state/game/state/game/component/opponent/fighter.h"

/*=CONSTANTES================================================================*/
#define RELOAD_SPEED_TANK	300
#define RELOAD_SPEED_BOAT	300
#define RELOAD_SPEED_PLANE	270
#define MAXIMUM_OPPONENT_SCENARIO_LIST 200

enum DIRECTION {
	UP = 0,
	DOWN,
	RIGHT,
	LEFT
};

enum OPPONENTS {
	BOMBER_GRAY = 0,
	BOMBER_BLACK,
	TANK,
	BOAT,
	FIGHTER_WHITE,
	FIGHTER_GOLD,
	FIGHTER_BLUE,
	FIGHTER_GREEN
};

/*=VARIABLES=================================================================*/
//Authorise l'attaque
bool authorizeAttack;

//Nombre d'opposant du sc�nario
int numberOpponent;

//Liste des opposants du sc�nario
struct opponentScenario listOpponent[MAXIMUM_OPPONENT_SCENARIO_LIST];

/*=PROTOTYPE=================================================================*/
//Initialise les donn�es relatives aux opponents
bool opponentInit();

//Charge un sc�narion
void loadScenario(int scenarioNumber);

//Mise � jour des donn�es des opponents
void opponentLoop();

//Affiche les opponents
void opponentRender();

//Nettoie la m�moire
void opponentQuit();

//Ajoute un opposant
void addOpponent(opponentScenario opponentBehavior, Opponent *opponentList, SDL_Surface* opponenturface, const int shadowAnimState, int lifePoint, int width, int height);

//Detruit un opposant
bool destroyOpponent(Opponent* opponentList, int point);

//Test collision avec opposant
bool isCollisionOpponent(Coordinates object, int damagePoint);

//Affiche un opposant
void showOpponent(Opponent* opponent);

//Tue tout les opposants
void killAll();

#endif /*OPPONENT_H*/
