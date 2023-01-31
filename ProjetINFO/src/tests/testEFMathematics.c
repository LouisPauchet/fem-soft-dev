/**
 * @file testEFMathematics.c
 * @author Louis Pauchet
 * @brief Fichier contenant les fonctions permettant de tester le programme à partir d'exemples dont la solution est déjà connus comme par exemple l'exemple du TD5.
 * @version 0.1
 * @date 2022-05-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "./testHeader.h"

#include "../../include/EF.h"
#include "../../include/Matrix.h"


static const double epsilon = 0.00000000001;
extern BOOLEAN WorkWithTriangular;

/**
 * @brief Fonction permettant de tester le logiciel à partir de l'exemple du TD5
 * 
 * Dans cette fonction on va créer le system présenté dans le TD 5 et vérifier que les résultats sont cohérentes avec ceux données dans le TD5.
 * 
 * Ce est réalisé en mode boite noire et permet de tester globalement le logiciel. Il ne garantit pas le fonctionnement dans tous les cas.
 * 
 * 
 * Liste des noeuds
 * ----------------------------------------
 * 
 * Noeud 0 - Déplacement = 1 - Effort = NA
 * 
 * Noeud 1 - Déplacement = NA - Effort = 0
 * 
 * Noeud 2 - Déplacement = NA - Effort = 3
 * 
 * 
 * Liste des éléments
 * ---------------------------------------
 * 
 * Element 0 - Raideur = 1 - Connectivitée (0, 1)
 * 
 * Element 1 - Raideur = 1 - Connectivitée (1, 2)
 * 
 * Résultats vérifiés
 * ---------------------------------------
 * 
 * On vérifie que \f$U_f = \binom{5}{7} \f$
 * 
 */


void testBlindEF_exemple1(void) {
    EFMecanicalSystem System;
    EFSystemInit(&System);

    pEFNode NewNode =  EFNodeNew(0, 3.0, 0.0);
    System.ListOfNode = listAddEnd(System.ListOfNode, (pEFNode) NewNode);
    System.ListOfNodeR = listAddEnd(System.ListOfNodeR, (pEFNode) NewNode);

    NewNode = EFNodeNew(1, 0.0, 0.0);
    System.ListOfNode = listAddEnd(System.ListOfNode, (pEFNode) NewNode);
    System.ListOfNodeF = listAddEnd(System.ListOfNodeF, (pEFNode) NewNode);

    NewNode = EFNodeNew(2, 0.0, 2.0);
    System.ListOfNode = listAddEnd(System.ListOfNode, (pEFNode) NewNode);
    System.ListOfNodeF = listAddEnd(System.ListOfNodeF, (pEFNode) NewNode);


    pEFElement NewElement = EFElementNew(0, 0, 1, (double) 1.);
    System.ListOfElement = listAddEnd(System.ListOfElement, (pEFElement) NewElement);

    NewElement =  EFElementNew(1, 1, 2, (double) 1.);
    System.ListOfElement = listAddEnd(System.ListOfElement, (pEFElement) NewElement);

    EFDispSystem(System);
    EFEquating(&System);

    pMatrix FSol = matrixNew(3,1,"FSol");

    matrixSetValue(FSol, 0, 0, -2.0);
    matrixSetValue(FSol, 1, 0, 0.0);
    matrixSetValue(FSol, 2, 0, 2.0);


    pMatrix USol = matrixNew(2,1,"USol");

    matrixSetValue(USol, 0, 0, 5.0);
    matrixSetValue(USol, 1, 0, 7.0);

    //matrixShow(MatrixListSearch(System.ListOfMatrix, "F"));
    //matrixShow(FSol);

    //matrixShow(MatrixListSearch(System.ListOfMatrix, "Uf"));
    //matrixShow(USol);

    CU_ASSERT_TRUE( matrixIsEqual(MatrixListSearch(System.ListOfMatrix, "F"), FSol));
    CU_ASSERT_TRUE( matrixIsEqual(MatrixListSearch(System.ListOfMatrix, "Uf"), USol));


    //CU_ASSERT_EQUAL(matrixGetValue(MatrixListSearch(ListOfMatrix, 'F'),0,0), -2);
    //CU_ASSERT_EQUAL(matrixGetValue(MatrixListSearch(ListOfMatrix, 'F'),1,0), 0);
    //CU_ASSERT_EQUAL(matrixGetValue(MatrixListSearch(ListOfMatrix, 'F'),2,0), 2);

     
    
}

