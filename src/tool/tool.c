#include "tool/tool.h"

//Charge correctement une surface
SDL_Surface* loadImage(const char* path) {

	//R�cup�re l'extension du fichier
	if(strstr(path, "png") != NULL) return SDL_DisplayFormatAlpha(IMG_Load(path));

	return SDL_DisplayFormat(IMG_Load(path));
}

//Applique la transparence d'une couleur
int setColorKey(SDL_Surface* surface, int Rmask, int Gmask, int Bmask) {

	return SDL_SetColorKey(surface, SDL_RLEACCEL | SDL_SRCCOLORKEY , SDL_MapRGB(SDL_GetVideoSurface()->format, Rmask, Gmask, Bmask));
}

//Applique la transparence
void setAlpha(SDL_Surface* surface, int Amask) {

	SDL_SetAlpha(surface, SDL_RLEACCEL | SDL_SRCALPHA , Amask);
}

//Chiffre au hasard
int getRand(int min, int max) {
	SDL_Delay(2);
	srand(SDL_GetTicks());
	return rand()%(max-min) + min;
}

//Chiffre d�cimal entre 0.0 & 1.0
float getRandFloat() {
	SDL_Delay(2);
	srand(SDL_GetTicks());
	return (float)rand()/(float)RAND_MAX;
}

//Calcul l'angle en radians entre deux points
float getRadians2point(int x1, int y1, int x2, int y2) {
	return atan2(y2 - y1, x2 - x1);
}

//Converti une couleur hexad�cimal en SDL_Color
SDL_Color Hex2SDLcolor(Uint32 toConvert) {

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		SDL_Color color={(toConvert & 0x000000ff),(toConvert & 0x0000ff00)/0x100,(toConvert & 0x00ff0000)/0x10000,0};
	#else
		SDL_Color color = {(toConvert & 0x00ff0000)/0x10000,(toConvert & 0x0000ff00)/0x100,(toConvert & 0x000000ff),0};
	#endif

	return color;
}
