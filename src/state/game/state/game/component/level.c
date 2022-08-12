#include "state/game/state/game/component/level.h"

//Charge le niveau
bool levelInit() {

	//Charge le tileSet
	tileSet = loadImage(SPRITE_SET);

	//V�rifie si le fileSet � �t� bien charg�
	if(tileSet == NULL) return FALSE;

	return TRUE;
}

//Charge un niveau
bool loadLevel(int levelNumber) {

	playerLoad();
	interfaceLoad();

	scorePowerUp = 0;

	//Lib�re la surface
	SDL_FreeSurface(levelSurface);

	//Coupe la musique
	//Mix_FadeOutMusic(500);

	//Etat de l'avion toujours � normal en debut de jeu
	player.animState = ANIM_STATE_NORMAL;

	//Toujours � zero en d�but de niveau
	scrollMap = 0;

	//Position de l'ombre
	timerAutoPilot = SDL_GetTicks() + AUTO_PILOT_DURATION;

	//Mise � jour du niveau courant
	currentLevel = levelNumber;

	//Charge le sc�nario de ce niveau
	loadScenario(currentLevel);

	//Charge le niveau en mode lecture
	char fullLevelPath[100];
	strcpy(fullLevelPath, LEVEL_PATH);
	strcat(fullLevelPath, levelList[currentLevel]);
	FILE * fileLevel = fopen(fullLevelPath, "r");

	//Check erreur de chargement
	if(fileLevel == NULL) return FALSE;

	//Remets le nombre de ligne du niveau � 0 avant calcul
	currentLevelNumLine = 0;

	//Compte le nombre de ligne du fichier
	char buffer[256];
	while(fgets(buffer, sizeof(buffer), fileLevel) != NULL) currentLevelNumLine++;

	//Reviens au d�but du fichier
	rewind(fileLevel);

	//Cr�� les surfaces avec les bonnes dimensions
	levelSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, SCREEN_WIDTH, currentLevelNumLine * TILE_SIZE, SCREEN_PIXEL_FORMAT, 0, 0, 0, 0);

	//Tampon qui contiendra une ligne du fichier
	int line_id;
	int case_id;
	int sprite_id;

	//Jusqu'a la fin du fichier
	//Ligne
	for(line_id = 0; line_id < currentLevelNumLine; line_id++) {

		//Case
		for(case_id = 0; case_id < SCREEN_WIDTH / TILE_SIZE; case_id++) {

			fscanf(fileLevel, "%d ", &sprite_id);

			BlitCase(levelSurface, line_id, case_id, sprite_id);
		}

		fscanf(fileLevel, "\n");
	}

	//Ferme le fichier de niveau
	fclose(fileLevel);

	//Charge les effets
	SFX_game_over = Mix_LoadWAV(SFX_GAME_OVER);
	SFX_mission_complete = Mix_LoadWAV(SFX_MISSION_COMPLETE);

	//Au d�but du niveau le joueur commence � la moiti� de l'�cran
	positionPlayerOnMap = SCREEN_HEIGHT/2;

	return TRUE;
}

//Mise � jour des donn�es du niveau
void levelLoop() {

	//Arriv� � la fin du niveau on stope la progession
	if(scrollMap < (currentLevelNumLine * TILE_SIZE - SCREEN_HEIGHT) && (currentPilotingState == PLAYER || currentPilotingState == LANDING)) {
		scrollMap += MAP_SCROLL_SPEED;

		//Mise � jour de la position du joueur
		positionPlayerOnMap = SCREEN_HEIGHT + (scrollMap - player.position.y);
	}

	//Arriv� � la fin on place l'avion en mode Atterissage
	if(scrollMap > (currentLevelNumLine * TILE_SIZE - SCREEN_HEIGHT - 180)) changePilotingState(LANDING);
}

//Affiche le niveau
void levelRender() {

	//D�fini la cam�ra [�vite de coller en dehors de l'�cran]
	SDL_Rect camera;
	camera.h = SCREEN_HEIGHT;
	camera.w = SCREEN_WIDTH;
	camera.x = 0;
	camera.y = -scrollMap + levelSurface->h - SCREEN_HEIGHT;

	//Collage des diff�rents calques
	/*Terrain*/
	SDL_BlitSurface(levelSurface, &camera, SDL_GetVideoSurface(), 0);
}

//Lib�re la m�moire
void levelQuit() {

	//D�charge les effets
	Mix_FreeChunk(SFX_game_over);
	Mix_FreeChunk(SFX_mission_complete);

	//D�charge le tileSet
	SDL_FreeSurface(tileSet);

	//D�charge la surface du niveau
	SDL_FreeSurface(levelSurface);
}

//Colle une case sur le niveau
void BlitCase(SDL_Surface* surfaceDestination, int line_id, int case_id, int sprite_id) {

	SDL_Rect destination = {TILE_SIZE * case_id, TILE_SIZE * line_id, 0, 0};

	SDL_Rect case_dimension = {TILE_SIZE * (sprite_id%NUM_TILE_BY_LINE), TILE_SIZE * (sprite_id/NUM_TILE_BY_LINE), TILE_SIZE, TILE_SIZE};

	//Colle la case sur la surface
	SDL_BlitSurface(tileSet, &case_dimension, surfaceDestination, &destination);
}
