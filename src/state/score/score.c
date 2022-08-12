#include "state/score/score.h"

//Charge le state
bool scoreOnLoad() {

	//Initialisation
	isReturn 	= FALSE;
	sizeResult	= 0;
	memset(&listResult, 0, sizeof listResult);

	//Charge la police
	policeText	= TTF_OpenFont(FONT_MENU, SCORE_TEXT_SIZE);
	policeScore	= TTF_OpenFont(FONT_SCORE, SCORE_TEXT_SIZE);

	//Set a color
	textColor = Hex2SDLcolor(COLOR_WHITE);
	isPlayerTextColor = Hex2SDLcolor(COLOR_YELLOW);

	//Charge le background
	menuBackground = SDL_DisplayFormat(IMG_Load(SPRITE_BACKGROUND));

	//Cr�� le texte
	textReturn = TTF_RenderText_Blended(policeText, "Appuyez sur une touche pour retourner au menu", textColor);

	/*************/
	//Charge le fichier score
	sizeResult = loadScore(listResult);
	/*************/

	return TRUE;
}

//Gestion des �v�nements
void scoreOnEvent(SDL_Event* event) {

	//Pool d'�v�nement
	while(SDL_PollEvent(event)) {

		switch(event->type) {

			//Touche appuy�es
			case SDL_KEYDOWN: {

				isReturn = TRUE;

				break;
			}

			//Touche relach�
			case SDL_KEYUP: {
				break;
			}

			//Ferme la fenetre
			case SDL_QUIT: {

				isRunning = FALSE;

				break;
			}
		}//switch
	}//while
}

//Effectue le rendu
void scoreOnRender() {

    SDL_Rect pos;

	//Rempli le fond en noir
    SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0x00, 0x00, 0x00));

    //Affiche le titre
    pos.x = 0;
    pos.y = -100;
    SDL_BlitSurface(menuBackground, 0, SDL_GetVideoSurface(), &pos);

    //Affiche le texte de retour
    pos.x = (SCREEN_WIDTH-textReturn->w)/2;
    pos.y = SCREEN_HEIGHT - SCORE_TEXT_SIZE - 40;
    SDL_BlitSurface(textReturn, 0, SDL_GetVideoSurface(), &pos);

    //Affiche les noms et scores
	int i;
	for(i = 0; i < sizeResult; i++) {

		//Test si le score n'est pas � zero [contrecarre l'initialisation � 0]
		if(listResult[i].score != 0) {
			//Position Vertical [nom]
			pos.x = 200;

			//Mise � jour de la position vertical
			pos.y = 200 + SCORE_TEXT_SIZE * i + 10;

			//Test si on � d�j� et que notre nouveau score existe
			bool isPlayer = (strlen(player.name) > 0 && strcmp(player.name, listResult[i].playerName) == 0 && player.score == listResult[i].score) ? TRUE  : FALSE ;

			//Colle les noms � l'image
			SDL_Surface* tempPlayerNameSurface = TTF_RenderText_Blended(policeScore, listResult[i].playerName, (isPlayer == TRUE) ? isPlayerTextColor : textColor);
			SDL_BlitSurface(tempPlayerNameSurface, NULL, SDL_GetVideoSurface(), &pos);
			SDL_FreeSurface(tempPlayerNameSurface);

			//Position Vertical [score]
			pos.x = 400;

			//Colle les score � l'image
			char c[20]; sprintf(c, "%d", listResult[i].score);

			SDL_Surface* tempPlayerScoreSurface = TTF_RenderText_Blended(policeScore, c, (isPlayer == TRUE) ? isPlayerTextColor : textColor);
			SDL_BlitSurface(tempPlayerScoreSurface, NULL, SDL_GetVideoSurface(), &pos);
			SDL_FreeSurface(tempPlayerScoreSurface);
		}//si non null
	}//for
}

//Boucle de mise � jour des donn�es
void scoreOnLoop() {

	//Permet de retourner vers le menu
	if(isReturn == TRUE) changeAppState(APP_STATE_MENU);
}

//Lib�re la m�moire
void scoreOnQuit() {

	//Lib�re les surfaces
	//SDL_FreeSurface(menuBackground);
	SDL_FreeSurface(textReturn);

	//Ferme le police
	TTF_CloseFont(policeText);
	TTF_CloseFont(policeScore);
}
