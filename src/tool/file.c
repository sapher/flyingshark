#include "tool/file.h"

int loadScore(playerResult* listResult) {

	int i=0;	//Compteur

   	//Tente d'ouvrir le fichier en mode lecture
	scoreFile = fopen(FILE_SCORE, "r");

	//Test si l'ouverture � reussit
	if(scoreFile == NULL) return FALSE;
	else {

		//Variable
		char buffer[BUFFER_MAX];	//Une ligne du fichier
		char buff_player[PLAYERNAME_LENGTH];	//Nom du joueur
		int buff_score = 0;

		//Ne prends que le nombre de player d�fini
		for(i = 0; i < MAX_PLAYER_SCORE; i++) {

			//V�rifier si on est pas arriv� � la fin du fichier
			if(fgets(buffer, sizeof(buffer), scoreFile) != NULL) {

				//Extrait les infos du fichier
				sscanf(buffer, "%s %d", buff_player, &buff_score);

				//Rempli le tableau
				strcpy(listResult[i].playerName, buff_player);
				listResult[i].score = buff_score;
			}
			else {

				//Quitte la boucle
				break;
			}//else
		}//for
	}//else

	//Ferme le fichier
	fclose(scoreFile);

	return i;
}

//Enregistre le score
bool saveScore(char* playerName, int playerScore) {

	//Variables
    int     lineCount = 0;          //Nombre de ligne dans le fichier
    char**  fileContentArray = NULL;//Fichier en m�moire
    int     i;                      //Compteur
    bool 	done = FALSE;      		//Permet de savoir si on � d�j� ajout� le nouveau score
    char    data[BUFFER_MAX];       //Nouvelle donn�e sous forme de chaine de caract�re

    //Ouvre le fichier en mode lecture/ecriture. Le fichier est cr�� s'il n'existe pas
	scoreFile = fopen(FILE_SCORE, "r");

    //Test si le fichier � �t� ouvert correctement
    if(scoreFile != NULL) {

        //Alloue la m�moire
        fileContentArray = (char**)malloc((lineCount+1) * sizeof(char*));

        //Copie le contenu du fichier en m�moire
        //Buffer
        char buffer[BUFFER_MAX];

        //Boucle d'exploration
        while(fgets(buffer, sizeof(buffer), scoreFile) != NULL) {

            //Alloue la m�moire
            fileContentArray = (char**)realloc(fileContentArray, (lineCount+1) * sizeof(char*));

            //Copie la ligne dans le tableau
            //fileContentArray[lineCount++] = strdup(buffer);
        }

        //Ferme le fichier
        fclose(scoreFile);

        //Rempli le fichier avec les nouvelles valeurs
        //Ecrase l'ancien fichier si celui-ci existe
        scoreFile = fopen(FILE_SCORE, "r");

        //Retrouve l'emplacement ou sera int�gr� le nouveau score
        //Variables
        int positionInFile  = lineCount;
        int scoreInFile     = 0;
        char playerInFile[40];
        for(i = 0; i < lineCount; i++) {

            //R�cup�re les valeurs
            sscanf(fileContentArray[i], "%s %d", strdup(playerInFile), &scoreInFile);

            //D�fini la position
            if(playerScore > scoreInFile) {
                positionInFile -= 1;
            }//if
        }//for

        //Ferme le fichier
        fclose(scoreFile);

        //Ouvre le fichier en mode �criture
        scoreFile = fopen(FILE_SCORE, "w");

        //Fichier non charg�
        if(scoreFile == NULL) return FALSE;

        i = 0;

        //Reste dans les limites d�finis
        while(i < lineCount + 1 && i < MAX_PLAYER_SCORE) {

            //Si on est arriv� � l'emplacement calcul�
            if(i == positionInFile) {

                //Mise en page
                if(i != lineCount) sprintf(data, "%s %d\n", playerName, playerScore);
                else sprintf(data, "\n%s %d\n", playerName, playerScore);

                //Enregistre les nouvelles donn�es
                fputs(data, scoreFile);

                done = TRUE;
            }//if

            //Enregistre l'ancien contenu dans le fichier
            else fputs(fileContentArray[(done == TRUE) ? i-1 : i ], scoreFile);

            i++;
        }//while

        //M�nage
        //Lib�re les �l�ments
        for(i = 0; i < lineCount; i++) free(fileContentArray[i]);

        //Lib�re l'array
        free(fileContentArray);

        //Ferme le fichier
        fclose(scoreFile);
    } else return FALSE;

    return TRUE;
}

//R�cup�re les noms de fichiers dans un dossier et retourne le nombre de fichier trouv�
int getFilesInDir(const char* dirPath, char*** listFile, const char* fileExt)
{
    //Les variables
    DIR*    levelDirectory;
    int     numOfLine = 0;	//Nombre de fichier
    struct  dirent *ent;

    //Ouvre le flux de dossier
    levelDirectory = opendir(dirPath);

    //Si on � trouver le dossier
    if(levelDirectory != NULL)
    {

    	//Pour chaque �l�ment trouv�
        while((ent = readdir(levelDirectory)) != NULL)
        {
        	//Si correspond � l'extensions
            if(strstr(ent->d_name, fileExt) != NULL)
            {

            	//R�alloue la m�moire pour la nouvelle entr�e
                *listFile = (char**)realloc(*listFile, (numOfLine+1) * sizeof(char*));

                //Chemin de fichier complet
                /*char fullPath[100];

                //Buff
                strcpy(fullPath, dirPath);
                strcat(fullPath, ent->d_name);

                (*listFile)[numOfLine++] = strdup(fullPath);*/

                (*listFile)[numOfLine++] = strdup(ent->d_name);
            }//if
        }//while
    }//if

    //Ferme le flux
    closedir(levelDirectory);

    return numOfLine;
}
