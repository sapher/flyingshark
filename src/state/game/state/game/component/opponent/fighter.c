#include "state/game/state/game/component/opponent/fighter.h"

//Initialise les donn�es relatives aux fighters
bool fighterInit() {

	//Charge la surface
	fighterWhiteSurface = loadImage(SPRITE_FIGHTER_WHITE);
	fighterGoldSurface = loadImage(SPRITE_FIGHTER_GOLD);
	fighterBlueSurface = loadImage(SPRITE_FIGHTER_BLUE);
	fighterGreenSurface = loadImage(SPRITE_FIGHTER_GREEN);

	//Test
	if(fighterWhiteSurface == NULL) return FALSE;
	if(fighterGoldSurface == NULL) return FALSE;
	if(fighterBlueSurface == NULL) return FALSE;
	if(fighterGreenSurface == NULL) return FALSE;

	return TRUE;
}

//Mise � jour des donn�es des fighters
void fighterLoop() {

	//Boucle pour tout les fighters
	int i;
	for(i = 0; i < MAXIMUM_OPPONENT_LIST; i++) {

		//Si le fighter existe
		if(fighterList[i].isExist == TRUE) {

			//Todo: Cr�� une fonction pour l'animation de l'�lice
			//Change l'�tat d'animation
			if(fighterList[i].lastAnimStateChange <= SDL_GetTicks()) {

				if(fighterList[i].animState == FIGHTER_NORMAL) fighterList[i].animState = FIGHTER_HELIX_LEFT;
				else if(fighterList[i].animState == FIGHTER_HELIX_LEFT) fighterList[i].animState = FIGHTER_HELIX_RIGHT;
				else if(fighterList[i].animState == FIGHTER_HELIX_RIGHT) fighterList[i].animState = FIGHTER_NORMAL;

				fighterList[i].lastAnimStateChange = SDL_GetTicks() + HELIX_CHANGE_INTERVAL;
			}

			//La position du fighter suit l'avancement de l'�cran
			if(fighterList[i].direction == DOWN) {

				fighterList[i].position.y += FIGHTER_SPEED;

				//Suit le joueur
				//Si l'avion de l'ennemi se trouve plus haut que l'avion du joueur
				if(fighterList[i].position.y + SPACE_BETWEEN_OPPONENT < player.position.y) {

					//A gauche de l'ennemi
					if(fighterList[i].position.x + FIGHTER_WIDTH/2 + 5 < player.position.x) {
						fighterList[i].position.x += 0.5;
						fighterList[i].animState = FIGHTER_RIGHT;
					}//if
					//A droite de l'ennemi
					else {
						fighterList[i].position.x -= 0.5;
						fighterList[i].animState = FIGHTER_LEFT;
					}//else
				}//if
				else {
					if(fighterList[i].animState == FIGHTER_RIGHT || fighterList[i].animState == FIGHTER_LEFT) fighterList[i].animState = FIGHTER_NORMAL;
				}//else

				//Attaque
				if(fighterList[i].position.x < player.position.x && fighterList[i].position.x + FIGHTER_WIDTH > player.position.x) {

					if(fighterList[i].lastAttack <= SDL_GetTicks() && authorizeAttack == TRUE) {

						//Attaque
						Coordinates fakeCraft = {fighterList[i].position.x, fighterList[i].position.y + 50};
						launchFireball(fighterList[i].position, fakeCraft);

						//Mets � jour le timer
						fighterList[i].lastAttack = SDL_GetTicks() + FIGHTER_RELOAD_SPEED;
					}//if
				}//if
			}//if

			//Test si n'a pas �t� d�truit
			destroyOpponent(&fighterList[i], FIGHTER_POINT);

			//Supprime si d�passe de l'�cran
			if(outOfSceen(fighterList[i].position) == TRUE) fighterList[i].isExist = FALSE;
		}//if
	}//for
}

//Affiche les fighters
void fighterRender() {

	//Boucle pour tout les fighters
	showOpponent(fighterList);
}

//Lib�re la m�moire
void fighterQuit() {

	memset(fighterList, 0, sizeof fighterList);

	SDL_FreeSurface(fighterWhiteSurface);
	SDL_FreeSurface(fighterGoldSurface);
	SDL_FreeSurface(fighterBlueSurface);
	SDL_FreeSurface(fighterGreenSurface);
}
