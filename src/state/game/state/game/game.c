#include "state/game/state/game/game.h"

//Charge le state
bool gameOnLoad() {

	//Charge la liste de niveaux
	numLevel = getFilesInDir(LEVEL_PATH, &levelList, LEVEL_EXTENSION);

	//Charge la liste de scn�raio
	numScenario = getFilesInDir(SCENARIO_PATH, &scenarioList, SCENARIO_EXTENSION);

	//Si on n'a pas de niveau ni de scn�raion on ferme
	//if(numLevel == 0 || numScenario == 0 || numLevel != numScenario) return FALSE;

    //Charge l'interface
    if(interfaceInit() == FALSE) return FALSE;

	//Initialise les niveaux
	if(levelInit() == FALSE) return FALSE;

	//Initialise l'avion du joueur
	if(playerInit() == FALSE) return FALSE;

	//Initialise l'avion du joueur
	if(missileInit() == FALSE) return FALSE;

	//Charge le 1er niveau
	if(loadLevel(0) == FALSE) return FALSE;

	//Charge les explosions
	if(explosionInit() == FALSE) return FALSE;

	//Charge les powerups
	if(powerUpInit() == FALSE) return FALSE;

    //Charge les ennemis
    if(opponentInit() == FALSE) return FALSE;

	return TRUE;
}

//Lorsque l'�tat de jeu "jeu" devient actif
void gameOnActivate() {

	//R�active le son du moteur
	Mix_Resume(CH_FLIGHT);

	//R�active le son
	//Mix_ResumeMusic();
}

//Gestion des �v�nements
void gameOnEvent(SDL_Event* event) {

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

					//Droit
					case SDLK_RIGHT:
						isMoveRight = TRUE;
					break;

					//Gauche
					case SDLK_LEFT:
						isMoveLeft = TRUE;
					break;

					case SDLK_SPACE:
						missileLaunch(player.position);
					break;

					case SDLK_s:
						killAll();
					break;

					case SDLK_ESCAPE:
						if(currentPilotingState == PLAYER) changeGameState(GAME_STATE_PAUSE);
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

					//Droit
					case SDLK_RIGHT:
						isMoveRight = FALSE;
					break;

					//Gauche
					case SDLK_LEFT:
						isMoveLeft = FALSE;
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
void gameOnRender() {

    //Affiche le terrain
    levelRender();

    //Affiche les boules de feu
    missileRender();

    //Affiche les explosions
    explosionRender();

    //Affiche les ennemis
    opponentRender();

    //Affiche les explosions
    explosionRender();

    //Affiche les powerups
    powerUpRender();

	//Affiche l'avion du joeur
    playerRender();

    //Affiche l'interface
    interfaceRender();
}

//Boucle de mise � jour des donn�es
void gameOnLoop() {

	//Mise � jour des donn�es du niveau
	levelLoop();

	//Mets � jour la position des boules de feu lanc�e
	missileLoop();

	//Boucle qui mets � jour la position du joueur
	playerLoop();

	//Boucle qui mets � jour les donn�es relatives aux explosion
	explosionLoop();

	//Boucle qui mets � jour les donn�es relatives aux powerups
	powerUpLoop();

    //Mets � jour les donn�es des ennemis
    opponentLoop();

    //Boucle qui mets � jour les donn�es relatives � l'interface
    interfaceLoop();
}

//Lib�re la m�moire
void gameOnQuit() {

	explosionQuit();

	levelQuit();

	missileQuit();

	playerQuit();

	powerUpQuit();

	interfaceQuit();

	opponentQuit();
}
