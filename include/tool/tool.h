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

#ifndef TOOL_H
#define TOOL_H

/*=INCLUSION=================================================================*/
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <time.h>

/*=PROTOTYPES================================================================*/
//Charge correctement une surface
SDL_Surface* loadImage(const char* path);

//Applique la transparence d'une couleur
int setColorKey(SDL_Surface* surface, int Rmask, int Gmask, int Bmask);

//Applique la transparence
void setAlpha(SDL_Surface* surface, int Amask);

//Chiffre au hasard
int getRand(int min, int max);

//Chiffre d�cimal entre 0.0 & 1.0
float getRandFloat();

//Calcul l'angle entre deux points
float getRadians2point(int x1, int y1, int x2, int y2);

//Converti SDL Color 2 Int
SDL_Color Hex2SDLcolor(Uint32 toConvert);

#endif /*TOOL_H*/
