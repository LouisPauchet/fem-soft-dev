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
#include "Matrix.h"

#endif

#include <assert.h>

/**
 * @brief Fonction permettant d'obtenir la taille d'une matrice dans la direction X ou Y.
 * 
 * @param mat Pointeur sur un matrice
 * @param direction  Caractère indiquant la direction à utiliser. 
 * La direction ne peut-être que X ou Y.
 * Attention de bien tenir compte de la case.
 * @return int 
 */

int matrixGetSizeX(pMatrix mat, char direction) {
    
    assert(direction == 'Y' || direction == 'X');
    
    switch (direction) {
        case 'X' :
            return mat->SizeX;
        case 'Y' :
            return mat->SizeY;
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
 * @return BOOLEAN 
 */
BOOLEAN matrixFieldExist(pMatrix mat, int dX, int dY) {

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