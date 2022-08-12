/*=INCLUSION=================================================================*/
#include "define.h"

//Etat du jeu
#include "state/intro/intro.h"
#include "state/menu/menu.h"
#include "state/game/game_state.h"
#include "state/score/score.h"
#include "state/input/input.h"

/*=CONSTANTES=================================================================*/

/*=VARIABLES=================================================================*/
//Musique
Mix_Music* Music_menu;

unsigned int startTicks;

/*=PROTOTYPES================================================================*/
bool Init();
void changeAppState(const char newState);
void LoadState();
void Event(SDL_Event* event);
void Loop();
void Render();
int	 Execute();
int	 Quit();
