#include "state/game/state/game/component/opponent/tank.h"

//Initialise les donn�es relatives aux tanks
bool tankInit() {

	//Charge la surface
	tankSurface = loadImage(SPRITE_TANK);

	//Test
	if(tankSurface == NULL) return FALSE;

	return TRUE;
}

//Mise � jour des donn�es des tanks
void tankLoop() {

	//Boucle pour tout les tanks
	int i;
	for(i = 0; i < MAXIMUM_OPPONENT_LIST; i++) {

		//Si le tank existe
		if(tankList[i].isExist == TRUE && currentPilotingState == PLAYER) {

			//La position du tank suit l'avancement de l'�cran
			tankList[i].position.y += MAP_SCROLL_SPEED;

			//ATTAQUE!
			/*if(tankList[i].lastAttack <= SDL_GetTicks() && authorizeAttack == TRUE) {

				//Attaque
				launchFireball(tankList[i].position, player.position);

				//Mets � jour le timer
				tankList[i].lastAttack = SDL_GetTicks() + TANK_RELOAD_SPEED + getRand(20, 70); //Free Will
			}//if*/
			if(updateTimer(&tankList[i].lastAttack, TANK_RELOAD_SPEED) == TRUE && authorizeAttack == TRUE) {

				//Attaque
				launchFireball(tankList[i].position, player.position);
			}
		}//if

		//Test si n'a pas �t� d�truit
		destroyOpponent(&tankList[i], TANK_POINT);

		//Supprime si d�passe de l'�cran
		if(outOfSceen(tankList[i].position) == TRUE) tankList[i].isExist = FALSE;
	}//for
}

//Affiche les tanks
void tankRender() {

	//Boucle pour tout les tanks
	showOpponent(tankList);
}

//Lib�re la m�moire
void tankQuit() {

	memset(tankList, 0, sizeof tankList);

	SDL_FreeSurface(tankSurface);
}
