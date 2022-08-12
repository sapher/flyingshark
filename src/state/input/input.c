#include "state/input/input.h"

bool inputOnLoad() {

	//Fais en sorte qu'il n'y ait pas de texte
	memset(player.name, 0, sizeof player.name);

	//Initialise le buffer
	buffer = 0;

	//Set a color [barbarian]
	textColor.r = textColor.b = textColor.g = 255;

	//Charge le background
	menuBackground = SDL_DisplayFormat(IMG_Load(SPRITE_BACKGROUND));

	//D�faut
	isDelete	= FALSE;
	isSelect	= FALSE;

	//Charge la police
	police = TTF_OpenFont(FONT_MENU, TEXT_SIZE);

	//Label
	labelSurface = TTF_RenderText_Blended(police, "NOM DU JOUEUR:", textColor);

	return TRUE;
}

void inputOnRender() {

	SDL_Rect pos;

	//Ralenti la vitesse de frappe
	SDL_Delay(75);

    //Affiche le titre
    pos.x = 0;
    pos.y = -100;
    SDL_BlitSurface(menuBackground, 0, SDL_GetVideoSurface(), &pos);

    //Centrage de l'input
    int POSITION_INPUT_X = (SCREEN_WIDTH - TEXT_SIZE * PLAYERNAME_LENGTH)/2;

    //Ajout d'un label
	pos.x = POSITION_INPUT_X - INPUT_PADDING;
	pos.y = POSITION_INPUT_Y - INPUT_PADDING*3 - TEXT_SIZE;
	SDL_BlitSurface(labelSurface, 0, SDL_GetVideoSurface(), &pos);

    /*CADRE INPUT*/
    int x1 = POSITION_INPUT_X - INPUT_PADDING;
    int y1 = POSITION_INPUT_Y - INPUT_PADDING;
    int x2 = POSITION_INPUT_X + TEXT_SIZE * PLAYERNAME_LENGTH;
    int y2 = POSITION_INPUT_Y + TEXT_SIZE + INPUT_PADDING;

    rectangleRGBA(SDL_GetVideoSurface(), x1, y1, x2, y2, 255, 255, 255, 255);

    /**TEXTE DE L'INPUT*/
	//Rempli la surface texte
	textSurface = TTF_RenderText_Blended(police, player.name, textColor);

	//D�fini la position � l'�cran
	pos.x = POSITION_INPUT_X;
	pos.y = POSITION_INPUT_Y;

	//Colle le texte � l'�cran
	SDL_BlitSurface(textSurface, NULL, SDL_GetVideoSurface(), &pos);
}

void inputOnLoop() {

	//Test si le buffer est plein
	if(buffer != 0) {

		//Force les majuscules
		buffer = toupper(buffer);

		//V�rifie que la taille n'est pas d�pass�
		if(strlen(player.name)+1 <= PLAYERNAME_LENGTH) {

			//Copie le buffer dans le string
			strcat(player.name, &buffer);
		}

		//Lib�re le buffer
		buffer = 0;
	}

	/*Supprime le dernier caract�re [?]*/
	if(isDelete == TRUE) player.name[(strlen(player.name)-1)] = '\0';

	//Continue
	if(isSelect == TRUE) changeAppState(APP_STATE_GAME);
}

//Gestion des �v�nements
void inputOnEvent(SDL_Event* event) {

	//Pool d'�v�nement
	while(SDL_PollEvent(event)) {

		switch(event->type) {

			//Touche appuy�es
			case SDL_KEYDOWN: {
				switch(event->key.keysym.sym) {

					//Supprime un caract�re
					case SDLK_BACKSPACE:
						isDelete = TRUE;
					break;

					//Emp�che d'entr�e un espace
					case SDLK_SPACE:
						//do nothing...
					break;

					//Accepte
					case SDLK_RETURN  :
						isSelect = TRUE;
					break;

					//R�cup�re tout les touches entr�e
					default:
						if(event->key.keysym.unicode < 256) buffer = event->key.keysym.unicode;

					break;
				}

				break;
			}

			//Touche relach�
			case SDL_KEYUP: {
				switch(event->key.keysym.sym) {

					//Supprime un caract�re
					case SDLK_BACKSPACE:
						isDelete = FALSE;
					break;

					//Accepte
					case SDLK_RETURN  :
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
			}//case
		}//switch
	}//while
}

bool inputOnQuit() {
	return TRUE;
}
