#include "state/game/state/game/component/opponent/bomber.h"

//Initialise les donn�es relatives aux opponents
bool bomberInit() {

	//Charge la surface
	bomberGraySurface	= loadImage(SPRITE_BOMBER_GRAY);
	bomberBlackSurface	= loadImage(SPRITE_BOMBER_BLACK);

	//Test
	if(bomberGraySurface == NULL && bomberBlackSurface == NULL) return FALSE;

	return TRUE;
}

//Mise � jour des donn�es des opponents
void bomberLoop() {

	//Boucle pour tout les bombardiers
	int i;
	for(i = 0; i < MAXIMUM_OPPONENT_LIST; i++) {

		//Si le bomber existe
		if(bomberList[i].isExist == TRUE) {

			//Change l'�tat d'animation
			if(bomberList[i].lastAnimStateChange <= SDL_GetTicks()) {

				if(bomberList[i].animState == BOMBER_GRAY) bomberList[i].animState = BOMBER_GRAY_HELIX_LEFT;
				else if(bomberList[i].animState == BOMBER_GRAY_HELIX_LEFT) bomberList[i].animState = BOMBER_GRAY_HELIX_RIGHT;
				else if(bomberList[i].animState == BOMBER_GRAY_HELIX_RIGHT) bomberList[i].animState = BOMBER_GRAY;

				bomberList[i].lastAnimStateChange = SDL_GetTicks() + HELIX_CHANGE_INTERVAL;
			}

			//ATTAQUE!
			if(updateTimer(&bomberList[i].lastAttack, BOMBER_RELOAD_SPEED) == TRUE && authorizeAttack == TRUE) {

				//TWEAK
				//Haut
				if(bomberList[i].direction == UP) {
					Coordinates falseAircraft;
					//BACK
					falseAircraft.x = bomberList[i].position.x;
					falseAircraft.y = bomberList[i].position.y + 50;
					launchFireball(bomberList[i].position, falseAircraft);

					//BACK LEFT
					falseAircraft.x = bomberList[i].position.x - 50;
					falseAircraft.y = bomberList[i].position.y + 50;
					launchFireball(bomberList[i].position, falseAircraft);

					//BACK RIGHT
					falseAircraft.x = bomberList[i].position.x + 50;
					falseAircraft.y = bomberList[i].position.y + 50;
					launchFireball(bomberList[i].position, falseAircraft);

					//LEFT
					falseAircraft.x = bomberList[i].position.x - 50;
					falseAircraft.y = bomberList[i].position.y;
					launchFireball(bomberList[i].position, falseAircraft);

					//BACK RIGHT
					falseAircraft.x = bomberList[i].position.x + 50;
					falseAircraft.y = bomberList[i].position.y;
					launchFireball(bomberList[i].position, falseAircraft);
				}
				//Bas
				else if(bomberList[i].direction == DOWN) {
					Coordinates falseAircraft;
					//BACK
					falseAircraft.x = bomberList[i].position.x;
					falseAircraft.y = bomberList[i].position.y - 50;
					launchFireball(bomberList[i].position, falseAircraft);

					//RIGHT
					falseAircraft.x = bomberList[i].position.x + 50;
					falseAircraft.y = bomberList[i].position.y;
					launchFireball(bomberList[i].position, falseAircraft);

					//BACK RIGHT
					falseAircraft.x = bomberList[i].position.x + 50;
					falseAircraft.y = bomberList[i].position.y - 50;
					launchFireball(bomberList[i].position, falseAircraft);

					//LEFT
					falseAircraft.x = bomberList[i].position.x - 50;
					falseAircraft.y = bomberList[i].position.y;
					launchFireball(bomberList[i].position, falseAircraft);

					//BACK LEFT
					falseAircraft.x = bomberList[i].position.x - 50;
					falseAircraft.y = bomberList[i].position.y - 50;
					launchFireball(bomberList[i].position, falseAircraft);
				}
			}

			//Supprime le bombardier si il d�passe l'�cran
			if(outOfSceen(bomberList[i].position) == TRUE) bomberList[i].isExist = FALSE;
			else {
				//Mise � jour de l'axe vertical
				if(bomberList[i].direction == UP) {
					bomberList[i].position.y -= BOMBER_GRAY_SPEED;
					bomberList[i].position.x += bomberList[i].velocity.x;
				}
				else if(bomberList[i].direction == DOWN) {
					bomberList[i].position.y += BOMBER_GRAY_SPEED;
					bomberList[i].position.x += bomberList[i].velocity.x;
				}
			}//else

			//Test si n'a pas �t� d�truit
			destroyOpponent(&bomberList[i], BOMBER_GRAY_POINT);

			//Supprime si d�passe de l'�cran
			if(outOfSceen(bomberList[i].position) == TRUE) bomberList[i].isExist = FALSE;
		}
	}
}

//Affiche les opponents
void bomberRender() {

	//Boucle pour tout les bombardiers
	showOpponent(bomberList);
}

//Lib�re la m�moire
void bomberQuit() {

	memset(bomberList, 0, sizeof bomberList);

	SDL_FreeSurface(bomberGraySurface);
	SDL_FreeSurface(bomberBlackSurface);
}
