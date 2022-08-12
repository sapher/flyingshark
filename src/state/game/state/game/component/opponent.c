#include "state/game/state/game/component/opponent.h"

//Initialise les donn�es relatives aux opponents
bool opponentInit() {

	//Charge les fireballs
	if(fireballInit() == FALSE) return FALSE;

	//Charge les
	if(boatInit() == FALSE) return FALSE;

	//Charge les bombers
	if(bomberInit() == FALSE) return FALSE;

	//Charge les fighters
	if(fighterInit() == FALSE) return FALSE;

	//Charge les tanks
	if(tankInit() == FALSE) return FALSE;

	return TRUE;
}

//Charge un sc�narion
void loadScenario(int scenarioNumber) {

	//Supprime les �nnemis dans le sc�nario
	memset(listOpponent, 0, sizeof listOpponent);

	//Nombre d'opposant initialis� � 0;
	numberOpponent = 0;

    //Ouvre le fichier en mode lecture
	char fullScenarioPath[100];
	strcpy(fullScenarioPath, SCENARIO_PATH);
	strcat(fullScenarioPath, scenarioList[scenarioNumber]);
    FILE* loadedScenario = fopen(fullScenarioPath, "r");

    //Test si ouvert
    if(loadedScenario != NULL) {

        //Variables
        char buffer[255];	//Une ligne du fichier

        //Pour chaque ligne du fichier
        while(fgets(buffer, sizeof buffer, loadedScenario) != NULL) {

            //R�cup�re les donn�es
            //[appearAt] - [type] - [direction] - [[fromX]-[fromY]] - [to] - [[velX] - [velY]]
            //Rempli la structure
            //TODO:cause crash
            sscanf(buffer, "%d - %d - %d - [%f - %f] - %d - [%f - %f]",
            		&listOpponent[numberOpponent].appearAt,
            		&listOpponent[numberOpponent].typeOpponent,
            		&listOpponent[numberOpponent].direction,
            		&listOpponent[numberOpponent].position.x,
            		&listOpponent[numberOpponent].position.y,
            		&listOpponent[numberOpponent].to,
            		&listOpponent[numberOpponent].velocity.x,
            		&listOpponent[numberOpponent].velocity.y
            );

            listOpponent[numberOpponent].isAppear = FALSE;

            numberOpponent++;

        }//while
    }

    //Ferme le fichier
    fclose(loadedScenario);
}

//Mise � jour des donn�es des opponents
void opponentLoop() {

	//Authorise ou non que les ennemis puissent attaquer
	authorizeAttack = (currentPilotingState == PLAYER) ? TRUE : FALSE;

	//Ajoute les opposants
	int i;
	for(i = 0; i < numberOpponent; i++) {

		//Respecte
		if(listOpponent[i].appearAt == floor(scrollMap) && listOpponent[i].isAppear == FALSE) {

			//Ajoute en fonction du type
			switch(listOpponent[i].typeOpponent) {

			//Bombardier gris & noir
			case BOMBER_GRAY:
				addOpponent(listOpponent[i], bomberList, bomberGraySurface, BOMBER_GRAY_SHADOW, BOMBER_GRAY_LIFE_POINT, BOMBER_GRAY_WIDTH, BOMBER_GRAY_HEIGHT);
				break;

			case BOMBER_BLACK:
				addOpponent(listOpponent[i], bomberList, bomberBlackSurface, BOMBER_BLACK_SHADOW, BOMBER_BLACK_LIFE_POINT, BOMBER_BLACK_WIDTH, BOMBER_BLACK_HEIGHT);
				break;

			//Bombardier gris & noir
			case FIGHTER_WHITE:
				addOpponent(listOpponent[i], fighterList, fighterWhiteSurface, FIGHTER_SHADOW_NORMAL, FIGHTER_LIFE_POINT, FIGHTER_WIDTH, FIGHTER_HEIGHT);
				break;

			//Bombardier gris & noir
			case FIGHTER_GOLD:
				addOpponent(listOpponent[i], fighterList, fighterGoldSurface, FIGHTER_SHADOW_NORMAL, FIGHTER_LIFE_POINT, FIGHTER_WIDTH, FIGHTER_HEIGHT);
				break;

			//Bombardier gris & noir
			case FIGHTER_BLUE:
				addOpponent(listOpponent[i], fighterList, fighterBlueSurface, FIGHTER_SHADOW_NORMAL, FIGHTER_LIFE_POINT, FIGHTER_WIDTH, FIGHTER_HEIGHT);
				break;

			//Bombardier gris & noir
			case FIGHTER_GREEN:
				addOpponent(listOpponent[i], fighterList, fighterGreenSurface, FIGHTER_SHADOW_NORMAL, FIGHTER_LIFE_POINT, FIGHTER_WIDTH, FIGHTER_HEIGHT);
			break;

			//Tank
			case TANK:
				addOpponent(listOpponent[i], tankList, tankSurface, 0, TANK_LIFE_POINT, TANK_WIDTH, TANK_HEIGHT);
				break;

			//Bateau
			case BOAT:
				addOpponent(listOpponent[i], boatList, boatSurface, 0, BOAT_LIFE_POINT, BOAT_WIDTH, BOAT_HEIGHT);
				break;
			}

			//N'afffichera plus
			listOpponent[i].isAppear = TRUE;
		}
	}

	//Mise � jour des donn�es des opponents
	fireballLoop();
	boatLoop();
	tankLoop();
	bomberLoop();
	fighterLoop();
}

