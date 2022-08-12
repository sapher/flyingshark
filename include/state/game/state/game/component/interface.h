#ifndef INTERFACE_H
#define INTERFACE_H

/*=INCLUSIONS================================================================*/
#include "define.h"
#include "state.h"
#include "tool/file.h"
#include "player.h"
#include "explosion.h"

/*=CONSTANTES================================================================*/
#define GAME_FONT_SIZE		24
#define POSITION_HIGH_SCORE_X	400
#define POSITION_HIGH_SCORE_Y	7
#define POSITION_PLAYER_SCORE_X	180
#define POSITION_PLAYER_SCORE_Y	7

#define POSITION_NUMBER_LIFE_X	20
#define POSITION_NUMBER_LIFE_Y	440
#define NUMBER_LIFE_SPACING		5

#define POSITION_NUMBER_LIFE_X	20
#define POSITION_NUMBER_LIFE_Y	440
#define NUMBER_LIFE_SPACING		5

#define POSITION_NUMBER_SPECIAL_WEAPON_X	600
#define POSITION_NUMBER_SPECIAL_WEAPON_Y	440
#define NUMBER_SPECIAL_WEAPON_SPACING		5

#define POSITION_BONUS_X	200
#define POSITION_BONUS_Y	200
#define BOMB_BONUS_INTERVAL	400
#define BOMB_BONUS_SPACING	35
#define BOMB_BONUS_POINT	3000
#define BONUS_VERTICAL_SPACING		30
#define	BONUS_ADD_POINT_STEP		250
#define	BONUS_ADD_POINT_INTERVAL	60
#define ALPHA_CHANGE_INTERVAL	22

#define DURATION_SHOW_LEVEL_NAME	3500

/*=VARIABLES=================================================================*/

TTF_Font* police;

//Nom du niveau
SDL_Surface* textLevelNameSurface;
unsigned int durations;

/**SCORE**/
//Texte label "Score"
SDL_Surface* textPlayerScoreSurface;

//Texte label "HighScore"
SDL_Surface* textHighScoreSurface;

//HighScore
SDL_Surface* numberHighScoreSurface;

//PlayerScore
SDL_Surface* numberPlayerScoreSurface;

/**SCORING**/
SDL_Surface* textBonusSurface;
SDL_Surface* bonusPointSurface;
unsigned int timerBonus;
unsigned int lastAddPoint;
int numberBombToShow;
int numberBonusPoint;

//Couleur du label du score
SDL_Color textColor;

//Couleur du Score
SDL_Color scoreColor;

//Texte GameOver
SDL_Surface* gameOverSurface;

//Le plus haut score contenu dans le fichier score
unsigned int highScore;

//Pointeur vers le fichier score
FILE* scoreFile;

//Transparence de l'�cran Game Over
int alphaTempBackgound;
unsigned int lastAlphaChange;

//Liste des resultats
playerResult listResult[MAX_PLAYER_SCORE];

/*=PROTOTYPE=================================================================*/
//Initialise les donn�es relatives � interface
bool interfaceInit();

//Charge l'interface
void interfaceLoad();

//Mise � jour des donn�es de l'interfaces
void interfaceLoop();

//Affiche l'interface
void interfaceRender();

//Lib�re la m�moire
void interfaceQuit();

#endif /*INTERFACE_H*/
