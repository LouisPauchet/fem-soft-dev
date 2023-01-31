#include "Matrix.h"

/*##################################*/
/*Signature des fonction privé "Set"*/
/*##################################*/

void setSizeX (pMatrix, int); //Saisir la taille X
void setSizeY (pMatrix, int); //Saisir la taille Y
void setName (pMatrix, char*); //Saisir le nom
void setValue (pMatrix, double, int , int); //Saisir la valeur



/*##################################*/
/*Signature des fonction privé "Set"*/
/*##################################*/

void setSizeX (pMatrix mat, int X) {
    mat->sizeX = X;
}

void setSizeY (pMatrix mat, int Y) {
    mat->sizeY = Y;
}

void setName (pMatrix mat, char* name) {
    if (strlen(name) < NameLenth) {
        strcpy(mat->name,name);
    }

    else {
        printf("ERREUR - Chaine incompatible\n");
    }
}

void setValue (pMatrix mat, double value, int X, int Y){
    if (
        (getSizeX(*mat) > X) &&
        (getSizeY(*mat) > Y)
    ) {
        mat->tab[X][Y] = value;
    }

    else {
        printf("ERREUR - Dimenssion incomptibles");
    }
    
}