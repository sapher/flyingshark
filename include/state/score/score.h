/*
 ============================================================================
 Name        : FlyingShark.c
 Author      : Severin Julien
 Version     : Beta
 Copyright   : School project
 Description : Affiche le score des joueurs
 ============================================================================
 */

#ifndef APP_STATE_SCORE_H
#define APP_STATE_SCORE_H

/*=INCLUSION=================================================================*/
#include "define.h"
#include "state.h"
#include "tool/file.h"

/*=CONSTANTES================================================================*/
#define POSITION_SCORE		200
#define SCORE_TEXT_SIZE		18

/*=VARIABLES=================================================================*/
//Retour vers le menu principal
bool isReturn;

//Pointeur vers le fichier score
FILE* scoreFile;

//Liste des resultats
playerResult listResult[MAX_PLAYER_SCORE];

//Taille du tableau de r�sultat
int sizeResult;

//Charge le background
SDL_Surface* menuBackground;

//Texte de retour
SDL_Surface* textReturn;

//Police charg� du texte
TTF_Font* policeText;

//Police charg� du score
TTF_Font* policeScore;

//Text Color
SDL_Color textColor;
SDL_Color isPlayerTextColor;

/*=PROTOTYPES================================================================*/
//Charge le state
bool scoreOnLoad();

//Gestion des �v�nements
void scoreOnEvent(SDL_Event* event);

//Effectue le rendu
void scoreOnRender();

//Boucle de mise � jour des donn�es
void scoreOnLoop();

//Lib�re la m�moire
void scoreOnQuit();

#endif /*APP_STATE_SCORE_H*/
