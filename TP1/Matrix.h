#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Déclaration des structures*/

#define NameLenth 20

struct Matrix
{  
    char name[NameLenth];
    double** tab;
    int sizeX;
    int sizeY;
};

/*Signature des fonctions déclarés*/

double getValue( struct Matrix, int, int); //Obtenir une valeur de la matrice
int getSizeX (struct Matrix); //Obtenir la taille X
int getSizeY (struct Matrix); //Obtenir la taille Y
char* getName (struct Matrix*); //Obtenir le nom de la matrice
void setSizeX (struct Matrix*, int); //Saisir la taille X
void setSizeY (struct Matrix*, int); //Saisir la taille Y
void setName (struct Matrix*, char*); //Saisir le nom
void setValue (struct Matrix*, double, int , int); //Saisir la valeur
void initMatrix( struct Matrix*); //Procédure d'initialisation d'une matrice
void initMatrixSilent( struct Matrix*); //Procédure d'initalisation silencieuse
void fillMatrix( struct Matrix*); //Procédure de remplissage d'une matrice
void dispMatrix( struct Matrix); //Procédure d'affichage d'une matrice
struct Matrix matrixProduct(struct Matrix*, struct Matrix*); //Procédure de calcul d'un produit matriciel

/* Déclaration des fonction */

/*Getteur*/
double getValue( struct Matrix mat, int X, int Y){
    return (mat.tab[X][Y]);
}

int getSizeX (struct Matrix mat) {
    return mat.sizeX;
} 

int getSizeY (struct Matrix mat) {
    return mat.sizeY;
}

char* getName (struct Matrix *mat) {
    /*char _name[NameLenth];
    strcpy(_name, mat.name);*/
    return mat->name;
}

/*Setteurs*/

void setSizeX (struct Matrix* mat, int X) {
    mat->sizeX = X;
}

void setSizeY (struct Matrix* mat, int Y) {
    mat->sizeY = Y;
}

void setName (struct Matrix* mat, char* name) {
    if (strlen(name) < NameLenth) {
        strcpy(mat->name,name);
    }

    else {
        printf("ERREUR - Chaine incompatible\n");
    }
}

void setValue (struct Matrix* mat, double value, int X, int Y){
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


/* Procédure réalisant le nommage, le dimenssionnment, l'allocation mémoire et la mise à zéro de la matrice passée en paramètre.
Le Type double est utilisé */

void initMatrix(struct Matrix* pMat) {
    /*Nom et dimenssion de la matrice*/

    printf("Donnez à nom à votre nouvelle matrice : ");
    fgets(pMat->name, sizeof(pMat->name), stdin);

    printf("Donnez les dimenssions de la matrice %s \n", getName(pMat));
    int _X, _Y;
    printf("Dimenssion X : ");
    scanf("%d", &_X);
    printf("Dimenssion Y : ");
    scanf("%d", &_Y);

    setSizeX(pMat, _X);
    setSizeY(pMat, _Y);

    initMatrixSilent(pMat);

    //system("clear");

    /*AllocationMémoire

    pMat->tab = (double**)malloc(pMat->sizeX*sizeof(double*));
    for (int i=0; i< pMat->sizeX; i++)
        pMat->tab[i] = (double*)malloc(pMat->sizeY * sizeof(double));

    /*Mise à zéro de la matrice

    /* Mise a zero des composantes
    for (int i=0;i<pMat->sizeX;i++)
        for (int j=0;j<pMat->sizeY;j++)
            pMat->tab[i][j]=0; */
}

/*Initialisation d'une matrice déjà nommé et dimenssionnée*/

void initMatrixSilent(struct Matrix* pMat) {

    /*AllocationMémoire*/

    pMat->tab = (double**)malloc(getSizeX(*pMat)*sizeof(double*));
    for (int i=0; i< pMat->sizeX; i++)
        pMat->tab[i] = (double*)malloc(getSizeX(*pMat) * sizeof(double));

    /*Mise à zéro de la matrice*/

    for (int i=0;i<getSizeX(*pMat);i++)
        for (int j=0;j<getSizeY(*pMat);j++)
            setValue(pMat, 0, i, j);
}


/*Procédure permettant de saisir ou modifier les données stockées dans la matrice*/

void fillMatrix(struct Matrix* pMat) {
    dispMatrix(*pMat);
    char choice;
    printf("Pour modifier tous les éléments de la matrice, saisir a, pour modifier certains éléments saisir u : ");
    scanf("%s", &choice);

    if (choice == 'a') {
        for (int i=0;i<getSizeX(*pMat);i++){
            for (int j=0;j<getSizeY(*pMat);j++){
                    double value;
                    system("clear");
                    dispMatrix(*pMat);
                    printf("(%d,%d) = ",i,j);
                    scanf("%lf",&value);
                    setValue(pMat, value, i, j);
                }
        }
    }

    else {
        char choice = 'y';

        while (choice =='y') {
            double value;
            int m,n;
            printf("Saisir coordonnée X de la valeur à modifier : ");
            scanf("%d", &m);
            printf("Saisir coordonnée X de la valeur à modifier : ");
            scanf("%d", &n);

            system("clear");
            dispMatrix(*pMat);

            printf("(%d,%d) = ",m,n);
            scanf("%lf",&value);

            setValue(pMat, value, m, n);

            printf("Saisir une autre valeur ? (y,n) ");
            scanf("%s", &choice);
        }
    }
}

/*Procédure pour afficher une matrice*/

void dispMatrix( struct Matrix Mat){

/* On créer la première ligne en affichant les numéros de colonnes */
system("clear");
    puts(getName(&Mat));
    printf("     "); //5 espaces

    for (int j=0;j<getSizeY(Mat);j++) {
        printf("  (%2d) ", j);
    }

/*On affiche le tableau avec le numéro de ligne*/

    printf(" \n");

        for (int i=0;i<getSizeX(Mat);i++){
            printf("(%2d) ", i);
            for (int j=0;j<getSizeY(Mat);j++){
                printf("|%5lf",getValue(Mat,i,j));
            }
            printf("|\n");
        }
}

/*Calcul du produit matriciel*/

struct Matrix matrixProduct(struct Matrix* mat1, struct Matrix* mat2) {
    // Vérification de la compatibilité et initialisation du résultat
    if (mat1->sizeY == mat2->sizeX) {
        struct Matrix result;
        char _name[NameLenth];
        strcat(_name, "PM_");
       
        strncat(_name, getName(mat1), (NameLenth-3)/2);
        strncat(_name, getName(mat2), (NameLenth-3)/2);

        setName(&result, _name);

        setSizeX(&result, getSizeX(*mat1));
        setSizeY(&result, getSizeY(*mat2));
        
        initMatrixSilent(&result);

        //Produit Matriciel

        for (int i=0; i < getSizeX(result); i++) {
            for (int j=0; j < getSizeY(result); j++) {
                double somme = 0;
                for (int k=0; k < getSizeY(*mat2); k++) {
                    somme += getValue(*mat1, i , k ) * getValue(*mat2, k , j );
                }
            }
        }

    }

    else {
        printf("Defaut de comptatibilité !");
        exit;
    }
}
