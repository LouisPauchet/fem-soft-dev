/**
 * @file MatrixStruct.c
 * @author Louis Pauchet (louis.pauchet@insa-rouen.fr)
 * @brief Définision des fonctions publiques et privée permettant de manipuler la structure de matrice.
 * @version 0.1
 * @date 2022-04-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef Matrix
#include "../../include/Matrix.h"

#endif

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

BOOLEAN WorkWithTriangular = False;

/**
 * @brief Fonction permettant d'obtenir la taille d'une matrice dans la direction X ou Y.
 * 
 * @param mat Pointeur sur un matrice
 * @param direction  Caractère indiquant la direction à utiliser. 
 * La direction ne peut-être que X ou Y.
 * Attention de bien tenir compte de la case.
 * @return int 
 */

int matrixGetSize(pMatrix mat, char direction) { 

    switch (direction) {
        case 'X' :
            return mat->SizeX;
            break;
        case 'Y' :
            return mat->SizeY;
            break;
        default :
            fprintf(stderr, "matrixGetSize - Unknown dimension");
            //printf("matrixGetSize - Unknown dimension");
            exit(EXIT_FAILURE);
            break;
    }
}

/**
 * @brief Fonction permettant de définir la taille d'une matrice dans une direction 
 * 
 * En cas de mauvaise saisie de la direction, une erreur sera renvoyé et l'execution du programme s'arrètera avec le code "EXIT_FAILURE"
 * 
 * @param mat Pointeur sur une matrice
 * @param direction Direction pour laquelle on souhaite définir la taille.
 * Ne peut être égal qu'à X ou Y.
 * @param Size Taille de la matrice à paramètrer.
 */

void matrixSetSize(pMatrix mat, char direction, int Size) {
        
    switch (direction) {
        case 'X' :
            mat->SizeX = Size;
            break;
        case 'Y' :
            mat->SizeY = Size;
            break;
        default :
            fprintf(stderr, "matrixSetSize - Unknown dimension");
            exit(EXIT_FAILURE);
            break;
    }
}

/**
 * @brief Fonction permettant de définir le nom d'une matrice.
 * 
 * En cas de nom trop long, une erreur est écrite sur le flux d'erreur standart et le programme s'arrète avec le code "EXIT_FAILLURE"
 * 
 * @param mat Pointeur sur la matrice à modifier
 * @param Name Pointeur sur une chaine de caractère contenant le nom.
 */
void matrixSetName(pMatrix mat, char* Name) {
    if (strlen(Name) <= NameLength)
        stpncpy(mat->name, Name, NameLength);
    else {
        fprintf(stderr, "matrixSetName - Too long name, the extra characters have been removed");
    }
}

/**
 * @brief Fonction permettant d'obtenir le nom d'une matrice
 * 
 * @param mat Pointeur sur la matrice.
 * @return Renvoie un pointeur sur une chaine de caractère.
 */

char* matrixGetName(pMatrix mat) {
    return mat->name;
}

/**
 * @brief Fonction permettant d'afficher le nom de la matrice à la suite de la ligne en cours
 * 
 * Fonction créer en raison de problèmes de segmentation sur le fait de passer en paramètre de printf le retour de la fonction matrixGetName.
 * 
 * @param mat de type pMatrix, c'est à dire pointeur sur une structure de matrice.
 */

void matrixShowName(pMatrix mat) {
    printf("%s",mat->name);
}

/**
 * @brief Fonction permettant de vérifier si les indices fournies en paramètres sont bien dans les dimensions de la matrice.
 * 
 * @param mat Pointeur sur une matrice
 * @param dX Entier positif indiquant la position X à vérifier
 * @param dX Entier positif indiquant la position Y à vérifier
 * 
 * @return Renvoie une valeur BOOLEAN (True = 1 ou False = 0) si l'entrée est dans les dimenssions de la matrice ou pas.
 */

BOOLEAN matrixFieldExist(pMatrix mat, int dX, int dY) {
    if ((dX <= matrixGetSize(mat, 'X')) && 
        (dY <= matrixGetSize(mat, 'Y')))
        return True;
    else
        return False;
}

/**
 * @brief Fonction permettant de savoir si une matrice est triangulaire ou pas.
 * 
 * Par défaut, les matrices sont considérés comme non triangulaire.
 * 
 * @param mat Pointeur sur la matrice source
 * @return Renvoie une valeur BOOLEAN (True = 1 ou False = 0) en fonction du statut de la matrice
 */

BOOLEAN matrixIsSym(pMatrix mat) {
    if (mat->isSym == True)
        return True;
    else
        return False;
}

/**
 * @brief Procédure permettant de transformer une matrice en matrice triangulaire.
 * 
 * @param mat Pointeur sur la matrice à modifier.
 */

void matrixSetSym(pMatrix mat) {
    mat->isSym = True;
}

/**
 * @brief Fonction permettant de définir une matrice non triangulaire.
 * 
 * @param mat Matrice à modifier.
 */

