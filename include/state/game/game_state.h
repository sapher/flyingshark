#ifndef APP_STATE_GAMESTATE_H
#define APP_STATE_GAMESTATE_H

/*=INCLUSION=================================================================*/
#include "define.h"

#include "state/game/state/game/component/player.h"
#include "state/game/state/game/component/level.h"
#include "state/game/state/game/component/missile.h"
#include "state/game/state/game/component/explosion.h"
#include "state/game/state/game/component/interface.h"
#include "state/game/state/game/component/powerup.h"
#include "state/game/state/game/component/opponent.h"
#include "state/game/state/game/component/opponent/bomber.h"

#include "state/game/state/game/game.h"
#include "state/game/state/gameover/gameover.h"
#include "state/game/state/pause/pause.h"
#include "state/game/state/endgame/endgame.h"

/*=CONSTANTES================================================================*/
enum GAME_STATE {
	GAME_STATE_GAME,
	GAME_STATE_PAUSE,
	GAME_STATE_GAMEOVER,
	GAME_STATE_ENDGAME

};

/*=VARIABLES=================================================================*/
//Liste des niveaux
char **levelList;
//Nombre de niveau
int	numLevel;

//Liste des sc�narios
char **scenarioList;

//Nombre de sc�nario
int numScenario;

//Etat de jeu
int currentGameState;


/*=PROTOTYPES================================================================*/
//Charge le state
bool gameStateOnLoad();

//Gestion des �v�nements
void gameStateOnEvent(SDL_Event* event);

//Effectue le rendu
void gameStateOnRender();

//Boucle de mise � jour des donn�es
void gameStateOnLoop();

//Lib�re la m�moire
void gameStateOnQuit();

//Test si sorti de l'�cran
bool outOfSceen(Coordinates position);

//D�t�ction de colision
bool isCollision(Coordinates A, Coordinates B);

//Mets � jour un timer
bool updateTimer(unsigned int* timer, const int interval);

//Change l'�tat du jeu
void changeGameState(const int newState);

#endif /*APP_STATE_GAMESTATE_H*/
