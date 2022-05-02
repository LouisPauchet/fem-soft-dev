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

pMatrix MatrixListSearch ( list workList, char* Name) {

    if ( strcmp (matrixGetName( (pMatrix) listGetElement(workList)), Name)) {
        return workList;
    }

    else {
        MatrixListSearch( listGetPrec(workList), Name);
        MatrixListSearch( listGetNext(workList), Name);
    }

}