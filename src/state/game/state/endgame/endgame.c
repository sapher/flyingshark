#include "state/game/state/endgame/endgame.h"

//Charge le state
bool endgameOnLoad() {

	//Charge la police
	TTF_Font* police = TTF_OpenFont(FONT_GAME, GAME_FONT_SIZE);

	//Set a color [alizarine]
	SDL_Color textColor = Hex2SDLcolor(COLOR_YELLOW);

	//Cr�� le texte bonus
	endgameTextSurface = TTF_RenderText_Blended(police, "YOU FINNISH THE GAME", textColor);

	//Ferme la police
	TTF_CloseFont(police);

	return TRUE;
}

//Lorsque l'on active l'�tat
void endgameOnActivate() {

	//Enregistre le score
	saveScore(player.name, player.score);
}

//Gestion des �v�nements
void endgameOnEvent(SDL_Event* event) {

	//Pool d'�v�nement
	while(SDL_PollEvent(event)) {

		switch(event->type) {

			//Ferme la fenetre
			case SDL_QUIT: {

				isRunning = FALSE;

				break;
			}//case
		}//switch
	}//while
}

//Effectue le rendu
void endgameOnRender() {

	//Colle la surface gameover � l'image
	SDL_Rect position = {(SCREEN_WIDTH - endgameTextSurface->w)/2, (SCREEN_HEIGHT - endgameTextSurface->h)/2, 0, 0};
	SDL_BlitSurface(endgameTextSurface, NULL, SDL_GetVideoSurface(), &position);
}

//Boucle de mise � jour des donn�es
void endgameOnLoop() {

	SDL_Delay(4000);

	changeAppState(APP_STATE_MENU);
}

//Lib�re la m�moire
void endgameOnQuit() {

	SDL_FreeSurface(endgameTextSurface);
}
