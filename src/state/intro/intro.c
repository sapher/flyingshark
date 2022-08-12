#include "state/intro/intro.h"

//Charge le state
void introOnLoad() {

	//Initialise les variables
	continueAnimation = TRUE;

	//FadeIn
	fadeState = FADE_IN;

	//Image courante
	currentImage = EDITOR;

	//Charge la surface
	backgroundSurface = loadImage(SPRITE_BACKGROUND);
	editorSurface = loadImage(SPRITE_EDITOR);
	alpha = 0;

	//Charge le theme
	Music_menu = Mix_LoadMUS(MUSIC_GAME_THEME);

	//Joue la musique
	Mix_FadeInMusic(Music_menu, -1, 1500);
}

//Gestion des �v�nements
void introOnEvent(SDL_Event* event) {

	//Pool d'�v�nement
	while(SDL_PollEvent(event)) {

		switch(event->type) {

			//Touche appuy�es
			case SDL_KEYDOWN:

				//Stop l'animation
				continueAnimation = FALSE;

				break;

			//Ferme la fenetre
			case SDL_QUIT: {

				isRunning = FALSE;

				break;
			}//case
		}//switch
	}//while
}

//Effectue le rendu
void introOnRender() {

	//Perd du temps pour faire durer l'animation
	SDL_Delay(SPEED_EFFECT);

	//Colle un fond uni
    SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0x00, 0x00, 0x00));

    //Colle le background
    switch (currentImage) {
		case EDITOR:

			//Donne la nouvelle valeur de transparence
			setAlpha( editorSurface, alpha);

			//Affiche la surface
		    SDL_BlitSurface(editorSurface, 0, SDL_GetVideoSurface(), NULL);

		    break;

		case GAME:

			//Donne la nouvelle valeur de transparence
			setAlpha( backgroundSurface, alpha);

			//Affiche la surface
			SDL_BlitSurface(backgroundSurface, 0, SDL_GetVideoSurface(), NULL);

			break;

		default: break;
	}
}


//Boucle de mise � jour des donn�es
void introOnLoop() {

	//Quitte si on n'a appuy�e sur une touche
	if(continueAnimation == TRUE && currentImage < MAX_IMAGE) {

		//FADE IN
		if(alpha < 255 && fadeState == FADE_IN) {

			//Incr�mente le compteur
			alpha++;

			//Lorsque l'animation est terminer on change d'�tat
			if(alpha == 255) fadeState = FADE_OUT;
		}//if

		//FADEOUT
		else if(alpha > 0 && fadeState == FADE_OUT) {

			//D�cremente le compteur
			alpha--;

			//Lorsque l'animation est terminer on change d'�tat
			if(alpha == 0) {
				fadeState = FADE_IN;
				currentImage++;
			}
		}//else if
	}//if

	else {

		//Change de state
		changeAppState(APP_STATE_MENU);
	}//else
}

//Lib�re la m�moire
void introOnQuit() {

	//Lib�re la Surface
	SDL_FreeSurface(editorSurface);
	SDL_FreeSurface(backgroundSurface);
}
