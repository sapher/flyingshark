/*
 ============================================================================
 Name        : FlyingShark.c
 Author      : Arnaud Boyer
 Version     : Beta
 Copyright   : School project
 Description : G�re les �tats de l'application
 Note:		 : -Les �v�nements sont g�r� de fa�on � permettre la persistance
 	 	 	   -L'activation d'un state doit se faire avant le d�sactivation
 	 	 	   d'un autre sinon crash (pas tr�s logique).
 	 	 	   -Le collage de surface cr�� dynamiquement dans la fonction
 	 	 	   OnRender cause une augmentation inutile de l'utilisation de la
 	 	 	   m�moire.
 ============================================================================
 */

/*=INCLUSION=================================================================*/
#include "define.h"

//Etat du jeu
#include "state/intro/intro.h"
#include "state/menu/menu.h"
#include "state/game/game_state.h"
#include "state/score/score.h"
#include "state/input/input.h"

/*=CONSTANTES=================================================================*/

/*=VARIABLES=================================================================*/
//Musique
Mix_Music* Music_menu;

unsigned int startTicks;

/*=PROTOTYPES================================================================*/
bool Init();
void changeAppState(const char newState);
void LoadState();
void Event(SDL_Event* event);
void Loop();
void Render();
int	 Execute();
int	 Quit();
