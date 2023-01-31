/**
 * @file testMatrixCalc.c
 * @author Louis Pauchet
 * @brief Fonctions contenant les fonctions permettant de tester les opérations mathématiques réalisées avec des @ref pMatrix et @ref Matrix.
 * @version 0.1
 * @date 2022-05-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "testHeader.h"
#include "../../include/Matrix.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/**
 * @brief Fonction permettant de tester le bon fonctionnement de la fonction matrixIsEqual
 * 
 * Les tests réalisées sont :
 *  - Deux matrices avec des dimenssions egals et mises à zéro sont bien égales
 *  - Deux matrice avec des dimenssions différents et mises à zéro sont bien différentes
 *  - Deux matrices avec des valeurs non nul différentes sur la diagonale sont bien différentes
 *  - Deux matrices avec des valeurs non nul égales sur la diagonale sont bien égales.
 *  - Deux matrices avec une valeurs n'appartenant pas à la diagonale identiques sont bien égales.
 *  - Deux matrices avec une valeurs n'appartenant pas à la diagonale différente sont bien différentes.
 * 
 */

void test_matrixIsEqual(void) {
    pMatrix matA = matrixNew(4,4,"matA");
    pMatrix matB = matrixNew(4,4,"matB");
    pMatrix matC = matrixNew(5,5,"matC");
    pMatrix matD = matrixNew(4,4,"matD");

    CU_ASSERT_TRUE( matrixIsEqual(matA, matB));
    CU_ASSERT_TRUE( ! matrixIsEqual(matA, matC));

    for (int i=0; i < matrixGetSize(matA, 'X'); i++) {
        matrixSetValue(matA, i, i, (double) i*i/23);
        matrixSetValue(matB, i, i, (double) i*i/23);
        matrixSetValue(matD, i, i, (double) i*i/21);
    }

        
    CU_ASSERT_TRUE( matrixIsEqual(matA, matB));
    CU_ASSERT_TRUE( ! matrixIsEqual(matA, matD))

    matrixSetValue(matA, 0, 1, 333e-3);
    matrixSetValue(matB, 0, 1, 333e-3);
    matrixSetValue(matD, 0, 1, 331e7);

    CU_ASSERT_TRUE( matrixIsEqual(matA, matB));
    CU_ASSERT_TRUE( ! matrixIsEqual(matA, matD))


}


#define DimMax 100
#define ValueMax 1000
#define ExpMax 8
#define nbTest 100

extern BOOLEAN WorkWithTriangular;

/**
 * @brief Fonction permettant de tester la fonction matrixSum
 * 
 * Nous testerons si la sommes de deux matrices quelconques (aléatoirement générée) est bien égale à ce qu'il faut.
 * 
 */

void test_matrixSum(void) {

    pMatrix ResultCalc, matA, matB, matResult;
    double A, B;


    for (int k = 0; k < nbTest; k++ ) {

        srand(time(NULL));
        int sizeX = (rand() % DimMax) + 5;
        int sizeY = (rand() % (DimMax / 10)) + 5;

        matA = matrixNew(sizeX, sizeY, "toto");
        matB = matrixNew(sizeX, sizeY, "titi");
        matResult = matrixNew(sizeX, sizeY, "toto");

        for (int i = 0; i < sizeX; i++) {
            for (int j =0; j < sizeY; j++) {
                A = ((rand() % ValueMax) / M_PI * pow(10, (rand() % ExpMax)));
                B = ((rand() % ValueMax) / M_PI * pow(10, (rand() % ExpMax)));

                matrixSetValue( matA, i, j, A);
                matrixSetValue( matB, i, j, B);
                matrixSetValue( matResult, i, j, (A + B));
            }
        }

        pMatrix ResultCalc = matrixSum(matA, matB, "toto");

        CU_ASSERT_TRUE( matrixIsEqual ( ResultCalc, matResult));

    }
    

}

/**
 * @brief Fonction permettant de tester la fonction matrixScalar
 * 
 * Test pour 100 matrices aléatoirement générés et de tailles aléatoire si la multiplication de matA par lambda.
 * 
 */