void testBlindEF_exemple1_sym(void) {


    WorkWithTriangular = True;

    EFMecanicalSystem System;
    EFSystemInit(&System);

    pEFNode NewNode =  EFNodeNew(0, 3.0, 0.0);
    System.ListOfNode = listAddEnd(System.ListOfNode, (pEFNode) NewNode);
    System.ListOfNodeR = listAddEnd(System.ListOfNodeR, (pEFNode) NewNode);

    NewNode = EFNodeNew(1, 0.0, 0.0);
    System.ListOfNode = listAddEnd(System.ListOfNode, (pEFNode) NewNode);
    System.ListOfNodeF = listAddEnd(System.ListOfNodeF, (pEFNode) NewNode);

    NewNode = EFNodeNew(2, 0.0, 2.0);
    System.ListOfNode = listAddEnd(System.ListOfNode, (pEFNode) NewNode);
    System.ListOfNodeF = listAddEnd(System.ListOfNodeF, (pEFNode) NewNode);


    pEFElement NewElement = EFElementNew(0, 0, 1, (double) 1.);
    System.ListOfElement = listAddEnd(System.ListOfElement, (pEFElement) NewElement);

    NewElement =  EFElementNew(1, 1, 2, (double) 1.);
    System.ListOfElement = listAddEnd(System.ListOfElement, (pEFElement) NewElement);


    EFEquating(&System);

    pMatrix FSol = matrixNew(3,1,"FSol");

    matrixSetValue(FSol, 0, 0, -2.0);
    matrixSetValue(FSol, 1, 0, 0.0);
    matrixSetValue(FSol, 2, 0, 2.0);


    pMatrix USol = matrixNew(2,1,"USol");

    matrixSetValue(USol, 0, 0, 5.0);
    matrixSetValue(USol, 1, 0, 7.0);

    //matrixShow(MatrixListSearch(System.ListOfMatrix, "F"));
    //matrixShow(FSol);

    //matrixShow(MatrixListSearch(System.ListOfMatrix, "Uf"));
    //matrixShow(USol);

    CU_ASSERT_TRUE( matrixIsEqual(MatrixListSearch(System.ListOfMatrix, "F"), FSol));
    CU_ASSERT_TRUE( matrixIsEqual(MatrixListSearch(System.ListOfMatrix, "Uf"), USol));


    //CU_ASSERT_EQUAL(matrixGetValue(MatrixListSearch(ListOfMatrix, 'F'),0,0), -2);
    //CU_ASSERT_EQUAL(matrixGetValue(MatrixListSearch(ListOfMatrix, 'F'),1,0), 0);
    //CU_ASSERT_EQUAL(matrixGetValue(MatrixListSearch(ListOfMatrix, 'F'),2,0), 2);

     
    
}

void testBlindEF_exemple2(void) {
    EFMecanicalSystem System;
    EFSystemInit(&System);

    //Création des noeuds

    pEFNode NewNode =  EFNodeNew(0, 4., 0.0);
    System.ListOfNode = listAddEnd(System.ListOfNode, (pEFNode) NewNode);
    System.ListOfNodeR = listAddEnd(System.ListOfNodeR, (pEFNode) NewNode);

    NewNode =  EFNodeNew(0, 2., 0.0);
    System.ListOfNode = listAddEnd(System.ListOfNode, (pEFNode) NewNode);
    System.ListOfNodeR = listAddEnd(System.ListOfNodeR, (pEFNode) NewNode);

    NewNode = EFNodeNew(1, 0.0, 4.0);
    System.ListOfNode = listAddEnd(System.ListOfNode, (pEFNode) NewNode);
    System.ListOfNodeF = listAddEnd(System.ListOfNodeF, (pEFNode) NewNode);

    NewNode = EFNodeNew(2, 0.0, 1.0);
    System.ListOfNode = listAddEnd(System.ListOfNode, (pEFNode) NewNode);
    System.ListOfNodeF = listAddEnd(System.ListOfNodeF, (pEFNode) NewNode);

    //Création des éléments

    pEFElement NewElement = EFElementNew(0, 0, 1, (double) 1.);
    System.ListOfElement = listAddEnd(System.ListOfElement, (pEFElement) NewElement);

    NewElement = EFElementNew(1, 1, 3, (double) 1.);
    System.ListOfElement = listAddEnd(System.ListOfElement, (pEFElement) NewElement);

    NewElement =  EFElementNew(2, 2, 3, (double) 1.);
    System.ListOfElement = listAddEnd(System.ListOfElement, (pEFElement) NewElement);

    NewElement = EFElementNew(3, 1, 2, (double) 1.);
    System.ListOfElement = listAddEnd(System.ListOfElement, (pEFElement) NewElement);


    EFEquating(&System);

    pMatrix FSol = matrixNew(4,1,"FSol");

    matrixSetValue(FSol, 0, 0, 2.0);
    matrixSetValue(FSol, 1, 0, -4.8);
    matrixSetValue(FSol, 2, 0, 3.8);
    matrixSetValue(FSol, 3, 0, -1.0);


    pMatrix USol = matrixNew(2,1,"USol");

    matrixSetValue(USol, 0, 0, 4.2);
    matrixSetValue(USol, 1, 0, 2.6);

    /*matrixShow(MatrixListSearch(System.ListOfMatrix, "F"));
    matrixShow(FSol);
    matrixShow(MatrixListSearch(System.ListOfMatrix, "Uf"));
    matrixShow(USol);*/

    CU_ASSERT_TRUE( matrixIsEqual(MatrixListSearch(System.ListOfMatrix, "F"), FSol));
    CU_ASSERT_TRUE( matrixIsEqual(MatrixListSearch(System.ListOfMatrix, "Uf"), USol));


    //CU_ASSERT_EQUAL(matrixGetValue(MatrixListSearch(ListOfMatrix, 'F'),0,0), -2);
    //CU_ASSERT_EQUAL(matrixGetValue(MatrixListSearch(ListOfMatrix, 'F'),1,0), 0);
    //CU_ASSERT_EQUAL(matrixGetValue(MatrixListSearch(ListOfMatrix, 'F'),2,0), 2);

     
}

