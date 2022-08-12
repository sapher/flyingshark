#include "state.h"

//Structure basique
bool Init() {

	//Place le programme en �tat de "marche"
	isRunning = TRUE;

	//Initilise la bibliot�que SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) return FALSE;

    //Ajoute une icon � la fen�tre [appel avant setVideoMode sinon n'affiche pas l'icone]
    SDL_WM_SetIcon(IMG_Load(APP_ICON), NULL);

    //Cr�� une f�netre [HWSURFACE = Utilise la m�moire de la carte graphique | DOUBLEBUF = active le double buffering]
    if(SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_PIXEL_FORMAT, SDL_HWSURFACE | SDL_DOUBLEBUF) == NULL) return FALSE;

    //Initialise SDL_ttf
    if(TTF_Init() == -1) return FALSE;

    //Ajoute une titre � la fen�tre
    SDL_WM_SetCaption(GAME_TITLE, NULL);

    //Initialisation de la parie audio
    //Initialise l'API Mixer
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);

	//Initialise un "contexte" audio
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) return FALSE;

	//Alloue le nombre de canaux
	Mix_AllocateChannels(20);

	//Tweak
	state.stateCurrent = -1;

	//GameState
	changeAppState(APP_STATE_INTRO);

	//Active la conversion des touches en unicode [permet la capture des touches]
	SDL_EnableUNICODE(1);

    //Cache le pointeur de la souris
    SDL_ShowCursor(SDL_DISABLE);

	//L'initialisation � r�ussit
	return TRUE;
}

//Change de State
void changeAppState(const char newState) {

	//Appel l'activation du nouveau State
	switch(newState) {
	case APP_STATE_INTRO:
		introOnLoad();
		break;

	case APP_STATE_MENU:
		menuOnLoad();
		break;

	case APP_STATE_GAME:
		gameStateOnLoad();
		break;

	case APP_STATE_SCORE:
		scoreOnLoad();
		break;

	case APP_STATE_INPUT:
		inputOnLoad();
		break;
	}

	//Appel la d�sactivation du State en cours
	switch(state.stateCurrent) {
	case APP_STATE_INTRO:
		introOnQuit();
		break;

	case APP_STATE_MENU:
		menuOnQuit();
		break;

	case APP_STATE_GAME:
		gameStateOnQuit();
		break;

	case APP_STATE_SCORE:
		scoreOnQuit();
		break;

	case APP_STATE_INPUT:
		inputOnQuit();
		break;
	}

	//Change le state courant
	state.stateCurrent	= newState;
}

//Gestionnaire d'�v�nement
void Event(SDL_Event* event) {

	switch(state.stateCurrent) {
	case APP_STATE_INTRO:
		introOnEvent(event);
		break;

	case APP_STATE_MENU:
		menuOnEvent(event);
		break;

	case APP_STATE_GAME:
		gameStateOnEvent(event);
		break;

	case APP_STATE_SCORE:
		scoreOnEvent(event);
		break;

	case APP_STATE_INPUT:
		inputOnEvent(event);
		break;
	}
}

//Boucle de modification des donn�es
void Loop() {

	switch(state.stateCurrent) {
	case APP_STATE_INTRO:
		introOnLoop();
		break;

	case APP_STATE_MENU:
		menuOnLoop();
		break;

	case APP_STATE_GAME:
		gameStateOnLoop();
		break;

	case APP_STATE_SCORE:
		scoreOnLoop();
		break;

	case APP_STATE_INPUT:
		inputOnLoop();
		break;
	}
}

//Effectu le rendu
void Render() {

	//Rempli l'�cran avec une couleur noir
    SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0x00, 0x00, 0x00));

	switch(state.stateCurrent) {
	case APP_STATE_INTRO:
		introOnRender();
		break;

	case APP_STATE_MENU:
		menuOnRender();
		break;

	case APP_STATE_GAME:
		gameStateOnRender();
		break;

	case APP_STATE_SCORE:
		scoreOnRender();
		break;

	case APP_STATE_INPUT:
		inputOnRender();
		break;
	}

	//Met � jour l'�cran
	SDL_Flip(SDL_GetVideoSurface());
}

//Ex�cute le programme et renvoie le statue dans lequel le programme se termine
int	 Execute() {

	//Initialise
	if(Init() == FALSE) return EXIT_FAILURE;

	//Initialise un Event Handler
	SDL_Event event;

	//Boucle principale du programme
	while(isRunning == TRUE) {

		startTicks = SDL_GetTicks();

		//Gestion des �v�nements
		Event(&event);

		//Modification des donn�es
		Loop();

		//Effectue le rendu � l'�cran
		Render();

		//R�gule la rapidit� g�n�ral du jeu
		while(SDL_GetTicks() - startTicks < 1000 / FRAME_RATE);
	}

	//Quitte proprement
	return Quit();
}


//Quittre proprement
int Quit() {

	//Ferme le partie audio
	//Ferme le "contexte"
	Mix_CloseAudio();

	//Quitte SDL_Mixer
	Mix_Quit();

	//Ferme SDL_ttf
	TTF_Quit();

	//Quitte la SDL
	SDL_Quit();

	//Programme terminer conform�mant � sont but
	return EXIT_SUCCESS;
}
