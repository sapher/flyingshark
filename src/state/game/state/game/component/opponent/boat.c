#include "state/game/state/game/component/opponent/boat.h"

//Initialise les donn�es relatives aux boats
bool boatInit() {

	//Charge la surface
	boatSurface = loadImage(SPRITE_BOAT);

	//Test
	if(boatSurface == NULL) return FALSE;

	return TRUE;
}

//Mise � jour des donn�es des boats
void boatLoop() {

	//Boucle pour tout les boats
	int i;
	for(i = 0; i < MAXIMUM_OPPONENT_LIST; i++) {

		//Si le boat existe
		if(boatList[i].isExist == TRUE && currentPilotingState == PLAYER) {

			//La position du boat suit l'avancement de l'�cran
			boatList[i].position.y += MAP_SCROLL_SPEED;

			//ATTAQUE!
			if(updateTimer(&boatList[i].lastAttack, BOAT_RELOAD_SPEED) == TRUE && authorizeAttack == TRUE) {

				//Attaque
				launchFireball(boatList[i].position, player.position);
			}

			//Test si n'a pas �t� d�truit
			destroyOpponent(&boatList[i], BOAT_POINT);

			//Supprime si d�passe de l'�cran
			if(outOfSceen(boatList[i].position) == TRUE) boatList[i].isExist = FALSE;
		}//if
	}//for
}

//Affiche les boats
void boatRender() {

	//Boucle pour tout les boats
	showOpponent(boatList);
}

//Lib�re la m�moire
void boatQuit() {

	memset(boatList, 0, sizeof boatList);

	SDL_FreeSurface(boatSurface);
}
