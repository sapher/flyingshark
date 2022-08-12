#include "state/game/state/game/component/player.h"

//Charge le niveau
bool playerInit() {

	//Initialisation des boutons
	isMoveDown	=	FALSE;
	isMoveLeft	=	FALSE;
	isMoveRight	=	FALSE;
	isMoveUp	=	FALSE;

	//Initialise les compteurs de score � 0
	player.score = 0;
	player.scorePowerUp = 0;

	//Initialise le nombre de vie
	player.life = DEFAULT_NUMBER_LIFE;

	//Initialise le nombre d'arme sp�cial
	player.numSpecialWeapon = DEFAULT_NUMBER_SPECIAL_WEAPON;

	//Initialise le nombre d'arme normal
	player.numWeapon = DEFAULT_NUMBER_WEAPON;

	//Charge la surface de l'avion
	aircraftSurface = loadImage(SPRITE_AIRCRAFT);

	//Test
	if(aircraftSurface == NULL) return FALSE;

	//Charge l'�ffets destruction du joueur
	SFX_player_destroy	= Mix_LoadWAV(SFX_PLAYER_DESTROY);
	SFX_player_landing	= Mix_LoadWAV(SFX_PLAYER_LANDING);
	SFX_player_takeoff	= Mix_LoadWAV(SFX_PLAYER_TAKEOFF);
	SFX_player_flight	= Mix_LoadWAV(SFX_PLAYER_FLIGHT);

	//D�fini la taille de l'avion
	player.position.h = AIRCRAFT_HEIGHT;
	player.position.w = AIRCRAFT_WIDTH;

	return TRUE;
}

bool playerLoad() {

	//Place le scaleFactor � zero
	scaleFactor = scaleFactorShadow = 0.0f;

	//Initialise le nombre d'arme sp�cial
	player.numSpecialWeapon = DEFAULT_NUMBER_SPECIAL_WEAPON;

	//Initialise le nombre d'arme normal
	player.numWeapon = DEFAULT_NUMBER_WEAPON;

	//Set les �tats
	player.animState = ANIM_STATE_NORMAL;
	player.lastAnimStateChange = SDL_GetTicks() + HELIX_CHANGE_INTERVAL;

	OneTimeByChangeState = FALSE;

	mar = 0;

	//Initialise � 0
	lastScaleFactorChange = 0;

	//Initialise la position du joueur sur la Map
	positionPlayerOnMap = 0;

	//Place le mode de pilotage de l'avion en �tat de d�collage
	changePilotingState(TAKEOFF);

	return TRUE;
}

