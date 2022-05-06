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

#ifndef DList
#include "../../include/List.h"
#define DList
#endif

#include <string.h>

/**
 * @brief Fonction permettant d'obtenir une matrice dans une liste chainée à partir de son nom
 * 
 * @param workList Liste de travail
 * @param Name Nom de la matrice à rechercher.
 * @return pMatrix Renvoie un pointeur sur la matrice si elle existe dans la liste, NULL sinon.
 */

pMatrix MatrixListSearch ( list workList, char* Name) {

    workList = listGoFirst(workList);

    while (! listIsEmpty(workList))
    {
        if ( ! strcmp (matrixGetName( (pMatrix) listGetElement(workList)), Name)) {
            return (pMatrix) listGetElement(workList);
            printf("OK\n");
        }
        workList = listGetNext(workList);
    }

    return NULL;
    

    /*if (!listIsEmpty(workList)) {
        if ( ! strcmp (matrixGetName( (pMatrix) listGetElement(workList)), Name)) {
            return ((pMatrix) listGetElement(workList));
        }

        else {
            MatrixListSearch( listGetPrec(workList), Name);
            MatrixListSearch( listGetNext(workList), Name);
        }
    }*/

}

void matrixListShow( list workList) {
    workList = listGoFirst(workList);

    while (! listIsEmpty(workList))
    {
        matrixShow(listGetElement(workList));
        workList = listGetNext(workList);
    }
    
}