/**
 * @file MatrixList
 * @author Louis Pauchet (louis.pauchet@insa-rouen.fr)
 * @brief 
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "../../include/privateMatrix.h"
#ifndef DMatrix
#include "../../include/Matrix.h"
#define DMatrix
#endif

#include "../../include/List.h"

#include <string.h>

/**
 * @brief Fonction permettant d'obtenir une matrice dans une liste chainée à partir de son nom
 * 
 * @param workList Liste de travail
 * @param Name Nom de la matrice à rechercher.
 * @return pMatrix 
 */

pMatrix MatrixListSearch ( list workList, char* Name) {

    if ( strcmp (matrixGetName( (pMatrix) listGetElement(workList)), Name)) {
        return ((pMatrix) listGetElement(workList));
    }

    else {
        MatrixListSearch( listGetPrec(workList), Name);
        MatrixListSearch( listGetNext(workList), Name);
    }

}