//Affiche les opponents
void opponentRender() {

	//Affiche les opponents
	boatRender();
	tankRender();
	fireballRender();
	bomberRender();
	fighterRender();
}

//Nettoie la m�moire
void opponentQuit() {

	memset(listOpponent, 0, sizeof listOpponent);

	fireballQuit();
	boatQuit();
	tankQuit();
	bomberQuit();
	fighterQuit();
}

//Ajoute un opposant
void addOpponent(opponentScenario opponentBehavior, Opponent *opponentList, SDL_Surface* opponenturface, const int shadowAnimState, int lifePoint, int width, int height) {

	int i;
	for(i = 0; i < MAXIMUM_OPPONENT_LIST; i++) {

		//place vide
		if(opponentList[i].isExist == FALSE) {

			//Rempli les donn�es
			opponentList[i].alive		= TRUE;
			opponentList[i].animState	= 0;
			opponentList[i].direction	= opponentBehavior.direction;
			opponentList[i].isExist		= TRUE;
			opponentList[i].lastAnimStateChange = SDL_GetTicks();
			opponentList[i].lastAttack	= SDL_GetTicks();
			opponentList[i].lifePoint	= lifePoint;
			opponentList[i].position.x	= opponentBehavior.position.x;
			opponentList[i].position.y	= opponentBehavior.position.y;
			opponentList[i].position.h	= height;
			opponentList[i].position.w	= width;
			opponentList[i].type		= opponentBehavior.typeOpponent;
			opponentList[i].velocity.x	= opponentBehavior.velocity.x;
			opponentList[i].velocity.y	= opponentBehavior.velocity.y;
			opponentList[i].opponentSurface	= opponenturface;
			opponentList[i].shadowAnimState = shadowAnimState;

			break;
		}
	}//for
}

//Detruit un opposant
bool destroyOpponent(Opponent* opponent, int point) {

	//Si tu� mais existe encore, on le fait exploser
	if(opponent->lifePoint <= 0 && opponent->alive == TRUE) {

		//Ajoute explosion au centre du sprite
		addExplosion(opponent->position.x + opponent->position.w/2, opponent->position.y + opponent->position.h/2, FALSE);

		//Ajoute les points aux scores du joueur
		player.score += point;
		player.scorePowerUp += point;

		//Raye de la map
		opponent->alive = FALSE;
		opponent->isExist = FALSE;

		//Lorsque l'on doit afficher le powerup
		if(SCORE_POWERUP < player.scorePowerUp) {

			bool done = FALSE;

			while(done == FALSE) {
				int i = getRand(0, 4);
				switch (i) {
					case POWERUP_LIFE:
						if(player.life < DEFAULT_MAXIMUM_NUMBER_LIFE) {
							addPowerUp(opponent->position.x, opponent->position.y, POWERUP_LIFE);
							done = TRUE;
						}
						break;

					case POWERUP_WEAPON:
						addPowerUp(opponent->position.x, opponent->position.y, POWERUP_WEAPON);
						done = TRUE;
						break;

					case POWERUP_SPECIAL_WEAPON:

						if(player.numSpecialWeapon < DEFAULT_MAXIMUM_SPECIAL_WEAPON) {
							addPowerUp(opponent->position.x, opponent->position.y, POWERUP_SPECIAL_WEAPON);
							done = TRUE;
						}
						break;

					case POWERUP_1000:
						addPowerUp(opponent->position.x, opponent->position.y, POWERUP_1000);
						done = TRUE;
						break;

					default: break;
				}//switch
			}

			player.scorePowerUp = 0;

		}//if

		return TRUE;
	}//if

	return FALSE;
}

