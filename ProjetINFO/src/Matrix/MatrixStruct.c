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
#include "../include/Matrix.h"

#endif

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
        case 'Y' :
            return mat->SizeY;
        default :
            fprintf(stderr, "matrixGetSize - Unknown dimension");
            exit(EXIT_FAILURE);
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
        case 'Y' :
            mat->SizeY = Size;
        default :
            fprintf(stderr, "matrixSetSize - Unknown dimension");
            exit(EXIT_FAILURE);
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
    if (strlen(Name) <= NameLenth)
        stpncpy(mat->name, Name, NameLenth);
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
        fprintf(stderr, "matrixSetValue - Out of range \n");
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
    if (matrixFieldExist(mat, dX, dY)) {
        if (matrixIsSym(mat) && (dX < dY))
            return mat->tab[dY][dX];
        else
            return mat->tab[dX][dY];
    }
    else {
        fprintf(stderr, "matrixGetValue - Out of range \n");
        exit(EXIT_FAILURE);
    }
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
        exit(EXIT_FAILURE);
    }

    else
        result->isSym = False;
        return result;
}


/**
 * @brief Fonction permettant d'établir les valeurs de la matrice à 0
 * 
 * @param mat Pointeur sur la matrice à modifier.
 */

void matrixSetZero(pMatrix mat) {
    for (int i = 0; i < matrixGetSize(mat,"X"); i++) {
        for (int j = 0; j < matrixGetSize(mat,"Y"); j++) {
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
 * @param X Entier signé définissant la dimension de la nouvelle matrice dans la direction X
 * @param Y Entier signé définissant la dimension de la nouvelle matrice dans la direction X
 * @param Name Pointeur sur un tableau de caractère contenant le nom de la nouvelle matrice.
 * 
 * @return On retourne une valeur BOOLEAN True = 1 or False = 0.
 */
pMatrix matrixNew(int X, int Y, char* Name) {
    pMatrix result = matrixAlloc();
    matrixSetSize(result,'X',X);
    matrixSetSize(result,'Y',Y);
    matrixSetName(result,Name);
    matrixSetZero(result);
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

}