//Mise � jour des donn�es du niveau
void playerLoop() {

	//Calcul le centre de l�cran
	float screenCenterX = (SCREEN_WIDTH - AIRCRAFT_WIDTH) / 2;
	float screenCenterY = (SCREEN_HEIGHT- AIRCRAFT_HEIGHT) / 2;

	//Controle par l'ordinateur
	switch(currentPilotingState) {

	//D�collage
	case LANDING:

		//Si le timer n'existe pas, on le lance
		if(lastScaleFactorChange == 0) lastScaleFactorChange = SDL_GetTicks() + SCALE_STEP_INTERVAL;

		//Mets � jour le scaleFactor si il est temps et si on � pas d�pass� le maximum
		if(lastScaleFactorChange <= SDL_GetTicks()) {

			//Mets � jour le scaleFactor
			if(scaleFactor >= SCALE_DOWN_MAX) scaleFactor -= SCALE_SHADOW_STEP;

			//Mets � jour le scaleFactorShadow
			if(scaleFactorShadow >= SCALE_DOWN_MAX) scaleFactorShadow -= SCALE_STEP;

			if(mar > 0) mar--;

			//Recr�e le timer
			lastScaleFactorChange = SDL_GetTicks() + SCALE_STEP_INTERVAL;
		}

		//Lorsque l'animation est terminer
		if(scaleFactor <= SCALE_DOWN_MAX && mar == 0) {
			changePilotingState(SCORING);
		}

		//Tente de ramen� tranquillement l'avion du joueur au millieu de l'�cran
		if((player.position.x > screenCenterX - AUTO_PILOT_SPEED && player.position.x < screenCenterX + AUTO_PILOT_SPEED) && (player.position.y > screenCenterY - AUTO_PILOT_SPEED && player.position.y < screenCenterY + AUTO_PILOT_SPEED)) {

			player.animState = ANIM_STATE_NORMAL;
		}
		else {
			//Ram�ne X
			if(player.position.x > screenCenterX) {
				player.animState = ANIM_STATE_NORMAL_LEFT;
				player.position.x -= AUTO_PILOT_SPEED;
			}
			else if(player.position.x < screenCenterX) {
				player.animState = ANIM_STATE_NORMAL_RIGHT;
				player.position.x += AUTO_PILOT_SPEED;
			}

			//Tente de ramen� tranquillement l'avion du joueur au millieu de l'�cran
			//Ram�ne X
			if(player.position.y > screenCenterY) {
				player.position.y -= AUTO_PILOT_SPEED;
			}
			else if(player.position.y < screenCenterY) {
				player.position.y += AUTO_PILOT_SPEED;
			}
		}

		//return;
		break;

	//D�collage
	case TAKEOFF:

		//Si le scaleFactor n'existe pas, place le scaleFactor au minimum
		if(scaleFactor == 0) scaleFactor = SCALE_DOWN_MAX;

		//Si le scaleFactorShadow n'existe pas, place le scaleFactorShadow au minimum
		if(scaleFactorShadow == 0) scaleFactorShadow = SCALE_DOWN_MAX;

		//Si le timer n'existe pas, on le lance
		if(lastScaleFactorChange == 0) lastScaleFactorChange = SDL_GetTicks() + SCALE_STEP_INTERVAL;

		//Mets � jour le scaleFactor si il est temps
		if(lastScaleFactorChange <= SDL_GetTicks()) {

			//Mets � jour le scaleFactor
			if(scaleFactor <= SCALE_DEFAULT) scaleFactor += SCALE_STEP;

			//Mets � jour le scaleFactor
			if(scaleFactorShadow <= SCALE_DEFAULT_SHADOW) scaleFactorShadow += SCALE_SHADOW_STEP;

			if(mar <= MARGIN) mar++;

			//Recr�e le timer
			lastScaleFactorChange = SDL_GetTicks() + SCALE_STEP_INTERVAL;
		}

		//Place l'avion en bas de l'�cran
		if(OneTimeByChangeState == FALSE) {

			player.position.x = screenCenterX;
			player.position.y = SCREEN_HEIGHT- AIRCRAFT_HEIGHT - 50;

			OneTimeByChangeState = TRUE;
		}

		//D�place l'ombre & l'avion
		if(timerAutoPilot <= SDL_GetTicks()) {

			timerAutoPilot = SDL_GetTicks() + AUTO_PILOT_DURATION;

			//Fait avancer l'avion
			player.position.y -= AUTO_PILOT_SPEED;
		}

		//Lorsque l'animation est terminer, le joueur peut prendre la main
		if(player.position.y >= screenCenterY - AIRCRAFT_SPEED && player.position.y <= screenCenterY + AIRCRAFT_SPEED) changePilotingState(PLAYER);

		//return;
		break;

	case PLAYER:
		lastScaleFactorChange = 0;
		break;

	case SCORING:
		player.animState = ANIM_STATE_NORMAL;
		break;
	}

	//Stop la fonction
	if(isMoveUp == FALSE && isMoveDown == FALSE && isMoveRight == FALSE && isMoveLeft == FALSE) {

		//Replace l'animation � sont etat norml
		if(player.animState == ANIM_STATE_NORMAL_LEFT || player.animState == ANIM_STATE_NORMAL_RIGHT) {
			player.animState = ANIM_STATE_NORMAL;
		}

		//Change l'�tat d'animation
		if(player.lastAnimStateChange <= SDL_GetTicks()) {

			if(player.animState == ANIM_STATE_NORMAL) player.animState = ANIM_STATE_NORMAL_HELIX_LEFT;
			else if(player.animState == ANIM_STATE_NORMAL_HELIX_LEFT) player.animState = ANIM_STATE_NORMAL_HELIX_RIGHT;
			else if(player.animState == ANIM_STATE_NORMAL_HELIX_RIGHT) player.animState = ANIM_STATE_NORMAL;

			player.lastAnimStateChange = SDL_GetTicks() + HELIX_CHANGE_INTERVAL;
		}

		return;
	}

	//Mouvement du joueur
	if(currentPilotingState == PLAYER) {
		//Monte
		if(isMoveUp == TRUE) {
			player.position.y -= AIRCRAFT_SPEED;
			if(player.position.y < 0) player.position.y = 0;
		}

		//Descend
		if(isMoveDown == TRUE) {
			player.position.y += AIRCRAFT_SPEED;
			if(player.position.y > SCREEN_HEIGHT - AIRCRAFT_HEIGHT) player.position.y = SCREEN_HEIGHT - AIRCRAFT_HEIGHT;
		}

		//Gauche
		if(isMoveLeft == TRUE) {

			player.animState = ANIM_STATE_NORMAL_LEFT;

			player.position.x -= AIRCRAFT_SPEED;
			if(player.position.x < 0) player.position.x = 0;
		}

		//Droite
		if(isMoveRight == TRUE) {

			player.animState = ANIM_STATE_NORMAL_RIGHT;

			player.position.x += AIRCRAFT_SPEED;
			if(player.position.x > SCREEN_WIDTH - AIRCRAFT_WIDTH) player.position.x = SCREEN_WIDTH - AIRCRAFT_WIDTH;
		}
	}//Permet de piloter l'avion [mode PLAYER]

	//Test collision avec les opposants
	if(isCollisionOpponent(player.position, AIRCRAFT_KAMIKAZE_DAMAGE_POINT) == TRUE) playerDestroy();
}

