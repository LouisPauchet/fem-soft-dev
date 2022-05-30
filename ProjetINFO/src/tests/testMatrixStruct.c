/**
 * @file testMatrixStruct.c
 * @author Louis Pauchet
 * @brief Fichier des tests unitaires des fonctions permettant de manipuler les types @ref Matrix et @ref pMatrix
 * @version 0.1
 * @date 2022-05-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "./testHeader.h"

#ifndef Matrix
#include "../../include/Matrix.h"
#endif


static const double epsilon = 0.00000000001;

void test_matrixGetSize(void) {
    Matrix TestMatrix;
    TestMatrix.SizeX = 3;
    TestMatrix.SizeY = 2;
    
    CU_ASSERT_EQUAL(matrixGetSize(&TestMatrix,'X'), 3);
    CU_ASSERT_EQUAL(matrixGetSize(&TestMatrix,'Y'), 2);
    CU_ASSERT_NOT_EQUAL(matrixGetSize(&TestMatrix,'Y'), 3);
    CU_ASSERT_NOT_EQUAL(matrixGetSize(&TestMatrix,'X'), 2);
}


void test_matrixSetSize(void) {
    Matrix TestMatrix;
    matrixSetSize(&TestMatrix, 'X', 3);
    matrixSetSize(&TestMatrix, 'Y', 2);
    
    CU_ASSERT_EQUAL(matrixGetSize(&TestMatrix,'X'), 3);
    CU_ASSERT_EQUAL(matrixGetSize(&TestMatrix,'Y'), 2);
    CU_ASSERT_NOT_EQUAL(matrixGetSize(&TestMatrix,'Y'), 3);
    CU_ASSERT_NOT_EQUAL(matrixGetSize(&TestMatrix,'X'), 2);
}


void test_matrixFieldExist(void) {
    Matrix TestMatrix;
    matrixSetSize(&TestMatrix, 'X', 10);
    matrixSetSize(&TestMatrix, 'Y', 30);
    CU_ASSERT(matrixFieldExist(&TestMatrix, 2, 2));
    CU_ASSERT_FALSE(matrixFieldExist(&TestMatrix, 1000, 1000));
    CU_ASSERT_FALSE(matrixFieldExist(&TestMatrix, 1000, 2));
    CU_ASSERT_FALSE(matrixFieldExist(&TestMatrix, 2, 1000));
    CU_ASSERT(matrixFieldExist(&TestMatrix, 10, 30));
    CU_ASSERT(matrixFieldExist(&TestMatrix, 2, 30));
    CU_ASSERT(matrixFieldExist(&TestMatrix, 10, 2));
}

void test_matrixIsSym(void) {
    Matrix TestMatrix;
    CU_ASSERT_FALSE(matrixIsSym(&TestMatrix));
    TestMatrix.isSym = False;
    CU_ASSERT_FALSE(matrixIsSym(&TestMatrix));
    TestMatrix.isSym = True;
    CU_ASSERT(matrixIsSym(&TestMatrix));
    TestMatrix.isSym = 384993;
    CU_ASSERT_FALSE(matrixIsSym(&TestMatrix));
}
