#ifndef LEVEL_H
#define LEVEL_H

/*=INCLUSION=================================================================*/
#include "define.h"
#include "player.h"
#include "explosion.h"
#include "powerup.h"
#include "opponent.h"

/*=CONSTANTES================================================================*/
#define TILE_SIZE			16
#define NUM_TILE_BY_LINE	22
#define MAP_SCROLL_SPEED	0.15
#define NUM_CHECKPOINT		4

/*=VARIABLES=================================================================*/

//Surface contenant le sprite
SDL_Surface* tileSet;

//Surface ou sera coller les cases pour former le niveaux
SDL_Surface* levelSurface;

//Niveau en cours
int currentLevel;

//Nombre de niveau du niveau en cours
int currentLevelNumLine;

//D�filement du d�cors
float scrollMap;

//Effets
Mix_Chunk* SFX_game_over;
Mix_Chunk* SFX_mission_complete;

/*=PROTOTYPE=================================================================*/
//Charge le niveau
bool levelInit();

//Charge un niveau
bool loadLevel(int levelNumber);

//Mise � jour des donn�es du niveau
void levelLoop();

//Affiche le niveau
void levelRender();

//Lib�re la m�moire
void levelQuit();

//Colle une case sur le niveau
void BlitCase(SDL_Surface* surfaceDestination, int line_id, int case_id, int sprite_id);

#endif /*LEVEL_H*/
