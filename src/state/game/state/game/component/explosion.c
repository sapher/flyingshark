#include "state/game/state/game/component/explosion.h"

//Initialise les donn�es relatives aux explosions
bool explosionInit() {

	//Charge la surface explosion
	explosionSurface = loadImage(SPRITE_DESTROY);

	//Pour chaque explosion
	int i; for(i = 0; i < MAX_EXPLOSION; i++) listExploded[i].isExist = FALSE;

	//Test
	if(explosionSurface == NULL) return FALSE;

	return TRUE;
}

//Mise � jour des donn�es des explosions
void explosionLoop() {

	//Pour chaque explosion
	int i;
	for(i = 0; i < MAX_EXPLOSION; i++) {

		if(listExploded[i].isExist == TRUE) {

			//L'explosion doit suivre l'avancement du niveau
			if(listExploded[i].isPlayer == FALSE) listExploded[i].position.y += MAP_SCROLL_SPEED;

			//Change le state quand il est temps
			if(listExploded[i].lastChangeState <= SDL_GetTicks()) {

				//Change le state
				listExploded[i].animState++;

				//Mets � jour, le dernier changement d'�tat
				listExploded[i].lastChangeState = SDL_GetTicks() + EXPLOSION_INTERVAL;
			}

			//Efface l'explosion si arriver � la derni�re animation
			if(listExploded[i].animState >= explosionSurface->w / EXPLOSION_WIDTH) {
				listExploded[i].isExist = FALSE;

				//S c'est l'avion on change le state en d�truit
				if(currentPilotingState != GAME_OVER) if(listExploded[i].isPlayer == TRUE) /*currentPilotingState = DESTROYED*/startCheckpoint();
			}//if
		}//if exist
	}//for
}

//Affiche les explosions
void explosionRender() {

	//Compteur
	int i;

	//Pour chaque explosion
	for(i = 0; i < MAX_EXPLOSION; i++) {

		//Si il y a une explosion
		if(listExploded[i].isExist == TRUE) {

			//Emplacement � l'�cran
			SDL_Rect explosionPosition = {listExploded[i].position.x, listExploded[i].position.y, 0, 0};

			//Applique l'emplacement sur le sprite
			SDL_Rect spriteExplosion = {EXPLOSION_WIDTH * listExploded[i].animState, 0, EXPLOSION_WIDTH, EXPLOSION_HEIGHT};

			//Blitte l'explosion
			SDL_BlitSurface(explosionSurface, &spriteExplosion, SDL_GetVideoSurface(), &explosionPosition);
		}//if
	}//for
}

//Lib�re la m�moire
void explosionQuit() {

	SDL_FreeSurface(explosionSurface);
}

//Ajoute une explosion
void addExplosion(int x, int y, bool isPLayer) {

	//Pour chaque explosion
	int i;

	//Traverse le tableau
	for(i = 0; i < MAX_EXPLOSION; i++) {

		//Retrouve la prochaine case vide
		if(listExploded[i].isExist == FALSE) {

			//Cr�� la nouvelle explosion
			listExploded[i].position.x	= x - EXPLOSION_WIDTH/2;
			listExploded[i].position.y	= y - EXPLOSION_HEIGHT/2;
			listExploded[i].animState	= 0;
			listExploded[i].lastChangeState = SDL_GetTicks() + EXPLOSION_INTERVAL;
			listExploded[i].isPlayer	= isPLayer;
			listExploded[i].isExist		= TRUE;

			//Quitte la boucle
			break;
		}//if
	}//for
}