//Affiche le joueur � l'�cran
void playerRender() {

	//On affiche l'avion que si sont etat n'est pas "DESTROY" ou "DESTROYED"
	if(currentPilotingState != DESTROY && currentPilotingState != DESTROYED && currentPilotingState != GAME_OVER) {

		//Surface tampon utilis� pour le collage de surface scaler
		SDL_Surface* scaledShadowSurface;

		//Cr�� l'ombre scal�
		scaledShadowSurface = zoomSurface(aircraftSurface, scaleFactorShadow, scaleFactorShadow, SMOOTHING_ON);

		/**SHADOW**/
		//Calcul de la taille scal� de la surface
		float scaleShadowX = AIRCRAFT_WIDTH * scaleFactorShadow;
		float scaleShadowY = AIRCRAFT_HEIGHT * scaleFactorShadow;

		//Cr�� l'emplacement ou sera coller l'ombre � l�cran
		SDL_Rect positionShadowOnScreen ={ player.position.x + mar, player.position.y + mar};

		//Cr�� l'emplacement repr�sentant l'ombre
		SDL_Rect positionShadowOnSprite = {0, 0, scaleShadowX, scaleShadowY};

		if(player.animState == ANIM_STATE_NORMAL_LEFT)	positionShadowOnSprite.x = scaleShadowX * ANIM_STATE_SHADOW_LEFT;
		else if(player.animState == ANIM_STATE_NORMAL_RIGHT)	positionShadowOnSprite.x = scaleShadowX * ANIM_STATE_SHADOW_RIGHT;
		else positionShadowOnSprite.x = scaleShadowX * ANIM_STATE_SHADOW;

		//Colle l'ombre
		SDL_BlitSurface(scaledShadowSurface, &positionShadowOnSprite, SDL_GetVideoSurface(), &positionShadowOnScreen);

		//Libr�re la surface pour eviter la mauvaise utilisation de la m�moire
		SDL_FreeSurface(scaledShadowSurface);

		/**AVION**/
		//Surface tampon utilis� pour le collage de surface scaler
		SDL_Surface* scaledAircraftSurface;

		//Cr�� l'avion scal�
		scaledAircraftSurface = zoomSurface(aircraftSurface, scaleFactor, scaleFactor, SMOOTHING_ON);

		//Calcul de la taille scal� de la surface
		float scaleX = AIRCRAFT_WIDTH * scaleFactor;
		float scaleY = AIRCRAFT_HEIGHT * scaleFactor;

		//Cr�� l'emplacement ou sera coller l'aircraft � l�cran
		SDL_Rect positionAircraftOnScreen = {player.position.x, player.position.y, 0, 0};

		//Cr�� l'emplacement repr�sentant l'avion
		SDL_Rect positionAircraftOnSprite = {scaleX * player.animState, 0, scaleX, scaleY};

		//Colle l'avion
		SDL_BlitSurface(scaledAircraftSurface, &positionAircraftOnSprite, SDL_GetVideoSurface(), &positionAircraftOnScreen);

		//Libr�re la surface pour eviter la mauvaise utilisation de la m�moire
		SDL_FreeSurface(scaledAircraftSurface);
	}//if
}

