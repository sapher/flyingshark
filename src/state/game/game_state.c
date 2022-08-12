#include "state/game/game_state.h"

//Charge le state
bool gameStateOnLoad() {

	//Charge tout les �tats
	gameOnLoad();
	endgameOnLoad();
	pauseOnLoad();
	gameOverOnLoad();

	//place l'�tat du jeu en d�marrage de niveau
	changeGameState(GAME_STATE_GAME);

	return TRUE;
}

//Gestion des �v�nements
void gameStateOnEvent(SDL_Event* event) {

	switch (currentGameState) {

		case GAME_STATE_GAME:
			gameOnEvent(event);
			break;

		case GAME_STATE_GAMEOVER:
			gameOverOnEvent(event);
			break;

		case GAME_STATE_PAUSE:
			pauseOnEvent(event);
			break;

		case GAME_STATE_ENDGAME:
			endgameOnEvent(event);
			break;

		default: break;
	}
}

//Effectue le rendu
void gameStateOnRender() {

	switch (currentGameState) {

		case GAME_STATE_GAME:
			gameOnRender();
			break;

		case GAME_STATE_GAMEOVER:
			gameOverOnRender();
			break;

		case GAME_STATE_PAUSE:
			pauseOnRender();
			break;

		case GAME_STATE_ENDGAME:
			endgameOnRender();
			break;
		default: break;
	}
}

//Boucle de mise � jour des donn�es
void gameStateOnLoop() {

	switch (currentGameState) {

		case GAME_STATE_GAME:
			gameOnLoop();
			break;

		case GAME_STATE_GAMEOVER:
			gameOverOnLoop();
			break;

		case GAME_STATE_PAUSE:
			pauseOnLoop();
			break;

		case GAME_STATE_ENDGAME:
			endgameOnLoop();
			break;
		default: break;
	}
}

//Lib�re la m�moire
void gameStateOnQuit() {

	//D�charge tout les �tats
	gameOnQuit();
	endgameOnQuit();
	pauseOnQuit();
	gameOverOnQuit();
}

//Test si sorti de l'�cran
bool outOfSceen(Coordinates position) {

	if(position.x + position.w * 2 <= 0 || position.x - position.w*2 > SCREEN_WIDTH || position.y + position.h*2 <= 0 || position.y - position.h*2 > SCREEN_HEIGHT) return TRUE;

	return FALSE;
}

//D�t�ction de colision
bool isCollision(Coordinates A, Coordinates B) {

	//C�te rectangle A
	int leftA	=	A.x;
	int rightA	=	A.x + A.w;
	int topA	=	A.y;
	int bottomA	=	A.y + A.h;

	//C�te rectangle B
	int leftB	=	B.x;
	int rightB	=	B.x + B.w;
	int topB	=	B.y;
	int bottomB	=	B.y + B.h;

	//Test colision
	if(bottomA <= topB) return FALSE;
	if(topA >= bottomB) return FALSE;
	if(rightA <= leftB) return FALSE;
	if(leftA >= rightB) return FALSE;

	return TRUE;
}

//Mets � jour un timer, retourne si le timer � �t� mise � jour ou non
bool updateTimer(unsigned int* timer, const int interval) {

	if(*timer <= SDL_GetTicks()) {

		*timer = SDL_GetTicks() + interval;

		return TRUE;
	}

	return FALSE;
}

//Change l'�tat du jeu
void changeGameState(const int newState) {

	switch (newState) {

		case GAME_STATE_PAUSE:
			pauseOnActivate();
			break;

		case GAME_STATE_GAME:
			gameOnActivate();
			break;

		case GAME_STATE_ENDGAME:
			endgameOnActivate();
			break;
		default:break;
	}

	currentGameState = newState;
}
