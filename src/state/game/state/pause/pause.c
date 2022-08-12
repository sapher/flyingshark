#include "state/game/state/pause/pause.h"

//Charge le state
bool pauseOnLoad() {

	//Charge du menu pause
	SFX_game_pause = Mix_LoadWAV(SFX_GAME_PAUSE);

	if(SFX_game_pause == NULL) return FALSE;

    //Charge la police
	TTF_Font* police = TTF_OpenFont(FONT_GAME, GAME_FONT_SIZE);

	//Set a color [alizarine]
	SDL_Color textColor = Hex2SDLcolor(COLOR_RED);

	//Cr�� le texte bonus
	pauseTextSurface = TTF_RenderText_Blended(police, "PAUSE", textColor);

	//Ferme la police
	TTF_CloseFont(police);

	return TRUE;
}

//Lorsque l'on active l'�tat
void pauseOnActivate() {

	//Lance un son pour la pause
	Mix_PlayChannel(-1, SFX_game_pause, 0);

	//Mets en pause la musique
	//Mix_HaltMusic();

	//D�sactive le son du moteur
	Mix_Pause(CH_FLIGHT);
}

//Gestion des �v�nements
void pauseOnEvent(SDL_Event* event) {

	//Pool d'�v�nement
	while(SDL_PollEvent(event)) {

		switch(event->type) {

			//Touche appuy�es
			case SDL_KEYDOWN: {
				switch(event->key.keysym.sym) {

				//Entr�e
					case SDLK_ESCAPE :
						changeGameState(GAME_STATE_GAME);
					break;

					//Evite les warnings
					default:break;
				}

				break;
			}

			//Ferme la fenetre
			case SDL_QUIT: {

				isRunning = FALSE;

				break;
			}//case
		}//switch
	}//while
}

//Effectue le rendu
void pauseOnRender() {

	//Colle la surface gameover � l'image
	SDL_Rect position = {(SCREEN_WIDTH - pauseTextSurface->w)/2, (SCREEN_HEIGHT - pauseTextSurface->h)/2, 0, 0};
	SDL_BlitSurface(pauseTextSurface, NULL, SDL_GetVideoSurface(), &position);
}

//Boucle de mise � jour des donn�es
void pauseOnLoop() {

}

//Lib�re la m�moire
void pauseOnQuit() {

	SDL_FreeSurface(pauseTextSurface);

	Mix_FreeChunk(SFX_game_pause);
}