//Lib�re la m�moire
void playerQuit() {

	memset(&player, 0, sizeof player);

	Mix_FreeChunk(SFX_player_destroy);
	Mix_FreeChunk(SFX_player_landing);
	Mix_FreeChunk(SFX_player_takeoff);
	Mix_FreeChunk(SFX_player_flight);
}

//D�truit l'avion du joueur
void playerDestroy() {

	//L'avion ne peut exploser quand �tat de pilotage par le joueur
	if(currentPilotingState == PLAYER) {

		//Retire une vie au joueur
		player.life--;

		//Lance le son de destruction
		Mix_PlayChannel(CH_PLAYER_DESTROY, SFX_player_destroy, 0);

		//Change l'�tat en destruction
		changePilotingState(DESTROY);

		//Ajoute une explosion � l'emplacement de l'avion
		addExplosion(player.position.x + AIRCRAFT_WIDTH/2, player.position.y + AIRCRAFT_HEIGHT/2, TRUE);

		//Si vraiment mort
		if(player.life <= 0) {
			changePilotingState(GAME_OVER);
		}//if
	}//if
}

//Permet de chang� l'�tat de pilotage simplement
void changePilotingState(const int newState) {

	//Pas la peine de continuer
	if(newState == currentPilotingState) return;

	OneTimeByChangeState = FALSE;

	//Lance une seul fois
	switch (newState) {
		case GAME_OVER:

			//Coupe le son du moteur
			Mix_HaltChannel(CH_FLIGHT);

			//FadeOut la musique
			Mix_FadeOutMusic(500);

			//Joue l'effet Game Over
			Mix_PlayChannel(CH_GAME_OVER, SFX_game_over, -1);

			break;
		case PLAYER:

			//Lance le son du moteur
			Mix_PlayChannel(CH_FLIGHT, SFX_player_flight, -1);

			break;
		case SCORING:

			//BUG
			Mix_HaltChannel(CH_LANDING);

			break;
		case LANDING:

			//Coupe le son du moteur
			Mix_HaltChannel(CH_FLIGHT);

			//Coupe la musique
			Mix_HaltMusic();

			//Lance le son de niveau terminer
			Mix_PlayChannel(CH_MISSION_COMPLETE, SFX_mission_complete, 0);

			//Lance le son d'atterissage
			Mix_PlayChannel(CH_LANDING, SFX_player_landing, 0);

			break;
		case TAKEOFF:

			//Lance le son de d�collage
			Mix_PlayChannel(CH_TAKEOFF, SFX_player_takeoff, 0);

			break;
		default: break;
	}

	//Change le state
	currentPilotingState = newState;
}


//Permet de replacer l'avion au dernier checkpoint
void startCheckpoint() {

	//Replace l'avion au millieu de l'�cran
	player.position.x = SCREEN_WIDTH/2-AIRCRAFT_WIDTH/2;
	player.position.y = SCREEN_HEIGHT/2-AIRCRAFT_HEIGHT/2;

	//Place en mode jouable
	changePilotingState(PLAYER);
}
