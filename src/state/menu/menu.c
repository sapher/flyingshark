#include "state/menu/menu.h"

//Charge le state
void menuOnLoad() {

	//Initialise les variables
	/*Son*/
	SFX_menu_move	= Mix_LoadWAV(SFX_MENU_MOVE);
	SFX_menu_select	= Mix_LoadWAV(SFX_MENU_SELECT);

	/*Mouvement*/
	isMoveUp	= FALSE;
	isMoveDown	= FALSE;
	isSelect	= FALSE;

	/*Index du menu*/
	currentIndex = MENU_DEFAULT_INDEX;

	//Charge le background
	menuBackground = SDL_DisplayFormat(IMG_Load(SPRITE_BACKGROUND));

	//Cr�� la police
	police = TTF_OpenFont(FONT_MENU, MENU_FONT_SIZE);

	//Cr�� le menu
	SDL_Color colorNormal	= Hex2SDLcolor(COLOR_WHITE);
	SDL_Color colorHover	= Hex2SDLcolor(COLOR_YELLOW);

	createMenuRow("NOUVEAU JEU"	,colorHover, colorNormal, APP_STATE_INPUT,  &menu[0]);
	//createMenuRow("JEU EN LIGNE",colorHover, colorNormal, APP_STATE_GAME,  &menu[1]);
	createMenuRow("SCORE", colorHover, colorNormal, APP_STATE_SCORE, &menu[1]);
	//createMenuRow("OPTION",	colorHover, colorNormal, APP_STATE_GAME,  &menu[3]);
	//createMenuRow("CREDITS",colorHover, colorNormal, APP_STATE_GAME,  &menu[2]);
	createMenuRow("QUITTER", colorHover, colorNormal, APP_STATE_QUIT,  &menu[2]);
}

//Gestion des �v�nements
void menuOnEvent(SDL_Event* event) {

	//Pool d'�v�nement
	while(SDL_PollEvent(event)) {

		/***********/
		switch(event->type) {

			//Touche appuy�es
			case SDL_KEYDOWN: {
				switch(event->key.keysym.sym) {
					//Haut
					case SDLK_UP:
						isMoveUp = TRUE;
					break;

					//Bas
					case SDLK_DOWN:
						isMoveDown = TRUE;
					break;

					//Entr�e
					case SDLK_RETURN :
						isSelect = TRUE;
					break;

					//Evite les warnings
					default:break;
				}

				break;
			}

			//Touche relach�
			case SDL_KEYUP: {
				switch(event->key.keysym.sym) {
					//Haut
					case SDLK_UP:
						isMoveUp = FALSE;
					break;

					//Bas
					case SDLK_DOWN:
						isMoveDown = FALSE;
					break;

					//Entr�e
					case SDLK_RETURN :
						isSelect = FALSE;
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
			}
		}
		/***********/
	}
}

//Effectue le rendu
void menuOnRender() {

    //Affiche le menu
	int i;
	SDL_Rect position;

    //Affiche le titre
	position.x = 0;
	position.y = -100;
    SDL_BlitSurface(menuBackground, 0, SDL_GetVideoSurface(), &position);

    //Affiche les �l�ments
	position.y = MENU_POSITION_Y;

	for(i = 0; i < MENU_SIZE; i++) {

		//Position X recalcul�e pour le centrage
		position.x = (SCREEN_WIDTH - menu[i].hover->w)/2;

		if(i > 0) position.y += V_MENU_SPACE;

		if(currentIndex == i) SDL_BlitSurface(menu[i].hover, 0, SDL_GetVideoSurface(), &position);
		else SDL_BlitSurface(menu[i].normal, 0, SDL_GetVideoSurface(), &position);
	}

	//Ralenti la vitesse du menu
	SDL_Delay(KEYBOARD_MOVE_SPEED);
}

//Boucle de mise � jour des donn�es
void menuOnLoop() {

	//Ne fais aucune action si  il n'y a pas eu un �v�nement
	if(!isMoveUp && !isMoveDown && !isSelect) return;

	//Sp�cial APP_STATE_QUIT
	if(isSelect && menu[currentIndex].linked_state == APP_STATE_QUIT) {

		isRunning = FALSE;

		return;
	}

	//Si un �l�ment � �t� s�l�ctionner
	if(isSelect == TRUE) {

		//Change de state
		changeAppState(menu[currentIndex].linked_state);

		Mix_PlayChannel(-1, SFX_menu_select, 0);

		return;
	}

	//Si monte
	if(isMoveUp && currentIndex > 0) {

		Mix_PlayChannel(-1, SFX_menu_move, 0);
		currentIndex--;
		return;
	}

	//Si monte
	if(isMoveDown && currentIndex < MENU_SIZE-1) {

		Mix_PlayChannel(-1, SFX_menu_move, 0);
		currentIndex++;
		return;
	}
}

//Lib�re la m�moire
void menuOnQuit() {

	//Lib�re les surfaces
	//SDL_FreeSurface(backgroundSurface);

	//Lib�re les surfaces du menu
	int i;
	for(i = 0; i < MENU_SIZE; i++) {
		SDL_FreeSurface(menu[i].hover);
		SDL_FreeSurface(menu[i].normal);
	}

	//Lib�re les SFX charg�
	Mix_FreeChunk(SFX_menu_move);
	Mix_FreeChunk(SFX_menu_select);
}

/******TOOLS********/
//Proc�dure permettant de cr�� un lien du menu
void createMenuRow(const char* text, SDL_Color colorHover, SDL_Color colorNormal, const int linkedState, menuElement* menuRow) {

	menuRow->normal	= TTF_RenderText_Blended(police, text, colorNormal);
	menuRow->hover	= TTF_RenderText_Blended(police, text, colorHover);
	menuRow->linked_state = linkedState;
}
/*******************/
