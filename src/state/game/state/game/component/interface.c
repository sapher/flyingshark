#include "state/game/state/game/component/interface.h"

//Initialise les donn�es relatives � interface
bool interfaceInit() {

	//Initialise le timer � 0
	timerBonus = 0;
	lastAddPoint = 0;
	numberBonusPoint = 0;
	lastAlphaChange = 0;
	alphaTempBackgound = 0;

	//Initialise le nombre de bombe � afficher � 0
	numberBombToShow = 0;

	//Initialise les compteurs de score � 0
	highScore = 0;

	//Charge la police
	police = TTF_OpenFont(FONT_GAME, GAME_FONT_SIZE);

	//Set a color [barbarian]
	textColor = Hex2SDLcolor(COLOR_WHITE);

	//Set a color [alizarine]
	scoreColor = Hex2SDLcolor(COLOR_RED);

	//Cr�� le texte bonus
	textBonusSurface = TTF_RenderText_Blended(police, "BONUS", textColor);

	//Cr�� le texte HighScore
	textHighScoreSurface = TTF_RenderText_Blended(police, "HIGH SCORE", textColor);

	//Cr�� le texte Score
	textPlayerScoreSurface = TTF_RenderText_Blended(police, "SCORE", textColor);

	//Cr�� un texte GameOver
	gameOverSurface = TTF_RenderText_Blended(police, "GAME OVER", textColor);

	//Charge le fichier score
	int sizeResult = loadScore(listResult);

	//Permet de r�cup�r� le plus haut score
	int i;
	for(i = 0; i < sizeResult; i++) {

		//R�cup�re le HighScore
		if(highScore < listResult[i].score) highScore = listResult[i].score;
		else break;

	}//for

	return TRUE;
}

//Charge l'interface
void interfaceLoad() {

	/********/
	durations = DURATION_SHOW_LEVEL_NAME + SDL_GetTicks();

	//Extrait le nom du niveau
	char levelFileName[40];
	sscanf(levelList[currentLevel], "%*d - %s", levelFileName);

	//Supprime l'extension [4 dernier]
	levelFileName[strlen(levelFileName)-strlen(LEVEL_EXTENSION)-1] = '\0';

	//Cr�� la couleur
	SDL_Color color	= Hex2SDLcolor(COLOR_BLUE);

	//G�n�re le nom du niveau
	textLevelNameSurface = TTF_RenderText_Blended(police, levelFileName, color);
	/********/
}

//Mise � jour des donn�es de l'interfaces
void interfaceLoop() {

	//Unused
	char buffer[33];

	switch(currentPilotingState) {
	//Mets � jour les donn�es du calcule du score
	case SCORING:

		//D�mare le timer
		if(timerBonus == 0) timerBonus = SDL_GetTicks() + BOMB_BONUS_INTERVAL;
		if(lastAddPoint == 0) lastAddPoint = SDL_GetTicks() + BONUS_ADD_POINT_INTERVAL;

		//Si il est temps d'afficher les bombes
		if(timerBonus <= SDL_GetTicks()) {

			if(numberBombToShow < player.numSpecialWeapon) {

				//Mets � jour le nombre de bombe � afficher
				numberBombToShow++;

				//Mise � jour du nombre de point
				numberBonusPoint = numberBombToShow * BOMB_BONUS_POINT;

				//Mets � jour le timer
				//TODO: ajouter une fonction pour la mise � jour du timer
				timerBonus = SDL_GetTicks() + BOMB_BONUS_INTERVAL;
			}//if
		}//if

		//Si il est temps d'afficher la mise � jour du score
		if(lastAddPoint <= SDL_GetTicks() && numberBombToShow == player.numSpecialWeapon) {

			//Si le nombre de point bonus est sup�rieur � 0
			if(numberBonusPoint > 0) {

				//Supprime le pas du nombre de points bonus
				numberBonusPoint -= BONUS_ADD_POINT_STEP;

				//Ajoute le pas au nombre de point du joueur
				player.score += BONUS_ADD_POINT_STEP;

				//Mets � jour le timer
				//TODO: ajouter une fonction pour la mise � jour du timer
				lastAddPoint = SDL_GetTicks() + BONUS_ADD_POINT_INTERVAL;
			}
			else {

				//Mise � jour du niveau
				currentLevel++;

				//On est arriver � la fin du jeu
				if(currentLevel+1 > numLevel) {
					changeGameState(GAME_STATE_ENDGAME);
					//return;
				}
				//Sinon charge le prochain niveau
				else {
					loadLevel(currentLevel);
				}
			}
		}//if

		//G�n�re la surface bonusPointSurface
		SDL_FreeSurface(bonusPointSurface); //Evite la mauvaise utilisation de la m�moire
		snprintf(buffer, 33, "%d", numberBonusPoint);
		bonusPointSurface	= TTF_RenderText_Blended(police, strcat(buffer, " POINTS"), scoreColor);

		break;

	default:
		timerBonus = 0;
		break;
	}

	//G�n�re la surface playerScore
	SDL_FreeSurface(numberPlayerScoreSurface); //Evite la mauvaise utilisation de la m�moire
	snprintf(buffer, 33, "%d", player.score);
	numberPlayerScoreSurface = TTF_RenderText_Blended(police, buffer, scoreColor);

	//Lorsque le score du joueur d�passe le highScore alors le nouveau highScore est celui du joueur
	//G�n�re la surface highScore
	SDL_FreeSurface(numberHighScoreSurface); //Evite la mauvaise utilisation de la m�moire
	snprintf(buffer, 33, "%d", (player.score > highScore) ? player.score : highScore);
	numberHighScoreSurface = TTF_RenderText_Blended(police, buffer, scoreColor);
}

