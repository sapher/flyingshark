#ifndef APP_STATE_MENU_H
#define APP_STATE_MENU_H

/*=INCLUSION=================================================================*/
#include "define.h"
#include "state.h"

/*=CONSTANTES================================================================*/
#define MENU_SIZE			3	//Nombre d'�l�ment du menu
#define MENU_FONT_SIZE		24
#define V_MENU_SPACE		20
#define MENU_POSITION_Y		220
#define MENU_DEFAULT_INDEX	0
#define KEYBOARD_MOVE_SPEED 105	//ms

/*=VARIABLES=================================================================*/
//SFX
Mix_Chunk* SFX_menu_move;
Mix_Chunk* SFX_menu_select;

//Contiendra la police
TTF_Font* police;

/*Mouvement*/
bool isMoveUp;
bool isMoveDown;
bool isSelect;

/*Index du menu*/
int currentIndex;

//Un Element du menu
typedef struct menuElement {
	SDL_Surface* normal;
	SDL_Surface* hover;
	int linked_state;
} menuElement;

//Liste des �l�ments qui constitue le menu
struct menuElement menu[MENU_SIZE];

/*=PROTOTYPES=================================================================*/
//Charge le state
void menuOnLoad();

//Gestion des �v�nements
void menuOnEvent(SDL_Event* event);

//Effectue le rendu
void menuOnRender();

//Boucle de mise � jour des donn�es
void menuOnLoop();

//Lib�re la m�moire
void menuOnQuit();

//Proc�dure permettant de cr�� un lien du menu
void createMenuRow(const char* text, SDL_Color colorHover, SDL_Color colorNormal, const int linkedState, menuElement* menuRow);

#endif /*APP_STATE_MENU_H*/