//Test collision avec opposant
bool isCollisionOpponent(Coordinates object, int damagePoint) {

	//Boucle pour chaque opposant
	int i;
	for(i = 0; i < MAXIMUM_OPPONENT_LIST; i++) {
		//BOAT
		if(boatList[i].isExist == TRUE && boatList[i].alive == TRUE) {
			if(isCollision(object, boatList[i].position) == TRUE)	{
				boatList[i].lifePoint	-= damagePoint;
				return TRUE;
			}
		}
		//TANK
		if(tankList[i].isExist == TRUE && tankList[i].alive == TRUE) {
			if(isCollision(object, tankList[i].position) == TRUE)	{
				tankList[i].lifePoint	-= damagePoint;
				return TRUE;
			}
		}
		//BOMBER
		if(bomberList[i].isExist == TRUE && bomberList[i].alive == TRUE) {
			if(isCollision(object, bomberList[i].position) == TRUE) {
				bomberList[i].lifePoint -= damagePoint;
				return TRUE;
			}
		}
		//FIGHTER
		if(fighterList[i].isExist == TRUE && fighterList[i].alive == TRUE) {
			if(isCollision(object, fighterList[i].position) == TRUE){
				fighterList[i].lifePoint-= damagePoint;
				return TRUE;
			}
		}
	}

	return FALSE;
}

//Affiche un opposant
void showOpponent(Opponent* opponent) {

	//Boucle pour tout les tanks
	int i;
	for(i = 0; i < MAXIMUM_OPPONENT_LIST; i++) {

		//Si le tank existe
		if(opponent[i].isExist == TRUE) {

			//Affiche l'opposant
			SDL_Rect opponentPositionOnScreen = {opponent[i].position.x, opponent[i].position.y, 0, 0};

			SDL_Rect opponentPositionOnSprite = {
					opponent[i].position.w * opponent[i].animState,
					opponent[i].position.h * opponent[i].direction,
					opponent[i].position.w,
					opponent[i].position.h
			};

			//Colle le tank � l'�cran
			SDL_BlitSurface(opponent[i].opponentSurface, &opponentPositionOnSprite, SDL_GetVideoSurface(), &opponentPositionOnScreen);

			//Affiche l'ombre
			if(opponent[i].shadowAnimState != 0) {

				//Mets � jour la position
				SDL_Rect shadowOpponentPositionOnScreen;
				shadowOpponentPositionOnScreen.x = opponent[i].position.x + MARGIN;
				shadowOpponentPositionOnScreen.y = opponent[i].position.y + MARGIN;

				opponentPositionOnSprite.x = opponent[i].position.w * opponent[i].shadowAnimState;

				//Colle le tank � l'�cran
				SDL_BlitSurface(opponent[i].opponentSurface, &opponentPositionOnSprite, SDL_GetVideoSurface(), &shadowOpponentPositionOnScreen);
			}

		}//if
	}//for
}

//Tue tout les opposants
void killAll() {

	//Test si il existe plus de 0 arme sp�cial
	if(player.numSpecialWeapon > 0) {

		int i;
		//Boucle pour tout les tanks
		for(i = 0; i < MAXIMUM_OPPONENT_LIST; i++) {

			//Lance le son de destruction
			Mix_PlayChannel(CH_PLAYER_DESTROY, SFX_player_destroy, 0);

			boatList[i].lifePoint	-=	5000;
			bomberList[i].lifePoint	-=	5000;
			fighterList[i].lifePoint-=	5000;
			tankList[i].lifePoint	-=	5000;
		}

		//Supprime une arme sp�cial
		player.numSpecialWeapon--;
	}
}