void test_matrixScalar(void) {
        pMatrix ResultCalc, matA, matB, matResult;
    double A, B;


    for (int k = 0; k < nbTest; k++ ) {

        srand(time(NULL));
        int sizeX = (rand() % DimMax) + 5;
        int sizeY = (rand() % (DimMax / 10)) + 5;

        matA = matrixNew(sizeX, sizeY, "toto");
        matResult = matrixNew(sizeX, sizeY, "toto");

        B = ((rand() % ValueMax) / M_PI * pow(10, (rand() % ExpMax)));

        for (int i = 0; i < sizeX; i++) {
            for (int j =0; j < sizeY; j++) {
                A = ((rand() % ValueMax) / M_PI * pow(10, (rand() % ExpMax)));
                

                matrixSetValue( matA, i, j, A);
                matrixSetValue( matResult, i, j, A * B);
            }
        }

        pMatrix ResultCalc = matrixScalar(matA, B, "toto");

        CU_ASSERT_TRUE( matrixIsEqual ( ResultCalc, matResult));

    }
    

}

void test_matrixProduct(void) {
    {  
        pMatrix matA = matrixNew (3,3,"toto");
        pMatrix matB = matrixNew (3,3,"toto");
        pMatrix matC = NULL;
        pMatrix matD = matrixNew (3,3,"toto");

        matC = matrixProduct(matA, matB, "toto");

        CU_ASSERT_TRUE (matrixIsEqual(matA, matB));
        CU_ASSERT_TRUE (matrixIsEqual(matA, matC));

        for (int i = 0; i<3; i++ ) {
            matrixSetValue(matA, i, i, 1);
            matrixSetValue(matB, i, i, 1);
        }

        matC = matrixProduct(matA, matB, "toto");

        CU_ASSERT_TRUE (matrixIsEqual(matA, matB));
        CU_ASSERT_TRUE (matrixIsEqual(matA, matC));

        for (int i = 0; i<3; i++) {
            for (int j=0; j<3; j++) {
                matrixSetValue(matA, i, i, (double) i + j);
                matrixSetValue(matB, i, i, (double) (9 - (i+j)));
            }
        }

        matC = matrixProduct(matA, matB, "toto");

        matrixSetValue(matD, 0,0, 1.4e1);
        matrixSetValue(matD, 1,1, 1.8e1);
        matrixSetValue(matD, 2,2, 2.0e1);

        CU_ASSERT_TRUE (matrixIsEqual(matC, matD));
    }

    {
        pMatrix ResultCalc, matA, matX, matB, matD;
        double A, B;


        for (int k = 0; k < nbTest; k++ ) {

            srand(time(NULL));
            int sizeX = 10;
            int sizeY = sizeX;
            int sizeZ = sizeX;

            matA = matrixNew(sizeX, sizeY, "toto");
            matX = matrixNew(sizeY, sizeZ, "titi");
            matB = matrixNew(sizeX, sizeZ, "toto");

            for (int i = 0; i < sizeX; i++) {
                for (int j =0; j < sizeY; j++) {
                    A = ((rand() % ValueMax) / M_PI );

                    matrixSetValue( matA, i, j, A);
                }
            }

            for (int i = 0; i < sizeY; i++) {
                for (int j =0; j < sizeZ; j++) {
                    A = ((rand() % ValueMax) / M_PI );

                    matrixSetValue( matX, i, j, A);
                }
            }

            matB = matrixProduct(matA, matX, "result");
            matD = matrixSystemSolve(matA, matB, "toto");

            //matrixShow(matD);
            //matrixShow(matX);

            CU_ASSERT_TRUE( matrixIsEqual (matX, matD ) );

            //matrixShow(matrixSum(matrixScalar(matD, -1.0), matX));

    }

    }
    

}

void test_matrixSolve(void) {
    
    pMatrix ResultCalc, matA, matX, matB, matD;
    double A, B;


    for (int k = 0; k < nbTest; k++ ) {

        srand(time(NULL));

        int choice = (rand() % 1);

        if ( choice ) WorkWithTriangular = True;

        else WorkWithTriangular = False;

        
        int sizeX = 20;
        int sizeY = sizeX;
        int sizeZ = sizeX;

        matA = matrixNew(sizeX, sizeY, "toto");
        matX = matrixNew(sizeY, sizeZ, "titi");
        matB = matrixNew(sizeX, sizeZ, "toto");

        for (int i = 0; i < sizeX; i++) {
            for (int j =0; j < sizeY; j++) {
                A = ((rand() % ValueMax) / M_PI );

                matrixSetValue( matA, i, j, A);
            }
        }

        for (int i = 0; i < sizeY; i++) {
            for (int j =0; j < sizeZ; j++) {
                A = ((rand() % ValueMax) / M_PI );

                matrixSetValue( matX, i, j, A);
            }
        }

        matB = matrixProduct(matA, matX, "result");
        matD = matrixSystemSolve(matA, matB, "toto");


        CU_ASSERT_TRUE( matrixIsEqual (matX, matD ) );
    }
    
}