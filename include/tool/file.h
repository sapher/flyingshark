#ifndef FILE_H
#define FILE_H

/*=INCLUDES==================================================================*/
#include "define.h"
#include <dirent.h>

/*=CONSTANTES================================================================*/
#define BUFFER_MAX	255

/*=STRUCTURES================================================================*/
typedef struct playerResult {
	char playerName[PLAYERNAME_LENGTH];
	int score;
} playerResult;

/*=VARIABLES=================================================================*/
FILE*   scoreFile;	//Pointeur du fichier score

/*=PROTOTYPES================================================================*/

//Charge le fichier score, r�cup�re les donn�es et retourrne la taille du fichier
int loadScore(playerResult* listResult);

//Enregistre le score
bool saveScore(char* playerName, int playerScore);

//R�cup�re les noms de fichiers dans un dossier et retourne le nombre de fichier trouv�
int getFilesInDir(const char* dirPath, char*** listFile, const char* fileExt);

#endif /*FILE_H*/
