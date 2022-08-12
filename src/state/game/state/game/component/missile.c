#include "state/game/state/game/component/missile.h"

//Charge le niveau
bool missileInit() {

    //Charge la surface de la boule de feu
	missileSurface = loadImage(SPRITE_MISSILE);

	//Test
	if(missileSurface == NULL) return FALSE;

	//Applique la transparence
	setColorKey(missileSurface, 8, 54, 129);

	//Charge les effets sonnores
	SFX_missile_launch		= Mix_LoadWAV(SFX_MISSILE_LAUNCH);
	SFX_missile_explosion	= Mix_LoadWAV(SFX_MISSILE_EXPLOSION);

	lastFireball = 0;

	return TRUE;
}

//Mise � jour des donn�es du niveau
void missileLoop() {

	//Compteur
	int i;
	int j;

	//Boucle qui met � jour la position des boule de feu
	for(i = 0; i < NUMBER_MISSILE; i++) {

		//Si la boule de feu existe
		if(missileList[i].isExist == TRUE) {

			//Cr�� le ou les missile
			for(j = 0; j < player.numWeapon; j++) {

				//Si le missile existe encore
				if(missileList[i].missile[j].isAlive == TRUE) {

					//Mets � jour la position � l'�cran
					missileList[i].missile[j].position.x += missileList[i].missile[j].velocity.x;
					missileList[i].missile[j].position.y -= MISSILE_SPEED;

					//Supprime la boule de feu qui elle sort de l'�cran
					if(outOfSceen(missileList[i].missile[j].position)) missileList[i].isExist = FALSE;

					//Test collision Missile/Ennemi
					int numReachTarget = 0;
					if(isCollisionOpponent(missileList[i].missile[j].position, MISSILE_DAMAGE_POINT) == TRUE) {

						//Supprime le missile
						missileList[i].missile[j].isAlive = FALSE;

						numReachTarget++;
					}

					//Test collision Missile/Fireball
					//Boucle pour tout les fireballs
					int i;
					for(i = 0; i < MAXIMUM_FIREBALL; i++) {

						//Existe
						if(fireballList[i].isExist == TRUE) {

							//Si il y a eu collision entre une boule de feu et un missile
							if(isCollision(missileList[i].missile[j].position, fireballList[i].position) == TRUE) {

								//Supprime le missile
								missileList[i].missile[j].isAlive = FALSE;

								//Supprime la fireball
								fireballList[i].isExist = FALSE;

								numReachTarget++;
							}
						}//si existe
					}//boucle les fireballs

					//Ne lance le son qu'une fois et seulement si on � atteint la cible
					if(numReachTarget > 0) {
						//Lance le son quand le missile atteint sa cible
						Mix_PlayChannel(-1, SFX_missile_explosion, 0);
					}

				}//if alive
			}//for j
		}//if exist
	}//for i
}

//Affiche le niveau
void missileRender() {

	//Compteur
	int i;
	int j;

	//Contiendra la position de la boule de feu
	SDL_Rect position;

	//Boucle qui vas afficher chaque boule de feu � l'image
	for(i = 0; i < NUMBER_MISSILE; i++) {

		//Si la boule de feu existe
		//Trouve la prochaine case vide du tableau
		if(missileList[i].isExist == TRUE) {

			//Cr�� le ou les missile
			for(j = 0; j < player.numWeapon; j++) {

				//Si le missile est encore vivant (?)
				if(missileList[i].missile[j].isAlive == TRUE) {

					//Set la position de la boule de feu
					position.x = missileList[i].missile[j].position.x;
					position.y = missileList[i].missile[j].position.y;

					//Colle la boule de feu � l'�cran
					SDL_BlitSurface(missileSurface, 0, SDL_GetVideoSurface(), &position);
				}//if alive
			}//for j
		}//if exist
	}//for i
}

//Lib�re la m�moire
bool missileQuit() {

	memset(missileList, 0, sizeof missileList);

	//Lib�re la m�moire des effets sonores
	Mix_FreeChunk(SFX_missile_launch);
	Mix_FreeChunk(SFX_missile_explosion);

	return TRUE;
}

//Lance une attaque
void missileLaunch(Coordinates origin) {

	//Compteur
	int i;
	int j;

	//Test si il est possible de lancer une missile
	if(lastFireball <= SDL_GetTicks() && currentPilotingState == PLAYER) {

		//Boucle qui vas ajouter une nouvelle boule de feu
		for(i = 0; i < NUMBER_MISSILE; i++) {

			//Trouve la prochaine case vide du tableau
			if(missileList[i].isExist == FALSE) {

				//Cr�� le ou les missile
				for(j = 0; j < player.numWeapon; j++) {

					missileList[i].missile[j].isAlive	= TRUE;
					missileList[i].missile[j].position.y= origin.y - 2;

					/*CENTRE PARFAITEMENT LES MISSILES AU CENTRE DE L'AVION*/
					//Centre de l'avion [compense la largeur du missile]
					int centerAircraft = (AIRCRAFT_WIDTH/2 - MISSILE_WIDTH/2);
					//D�fini le c�t� gauche ou droit
					int side 	= (j%2 == 1) ? MISSILE_SPACING : -MISSILE_SPACING;
					//Compteur commen�ant � 1 et non � zero en tout temps
					int m		= j + 1;
					//Evite le * 0
					int d		= (m < 2) ? 1 : (m%2 == 1) ? m : m - 1;
					missileList[i].missile[j].position.x= origin.x + centerAircraft + side * d;
					missileList[i].missile[j].velocity.x = d * ((j%2 == 1) ? MISSILE_SHIFT : -MISSILE_SHIFT);

					missileList[i].missile[j].position.h = MISSILE_HEIGHT;
					missileList[i].missile[j].position.w = MISSILE_WIDTH;
				}//for j

				//Lance le son
				Mix_PlayChannel(-1, SFX_missile_launch, 0);

				//Mets � jour le timer
				lastFireball = SDL_GetTicks()  + AIRCRAFT_RELOAD_SPEED;

				//Maintenant existe
				missileList[i].isExist = TRUE;

				//Arr�te la boucle
				break;
			}//if exist
		}//for i
	}//if
}