void matrixSetNotSym (pMatrix mat) {
    mat->isSym  = False;
}

/**
 * @brief Fonction permettant d'entrer une valeur dans une matrice
 * 
 * Si la position est en dehors de la matrice, le programme sera stoppé avec le statut "EXIT_FAILURE" et un message d'erreur sera affiché dans le flux d'erreur standard.
 * 
 * Si la position d'écriture est dans la zone creuse de la matrice (X < Y), la saisie de la valeur est ignoré et un message d'erreur est indiqué dans le flux d'erreur standard sans interruption du programme.
 * 
 * @param mat Poitneur sur la matrice à modifier
 * @param dX Position dans la direction X
 * @param dY Position dans la direction Y
 * @param value Valeur à ajouter ou modifier. Réel en double précision.
 */
void matrixSetValue(pMatrix mat, int dX, int dY, double value) {
    if (matrixFieldExist(mat, dX, dY)) {
        if (matrixIsSym(mat) && (dX < dY)) {
            fprintf(stderr, "matrixSetValue - Triangular matrix, the entry %f at the position (%i,%i) was ignored \n", value, dX, dY);
        }
        else
            mat->tab[dX][dY] = value;
    }
        
    else {
        fprintf(stderr, "matrixSetValue - Out of range - %s %d %d\n", mat->name, dX, dY);
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Fonction permettant d'obtenir une valeur contenue dans une matrice.
 *
 * En cas d'accès à une valeur en dehors de la dimenssion de la matrice, le programme s'arrète avec le code "EXIT_FAILURE" et revoie un message d'erreur sur le flux d'erreur standart.
 * 
 * @param mat Pointeur sur la matrice
 * @param dX Position selon la direction X
 * @param dY Position selon la direction Y
 * @return Retourne un double correspondant à la valeur de la matrice concerné.
 */

double matrixGetValue(pMatrix mat, int dX, int dY) {
    
    /*if (matrixIsSym(mat)) {
        if (dX < dY) {

            return (double) (mat->tab[dY][dX]);
        }

        else {
            return (double) (mat->tab[dX][dY]);
        }
                    #ifndef DEBUG
            printf("GetValue - MatrixSymetrique");
            #endif
    }*/
    
    if (matrixFieldExist(mat, dX, dY)) {
        if (matrixIsSym(mat) && (dX < dY))
            return (double) (mat->tab[dY][dX]);
        else
            return (double) (mat->tab[dX][dY]);
    }
    else {
        fprintf(stderr, "matrixGetValue - Out of range - %s %d %d\n", mat->name, dX, dY);
        exit(EXIT_FAILURE);
    }
    //return mat->tab[dX][dY];
}

/**
 * @brief Fonction permettant d'allouer un espace mémoire à une matrice.
 * 
 * En cas d'erreur, le programme s'arrète en écrivant un message d'erreur sur le flux d'erreur. Dans le cas contraire un pointeur sur l'espace mémoire alloué est retourné.
 * 
 * @return Renvoie un pointeur pointant sur l'espace mémoire alloué.
 */

pMatrix matrixAlloc() {
    pMatrix result = NULL;
    if ((result = malloc(sizeof(Matrix))) == NULL) {
        fprintf(stderr, "matrixAlloc - Allocation Faillure");
        result->isAlloc = False;
        exit(EXIT_FAILURE);
    }

    else
        result->isSym = False;
        result->isAlloc = True;
        return result;
}

/**
 * @brief Fonction permettant de libérer l'espace mémoire alloué à une matrice
 * 
 * @param mat pointeur sur un matrice
 * @return renvoie NULL après la libération
 */

pMatrix matrixUnAlloc(pMatrix mat) {
    if (mat->isAlloc) {
        free(mat);
        return NULL;
    }

}

/**
 * @brief Procedure permettant de libérer la mémoire d'un tableau de matrice
 * 
 * @param mat Pointeur sur une matrice.
 */

void matrixUnInit(pMatrix mat) {
    if (mat->isInit) {
        for (int i = 0; i<matrixGetSize(mat, 'X'); i++) {
            free (mat->tab[i]);
        }
        free(mat->tab);
    }
}

/**
 * @brief Fonction permettant d'allouer l'espace mémoire d'un tableau de matrice
 * 
 * @param mat Pointeur sur la matrice.
 */

void matrixInit(pMatrix mat) {
    //printf("OKOK");
    mat->isInit = True;

    if (matrixIsSym(mat) && (! (matrixGetSize(mat, 'X') == matrixGetSize(mat, 'Y')) )) matrixSetNotSym(mat);

    if (matrixIsSym(mat)) {

        if ((mat->tab = (double**)malloc(matrixGetSize(mat, 'X')*sizeof(double*))) == NULL) {
            fprintf(stderr, "matrixInit - Allocation Faillure - Dimension X");
            mat->isInit = False;
            exit(EXIT_FAILURE);
            
        }
            for (int i=0; i< matrixGetSize(mat, 'X'); i++)
                if ((mat->tab[i] = (double*)malloc((matrixGetSize(mat, 'Y') - i)* sizeof(double))) == NULL) {
                    fprintf(stderr, "matrixInit - Allocation Faillure - Dimension Y at %d", i);
                    mat->isInit = False;
                    exit(EXIT_FAILURE);
                };
    }

    else {
        if ((mat->tab = (double**)malloc(matrixGetSize(mat, 'X')*sizeof(double*))) == NULL) {
            fprintf(stderr, "matrixInit - Allocation Faillure - Dimension X");
            exit(EXIT_FAILURE);
            mat->isInit = False;
        }
            for (int i=0; i< matrixGetSize(mat, 'X'); i++)
                if ((mat->tab[i] = (double*)malloc(matrixGetSize(mat, 'Y') * sizeof(double))) == NULL) {
                    fprintf(stderr, "matrixInit - Allocation Faillure - Dimension Y at %d", i);
                    exit(EXIT_FAILURE);
                    mat->isInit = False;
                };
    }

    /*
    mat->tab = (double**)malloc(matrixGetSize(mat, 'X')*sizeof(double*));
    for (int i=0; i< matrixGetSize(mat, 'X'); i++)
        mat->tab[i] = (double*)malloc(matrixGetSize(mat, 'Y') * sizeof(double));
        */
}

/**
 * @brief Fonction permettant d'établir les valeurs de la matrice à 0
 * 
 * @param mat Pointeur sur la matrice à modifier.
 */

void matrixSetZero(pMatrix mat) {
    for (int i = 0; i < matrixGetSize(mat,'X'); i++) {
        for (int j = 0; j < matrixGetSize(mat,'Y'); j++) {
            matrixSetValue(mat, i, j, (double) 0);
        }
    }
}

/**
 * @brief Fonction permettant de créer une nouvelle matrice en mémoire.
 * 
 * La fonction matrixNew réaliser la création d'une matrice, son allocation mémoire, ainsi que sa mise à zéro.
 * Elle renvoie un pointeur sur la matrice.
 * 
 * La définition de la variable global WorkWithTriangular permettera de travailler avec des matrices creuses.
 * 
 * @param X Entier signé définissant la dimension de la nouvelle matrice dans la direction X
 * @param Y Entier signé définissant la dimension de la nouvelle matrice dans la direction X
 * @param Name Pointeur sur un tableau de caractère contenant le nom de la nouvelle matrice.
 * 
 * @return On retourne une valeur BOOLEAN True = 1 or False = 0.
 */
pMatrix matrixNew(int X, int Y, char* Name) {
    //printf("%d %d %s", X, Y, Name);
    pMatrix result = matrixAlloc();
    matrixSetSize(result,'X',X);
    matrixSetSize(result,'Y',Y);
    matrixSetName(result,Name);
    //printf("A%d", result->isSym);
    if (WorkWithTriangular) matrixSetSym(result); //On utilise la variable globale WorkWithTriangular pour choisir si les matrices sont triangulaires ou pas.
    //result->isSym = True;
    
    //printf("A%d", result->isSym);
    matrixInit(result);
    matrixSetZero(result);
    return result;
}

/**
 * @brief Fonction permettant de supprimer proprement une matrice de la mémoire.
 * 
 * La fonction matrixDel permet de libérer la mémoire utilisé par le tableau de donnée et de désalouer l'espace mémoire utilisé par une matrice.
 * La fonction termine par définir le pointeur sur la matrice sur NILL.
 * 
 * @param mat Pointeur sur la matrice à supprimer.
 * 
 */

void matrixDel(pMatrix mat) {
    if (!(mat == NULL)) {
        matrixUnInit(mat);
        matrixUnAlloc(mat);
    }
    return NULL;
}

/**
 * @brief Fonction permettent de remplacer une matrice par une autre.
 * 
 * Attention le stockage de la matrice new sera supprimé.
 * 
 * @param old Pointeur sur la matrice à remplacer.
 * @param new Pointeur sur la matrice de remplacement
 * @return pMatrix Renvoie un pointeur sur la matrice modifié.
 */

pMatrix matrixReplace(pMatrix old, pMatrix new) {
    matrixUnInit(old);
    matrixSetSize(old,'X', matrixGetSize(new,'X'));
    matrixSetSize(old,'Y', matrixGetSize(new,'Y'));
    matrixInit(old);
    matrixSetName(old, "\0\0\0\0\0");
    strcpy(matrixGetName(old), matrixGetName(new));

    for (int i = 0; i<matrixGetSize(old,'X'); i++) {
        for (int j = 0; j<matrixGetSize(old,'Y'); j++) {
            matrixSetValue(old, i, j, matrixGetValue(new,i,j));
        }
    }
    
    matrixDel(new);
    return old;
}