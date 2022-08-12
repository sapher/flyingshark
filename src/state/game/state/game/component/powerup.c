#include "state/game/state/game/component/powerup.h"

//Initialise les donn�es relatives aux powerUps
bool powerUpInit() {

	//Charge les powerups
	powerUpSurface = IMG_Load(SPRITE_POWERUP);

	//Test
	if(powerUpSurface == NULL) return FALSE;

	//Charge le son
	SFX_get_powerup = Mix_LoadWAV(SFX_GET_POWERUP);

	//Test si chargement
	if(SFX_get_powerup == NULL) return FALSE;

	return TRUE;
}

//Mise � jour des donn�es des powerUps
void powerUpLoop() {

	int i;

	//Pour chaque powerUps
	for(i = 0; i < MAX_POWERUP; i++) {

		//Si existe
		if(listPowerUp[i].isExist == TRUE) {

			//D�tecte la colision
			if(isCollision(player.position, listPowerUp[i].position) == TRUE) {

				//Lance le son
				Mix_PlayChannel(-1, SFX_get_powerup, 0);

				//Applique le powerup
				switch(listPowerUp[i].type) {

				//+1 vie
				case POWERUP_LIFE:
					player.life++;
					break;

				case POWERUP_WEAPON:
					if(player.numWeapon < MAXIMUM_NUMBER_WEAPON) player.numWeapon += 2;
					break;

				case POWERUP_SPECIAL_WEAPON:
					player.numSpecialWeapon++;
					break;

				//+1000pts score
				case POWERUP_1000:
					player.score += 1000;
					break;
				}

				//Supprime la powerUp
				listPowerUp[i].isExist = FALSE;
			}

			//Supprime la powerUp si sa dur�e de vie � �t� d�pass�
			if(listPowerUp[i].appearAt <= SDL_GetTicks()) listPowerUp[i].isExist = FALSE;

			//Mets � jour la position
			//Change l'�tat d'animation
			if(listPowerUp[i].lastMovementChange <= SDL_GetTicks()) {

				//Si touche le bord de l'�cran
				//Horizontale
				//Gauche
				if(listPowerUp[i].position.y <= 0) {
					listPowerUp[i].velocity.y = fabsf(listPowerUp[i].velocity.y);
				}
				//Droite
				else if(listPowerUp[i].position.y >= SCREEN_HEIGHT - POWERUP_HEIGHT) {
					listPowerUp[i].velocity.y = listPowerUp[i].velocity.y - listPowerUp[i].velocity.y * 2;
				}

				//Vertical
				//Haut
				if(listPowerUp[i].position.x <= 0) {
					listPowerUp[i].velocity.x = fabsf(listPowerUp[i].velocity.x);
				}
				//Bas
				else if(listPowerUp[i].position.x >= SCREEN_WIDTH - POWERUP_WIDTH) {
					listPowerUp[i].velocity.x = listPowerUp[i].velocity.x - listPowerUp[i].velocity.x * 2;
				}

				//Mets � jour la position
				listPowerUp[i].position.x += listPowerUp[i].velocity.x;
				listPowerUp[i].position.y += listPowerUp[i].velocity.y;

				//Update le timer
				listPowerUp[i].lastMovementChange = SDL_GetTicks() + POWER_UP_MOVEMENT_INTERVAL;
			}
		}//if
	}//for
}

//Affiche les powerUps
void powerUpRender() {

	int i;

	//Pour chaque powerUps
	for(i = 0; i < MAX_POWERUP; i++) {

		//Si le powerup Existe
		if(listPowerUp[i].isExist == TRUE) {

			//Cr�� l'emplacement a l'�cran
			SDL_Rect powerUpPosition = {listPowerUp[i].position.x, listPowerUp[i].position.y, 0, 0};

			//Cr�� l'emplacement a l'�cran
			SDL_Rect spritePosition = {listPowerUp[i].type * POWERUP_WIDTH, 0, POWERUP_WIDTH, POWERUP_HEIGHT};

			//Colle le powerup � l'�cran
			SDL_BlitSurface(powerUpSurface, &spritePosition, SDL_GetVideoSurface(), &powerUpPosition);
		}//if
	}//for
}

//Lib�re la m�moire
void powerUpQuit() {

	memset(listPowerUp, 0, sizeof listPowerUp);

	Mix_FreeChunk(SFX_get_powerup);
}

//Ajoute une powerUp
void addPowerUp(int x, int y, int type) {

	int i;

	//Traverse le tableau
	for(i = 0; i < MAX_POWERUP; i++) {

		//Retrouve la prochaine case vide
		if(listPowerUp[i].isExist != TRUE) {

			//Cr�� la nouvelle powerUp
			listPowerUp[i].position.x	= x;
			listPowerUp[i].position.y	= y;
			listPowerUp[i].position.h	= POWERUP_HEIGHT;
			listPowerUp[i].position.w	= POWERUP_WIDTH;
			listPowerUp[i].type			= type;
			listPowerUp[i].lastMovementChange = SDL_GetTicks() + POWER_UP_MOVEMENT_INTERVAL;
			listPowerUp[i].appearAt		= POWERUP_LIFETIME + SDL_GetTicks();
			listPowerUp[i].isExist		= TRUE;

			//D�fini un mouvement
			movementElection(&listPowerUp[i]);

			//Quitte la boucle
			break;
		}//if
	}//for
}

//D�fini un mouvement pour le powerup
void movementElection(elementPowerUp* powerup) {

	//Calcul la vitesse
	int x = getRand(1, 2);
	int y = getRand(1, 2);

	//D�fini le signe
	powerup->velocity.x = (getRand(0, 2) == 0) ? -x : x;
	powerup->velocity.y = (getRand(0, 2) == 0) ? -y : y;
}
