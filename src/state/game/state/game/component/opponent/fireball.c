#include "state/game/state/game/component/opponent/fireball.h"

//Initialise les donn�es relatives aux fireballs
bool fireballInit() {

	//Charge la surface
	fireballSurface = loadImage(SPRITE_FIREBALL);

	//Test
	if(fireballSurface == NULL) return FALSE;

	return TRUE;
}

//Mise � jour des donn�es des fireballs
void fireballLoop() {

	//Boucle pour tout les fireballs
	int i;
	for(i = 0; i < MAXIMUM_FIREBALL; i++) {

		//Existe
		if(fireballList[i].isExist == TRUE) {

			//Mise � jour de la trajectoire
			fireballList[i].position.x += FIREBALL_SPEED * fireballList[i].velX;
			fireballList[i].position.y += FIREBALL_SPEED * fireballList[i].velY;

			//G�re l'animation
			if(fireballList[i].lastAnimStateChange <= SDL_GetTicks() && fireballList[i].animState != FIREBALL_BIG) {

				//Change l'animation
				fireballList[i].animState++;

				//Mets � jour le timer
				fireballList[i].lastAnimStateChange = SDL_GetTicks() + FIREBALL_ANIM_INTERVAL;
			}//if

			//D�tecte la colision
			if(isCollision(player.position, fireballList[i].position) == TRUE) {

				//D�truit l'avion
				playerDestroy();

				//Supprime la boule de feu
				fireballList[i].isExist = FALSE;
			}

			//TODO: Ajouter une fonction qui g�re la sortie d'�cran
			//Supprime si la boule de feu sort de l'�cran
			if(fireballList[i].position.x - FIREBALL_WIDTH >= SCREEN_WIDTH || fireballList[i].position.x + FIREBALL_WIDTH <= 0 || fireballList[i].position.y - FIREBALL_WIDTH >= SCREEN_HEIGHT || fireballList[i].position.y + FIREBALL_HEIGHT <= 0) {
				fireballList[i].isExist = FALSE;
			}

			//Si sort de l'�cran
			if(outOfSceen(fireballList[i].position) == TRUE) fireballList[i].isExist = FALSE;

		}//if
	}//for
}

//Affiche les fireballs
void fireballRender() {

	//Boucle pour tout les fireballs
	int i;
	for(i = 0; i < MAXIMUM_FIREBALL; i++) {

		//Existe
		if(fireballList[i].isExist == TRUE) {

			//Affiche le tank
			SDL_Rect fireballPositionOnScreen = {fireballList[i].position.x, fireballList[i].position.y, 0, 0};

			SDL_Rect fireballPositionOnSprite = {FIREBALL_WIDTH * fireballList[i].animState, 0, FIREBALL_WIDTH, FIREBALL_HEIGHT};

			//Colle le fireball � l'�cran
			SDL_BlitSurface(fireballSurface, &fireballPositionOnSprite, SDL_GetVideoSurface(), &fireballPositionOnScreen);
		}//if
	}//for
}

//Nettoie la m�moire
void fireballQuit() {

	memset(fireballList, 0, sizeof fireballList);

	SDL_FreeSurface(fireballSurface);
}

//Lance une boule de feu
void launchFireball(Coordinates origin, Coordinates target) {

	//Boucle pour tout les fireballs
	int i;
	for(i = 0; i < MAXIMUM_FIREBALL; i++) {

		//place vide et
		if(fireballList[i].isExist == FALSE && origin.y > 0 && origin.y + origin.h < SCREEN_HEIGHT) {

			//R�cup�re l'angle en radians
			float radians = getRadians2point(origin.x, origin.y, target.x, target.y);

			//Cr�� le nouveu fireballs
			fireballList[i].position.x	= origin.x + origin.w / 2;
			fireballList[i].position.y	= origin.y + origin.h / 2;
			fireballList[i].position.w	= FIREBALL_WIDTH;
			fireballList[i].position.h	= FIREBALL_HEIGHT;
			fireballList[i].animState	= FIREBALL_LITTLE;
			fireballList[i].lastAnimStateChange	= SDL_GetTicks() + FIREBALL_ANIM_INTERVAL;
			//TODO: A modifier
			fireballList[i].velX 		= cos(radians);
			fireballList[i].velY 		= sin(radians);
			fireballList[i].isExist 	= TRUE;

			break;
		}//if
	}//for
}