void testBlindEF_exemple2_sym(void) {

    WorkWithTriangular = True;

    EFMecanicalSystem System;
    EFSystemInit(&System);

    //Création des noeuds

    pEFNode NewNode =  EFNodeNew(0, 4., 0.0);
    System.ListOfNode = listAddEnd(System.ListOfNode, (pEFNode) NewNode);
    System.ListOfNodeR = listAddEnd(System.ListOfNodeR, (pEFNode) NewNode);

    NewNode =  EFNodeNew(0, 2., 0.0);
    System.ListOfNode = listAddEnd(System.ListOfNode, (pEFNode) NewNode);
    System.ListOfNodeR = listAddEnd(System.ListOfNodeR, (pEFNode) NewNode);

    NewNode = EFNodeNew(1, 0.0, 4.0);
    System.ListOfNode = listAddEnd(System.ListOfNode, (pEFNode) NewNode);
    System.ListOfNodeF = listAddEnd(System.ListOfNodeF, (pEFNode) NewNode);

    NewNode = EFNodeNew(2, 0.0, 1.0);
    System.ListOfNode = listAddEnd(System.ListOfNode, (pEFNode) NewNode);
    System.ListOfNodeF = listAddEnd(System.ListOfNodeF, (pEFNode) NewNode);

    //Création des éléments

    pEFElement NewElement = EFElementNew(0, 0, 1, (double) 1.);
    System.ListOfElement = listAddEnd(System.ListOfElement, (pEFElement) NewElement);

    NewElement = EFElementNew(1, 1, 3, (double) 1.);
    System.ListOfElement = listAddEnd(System.ListOfElement, (pEFElement) NewElement);

    NewElement =  EFElementNew(2, 2, 3, (double) 1.);
    System.ListOfElement = listAddEnd(System.ListOfElement, (pEFElement) NewElement);

    NewElement = EFElementNew(3, 1, 2, (double) 1.);
    System.ListOfElement = listAddEnd(System.ListOfElement, (pEFElement) NewElement);


    EFEquating(&System);

    pMatrix FSol = matrixNew(4,1,"FSol");

    matrixSetValue(FSol, 0, 0, 2.0);
    matrixSetValue(FSol, 1, 0, -4.8);
    matrixSetValue(FSol, 2, 0, 3.8);
    matrixSetValue(FSol, 3, 0, -1.0);


    pMatrix USol = matrixNew(2,1,"USol");

    matrixSetValue(USol, 0, 0, 4.2);
    matrixSetValue(USol, 1, 0, 2.6);

    /*matrixShow(MatrixListSearch(System.ListOfMatrix, "F"));
    matrixShow(FSol);
    matrixShow(MatrixListSearch(System.ListOfMatrix, "Uf"));
    matrixShow(USol);*/

    CU_ASSERT_TRUE( matrixIsEqual(MatrixListSearch(System.ListOfMatrix, "F"), FSol));
    CU_ASSERT_TRUE( matrixIsEqual(MatrixListSearch(System.ListOfMatrix, "Uf"), USol));


    //CU_ASSERT_EQUAL(matrixGetValue(MatrixListSearch(ListOfMatrix, 'F'),0,0), -2);
    //CU_ASSERT_EQUAL(matrixGetValue(MatrixListSearch(ListOfMatrix, 'F'),1,0), 0);
    //CU_ASSERT_EQUAL(matrixGetValue(MatrixListSearch(ListOfMatrix, 'F'),2,0), 2);

     
}