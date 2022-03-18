#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>

/* Déclaration des structures*/

struct Matrix
{  
    char name[20];
    double** tab;
    int sizeX;
    int sizeY;
};

/*Signature des fonctions déclarés*/

void initMatrix( struct Matrix*); //Procédure d'initialisation d'une matrice
void initMatrixSilent( struct Matrix*); //Procédure d'initalisation silencieuse
void fillMatrix( struct Matrix*); //Procédure de remplissage d'une matrice
void dispMatrix( struct Matrix); //Procédure d'affichage d'une matrice
struct Matrix matrixProduct(struct Matrix*, struct Matrix*); //Procédure de calcul d'un produit matriciel

/* Déclaration des fonction */

/* Procédure réalisant le nommage, le dimenssionnment, l'allocation mémoire et la mise à zéro de la matrice passée en paramètre.
Le Type double est utilisé */

void initMatrix(struct Matrix* pMat) {
    /*Nom et dimenssion de la matrice*/

    printf("Donnez à nom à votre nouvelle matrice\n");
    scanf("%s", pMat->name);

    printf("Donnez les dimenssions de la matrice %s \n", pMat->name);
    scanf("Dimenssion X : %d", pMat->sizeX);
    scanf("Dimenssion Y : %d", pMat->sizeY);

    initMatrixSilent(pMat);

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

    pMat->tab = (double**)malloc(pMat->sizeX*sizeof(double*));
    for (int i=0; i< pMat->sizeX; i++)
        pMat->tab[i] = (double*)malloc(pMat->sizeY * sizeof(double));

    /*Mise à zéro de la matrice*/

    for (int i=0;i<pMat->sizeX;i++)
        for (int j=0;j<pMat->sizeY;j++)
            pMat->tab[i][j]=0;
}


/*Procédure permettant de saisir ou modifier les données stockées dans la matrice*/

void fillMatrix(struct Matrix* pMat) {
    dispMatrix(*pMat);
    char choice;
    printf("Pour modifier tous les éléments de la matrice, saisir a, pour modifier certains éléments saisir u : ");
    scanf("%s", &choice);

    if (choice == 'a') {
        for (int i=0;i<pMat->sizeX;i++){
        for (int j=0;j<pMat->sizeY;j++)
            {
                system("clear");
                dispMatrix(*pMat);
                printf("(%d,%d) = ",i,j);
                scanf("%lf",pMat->tab[i][j]);
            }
        }
    }

    else {
        char choice = 'y';

        while (choice =='y') {
            int m,n;
            printf("Saisir coordonnée X de la valeur à modifier : ");
            scanf("%d", m);
            printf("Saisir coordonnée X de la valeur à modifier : ");
            scanf("%d", n);

            system("clear");
            dispMatrix(*pMat);
            printf("(%d,%d) = ",m,n);
            scanf("%lf",pMat->tab[m][n]);

            printf("Saisir une autre valeur ? (y,n) ");
            scanf("%s", &choice);
        }
    }
}

/*Procédure pour afficher une matrice*/

void dispMatrix( struct Matrix Mat){

/* On créer la première ligne en affichant les numéros de colonnes */

    printf("     "); //5 espaces

    for (int j=0;j<Mat.sizeY;j++) {
        printf("  (%2d) ", j);
    }

/*On affiche le tableau avec le numéro de ligne*/

    printf(" \n");

        for (int i=0;i<Mat.sizeX;i++){
            printf("(%2d) ");
            for (int j=0;j<Mat.sizeY;j++){
                printf("|%6lf",Mat.tab[i][j]);
            }
            printf("|\n");
        }
}

/*Calcul du produit matriciel*/

struct Matrix matrixProduct(struct Matrix* mat1, struct Matrix* mat2) {
    // Vérification de la compatibilité
    if (mat1->sizeY == mat2->sizeX) {
        struct Matrix result;
        result.name = 'PM_' + mat1->name + mat2->name;
        result.sizeY = mat1->sizeY;
        result.sizeX = mat2->sizeY;
        initMatrixSilent(&result);

        //Produit Matriciel

    }

    else {
        printf("Defaut de comptatibilité !");
        exit;
    }
}