//Affiche l'interface
void interfaceRender() {

	/**SCORE*/
    SDL_Rect positionPlayerScore = { POSITION_PLAYER_SCORE_X, POSITION_PLAYER_SCORE_Y };

    //Colle la surface texte Score � l'image
	SDL_BlitSurface(textPlayerScoreSurface, NULL, SDL_GetVideoSurface(), &positionPlayerScore);

	positionPlayerScore.y += textPlayerScoreSurface->h;

	SDL_BlitSurface(numberPlayerScoreSurface, NULL, SDL_GetVideoSurface(), &positionPlayerScore);

	/**HIGHSCORE*/
    SDL_Rect positionHighScore;
    positionHighScore.x = POSITION_HIGH_SCORE_X;
    positionHighScore.y = POSITION_HIGH_SCORE_Y;

    //Colle la surface texte highScore � l'image
	SDL_BlitSurface(textHighScoreSurface, NULL, SDL_GetVideoSurface(), &positionHighScore);

	positionHighScore.y += textHighScoreSurface->h;

	SDL_BlitSurface(numberHighScoreSurface, NULL, SDL_GetVideoSurface(), &positionHighScore);

	/**NOMBRE DE VIE*/
	SDL_Rect positionNumberLife = {POSITION_NUMBER_LIFE_X, POSITION_NUMBER_LIFE_Y, 0, 0};
	SDL_Rect spritePowerUpLife = {0, 0, POWERUP_WIDTH, POWERUP_HEIGHT};

	//Boucle qui vas afficher le nombre de vie
	int i;
	//Test qu'il y a des vies � afficher
	if(player.life > 0) {
		for(i = 0; i < player.life; i++) {

			//D�calage
			positionNumberLife.x +=  (i == 0) ? 0 : POWERUP_WIDTH + NUMBER_LIFE_SPACING;

			//Colle le nombre de vie � l'�cran
			SDL_BlitSurface(powerUpSurface, &spritePowerUpLife, SDL_GetVideoSurface(), &positionNumberLife);
		}
	}

	/**NOMBRE D'ARME SPECIAL*/
	SDL_Rect positionNumberSpecialWeapon = {POSITION_NUMBER_SPECIAL_WEAPON_X, POSITION_NUMBER_SPECIAL_WEAPON_Y, 0, 0};

	SDL_Rect spritePowerUpSpecialWeapon = {POWERUP_WIDTH * 4, 0, POWERUP_WIDTH, POWERUP_HEIGHT};

	//Boucle qui vas afficher le nombre d'arme sp�cial
	//Test qu'il y a des arme sp�cial � afficher
	if(player.numSpecialWeapon > 0) {
		for(i = 0; i < player.numSpecialWeapon; i++) {

			//D�calage
			positionNumberSpecialWeapon.x -=  (i == 0) ? 0 : POWERUP_WIDTH + NUMBER_SPECIAL_WEAPON_SPACING;

			//Colle le nombre de vie � l'�cran
			SDL_BlitSurface(powerUpSurface, &spritePowerUpSpecialWeapon, SDL_GetVideoSurface(), &positionNumberSpecialWeapon);
		}
	}

	switch(currentPilotingState) {

	//Affiche les donn�es du calcule de score
	case SCORING: {

		//Les variables
		int i;

		//Position � l'image
		SDL_Rect positionOnScreen;

		//Affiche le texte "BONUS"
		positionOnScreen.x = (SCREEN_WIDTH-textBonusSurface->w)/2;
		positionOnScreen.y = POSITION_BONUS_Y;
		SDL_BlitSurface(textBonusSurface, 0, SDL_GetVideoSurface(), &positionOnScreen);

		//Affiche le score bonus
		positionOnScreen.x = (SCREEN_WIDTH-bonusPointSurface->w)/2;
		positionOnScreen.y += BONUS_VERTICAL_SPACING;
		SDL_BlitSurface(bonusPointSurface, 0, SDL_GetVideoSurface(), &positionOnScreen);

		//Affiche les bombes
		SDL_Rect positionOnSprite = {POWERUP_WIDTH * 4, 0, POWERUP_WIDTH, POWERUP_HEIGHT};

		positionOnScreen.y += BONUS_VERTICAL_SPACING;
		for(i = 0; i < numberBombToShow; i++) {

			//Affiche les bombes au millieu de l'�cran
			positionOnScreen.x = (SCREEN_WIDTH - (POWERUP_WIDTH * player.numSpecialWeapon) - (BOMB_BONUS_SPACING/2) * player.numSpecialWeapon + BOMB_BONUS_SPACING)/2 + BOMB_BONUS_SPACING * i;

			SDL_BlitSurface(powerUpSurface, &positionOnSprite, SDL_GetVideoSurface(), &positionOnScreen);
		}//form

		break;
	}

	//Affiche le gameOver
	case GAME_OVER: {

		//Colle une surface noir
		SDL_Surface* tempBlackGround = SDL_CreateRGBSurface(SDL_SRCALPHA, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_PIXEL_FORMAT, 0, 0, 0, 0);

		//Appliqe la transparence
		setAlpha(tempBlackGround, alphaTempBackgound);

		//On modifie la valeur de la transparence
		if(lastAlphaChange <= SDL_GetTicks()) {

			if(alphaTempBackgound < 255) alphaTempBackgound++;
			//L'animation est terminer on peut retourner au menu
			else  {

				//Enregistre le score
				saveScore(player.name, player.score);

				changeAppState(APP_STATE_MENU);
			}

			//Mets � jour le timer
			lastAlphaChange = SDL_GetTicks() + ALPHA_CHANGE_INTERVAL;
		}//if

		//Colle la surface
		SDL_BlitSurface(tempBlackGround, 0, SDL_GetVideoSurface(), 0);

		//Lib�re la surface
		SDL_FreeSurface(tempBlackGround);

		//Colle la surface gameover � l'image
		SDL_Rect position = {(SCREEN_WIDTH - gameOverSurface->w)/2, (SCREEN_HEIGHT - gameOverSurface->h)/2, 0, 0};
		SDL_BlitSurface(gameOverSurface, NULL, SDL_GetVideoSurface(), &position);
	}

	break;
	}

	//Affiche le nom du niveau
	if(durations >= SDL_GetTicks()) {

		//D�fini la position � l'�cran
		SDL_Rect positionOnScreen;
		positionOnScreen.x = SCREEN_WIDTH/2 - textLevelNameSurface->w / 2;
		positionOnScreen.y = SCREEN_HEIGHT/2 - textLevelNameSurface->h / 2;

		//Colle la surface � l'�cran
		SDL_BlitSurface(textLevelNameSurface, NULL, SDL_GetVideoSurface(), &positionOnScreen);
	}
}


//Lib�re la m�moire
void interfaceQuit() {
	TTF_CloseFont(police);
}
