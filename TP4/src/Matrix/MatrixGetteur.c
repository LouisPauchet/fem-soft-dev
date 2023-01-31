/*##################################*/
/*Signature des fonction privé "Get"*/
/*##################################*/

double getValue(pMatrix, int, int); //Obtenir une valeur de la matrice
int getSizeX (pMatrix); //Obtenir la taille X
int getSizeY (pMatrix); //Obtenir la taille Y
char* getNameMatrix (pMatrix); //Obtenir le nom de la matrice

/*######################################*/
/*Développement des fonction privé "Get"*/
/*######################################*/

/* Déclaration des fonction */

/*Getteur*/
double getValue(pMatrix mat, int X, int Y){
    return (mat->tab[X][Y]);
}

int getSizeX (pMatrix mat) {
    return mat->sizeX;
} 

int getSizeY (pMatrix mat) {
    return mat->sizeY;
}

char* getNameMatrix (pMatrix mat) {
    return mat->name;
}

