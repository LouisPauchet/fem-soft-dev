/**
 * @file EFMathematics.c
 * @author Louis Pauchet (louis.pauchet@insa-rouen.fr)
 * @brief Définition des fonctions permettant la mise en équation d'un système mécanique et la résolution des équations.
 * @version 0.1
 * @date 2022-04-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../../include/privateEF.h"
#ifndef DEf
#include "../../include/EF.h"
#define DEf
#endif

#include "../../include/privateMatrix.h"
#ifndef DMatrix
#include "../../include/Matrix.h"
#define DMatrix
#endif

#ifndef DList
#include "../../include/List.h"
#define DList
#endif

extern BOOLEAN WorkWithTriangular;

/**
 * @brief Fonction réalisant l'assemblage de la matrice K
 * 
 * La gestion des cas de matrice creuse ou plein est directement géré via les fonctions sur la structure de matrice et notamment la fonction matrixGetValue.
 * 
 * @param system Prend en entrée un pointeur sur un système mécanique complet.
 * 
 * @return K renvoie un pointeur sur matrice pMatrix contenant la matrice K assemblée.
 */

pMatrix EFEquatingK(EFMecanicalSystem* system) {
    int n = listGetSize (system->ListOfNode);
    pMatrix K = matrixNew(n,n, "K");

    list LocalListOfElement = listGoFirst(system->ListOfElement);

    while (!listIsEmpty(LocalListOfElement)) {
        int a = EFElementGetNode(listGetElement(LocalListOfElement), 1);
        int b = EFElementGetNode(listGetElement(LocalListOfElement), 2); //On définie les coordonnées correspondant aux noeux attachés à l'élément.

        double sr = EFElementGetSpringRate(listGetElement(LocalListOfElement));

        matrixSetValue(
            K,
            a,
            a, 
            matrixGetValue(K, a, a) + sr
            );

        matrixSetValue(
            K,
            a,
            b, 
            matrixGetValue(K, a, b) - sr
            );
        
        matrixSetValue(
            K,
            b,
            a, 
            matrixGetValue(K, b, a) - sr
            );

        matrixSetValue(
            K,
            b,
            b, 
            matrixGetValue(K, b, b) + sr
            );
        
        LocalListOfElement = listGetNext(LocalListOfElement);
    }

    return (pMatrix) K;
}

BOOLEAN IdIsEqual(list A, list B) {
    if (listIsEmpty(A) || listIsEmpty (B)) return False;

    return (BOOLEAN) (EFNodeGetId(listGetElement(A))) == (EFNodeGetId(listGetElement(B)));

}

/**
 * @brief Fonction permettant de créer la matrice des déplacement à partir d'une list de noeuds.
 * 
 * @param system Pointeur sur le système mécanique d'étude.
 * @return pMatrix Pointeur sur la matrice U des déplacements pour les noeuds du système.
 */

pMatrix EFEquatingU(EFMecanicalSystem* system) {
    int n = listGetSize(system->ListOfNode);
    pMatrix U = matrixNew(n, 1, "U");
/*
    list LocalListOfNode = listGoFirst(system->ListOfNode);

    for (int i = 0; i < n; i++) { //On parcours l'enssemble des noeuds présents dans la liste.
        matrixSetValue(U, i, 0, EFNodeGetDisplacement( (pEFNode) listGetElement(LocalListOfNode)));
        LocalListOfNode = listGetNext( LocalListOfNode ); //On récupère l'élément suivant.
    }

    return U;*/

    list listNodeSolve = listGoFirst(system->ListOfNodeR);
    list listNode = listGoFirst(system->ListOfNode);
    pMatrix Uf = MatrixListSearch(system->ListOfMatrix, "Uf");
    int i = 0;
    int j = 0;
    while (! listIsEmpty(listNode)) {
        
        if (IdIsEqual(listNode, listNodeSolve)) {
            matrixSetValue(U, i, 0, EFNodeGetDisplacement( (pEFNode) listGetElement(listNode)));
            listNodeSolve = listGetNext(listNodeSolve);
        }

        else {
            matrixSetValue(U, i, 0, matrixGetValue(Uf, j, (int) 0));
            EFNodeSetDisplacement(listGetElement(listNode), matrixGetValue(Uf, j, (int) 0));
            j++;
        }

        i ++;
        listNode = listGetNext(listNode);
    }

    return U;


}

/**
 * @brief Fonction permettant de remonter les efforts de la matrice F dans les noeuds du system mécanique.
 * 
 * @param mat Pointeur sur la matrice F.
 * @param listOfNode Pointeur sur le premier maillon de la list des noeuds.
 */

void EFEquatingF( pMatrix matF, list listOfNode) {
    int n = matrixGetSize(matF, 'X');
    int i=0;

    listOfNode = listGoFirst(listOfNode);

    while ( ! listIsEmpty(listOfNode)) {
        EFNodeSetStress( (pEFNode) listGetElement(listOfNode), matrixGetValue(matF, i, 0));
        
        //printf("%lf \n", matrixGetValue(matF, i, 0)), 
        listOfNode = listGetNext(listOfNode);
        i += 1;
    }
}


pMatrix EFExtract_Kff(EFMecanicalSystem system) {
    pMatrix K = MatrixListSearch(system.ListOfMatrix, "K");
    int nb_f = listGetSize(system.ListOfNodeF);
    pMatrix Kff = matrixNew(nb_f, nb_f, "Kff");

    list NodeFi = listGoFirst(system.ListOfNodeF);
    list NodeFj = listGoFirst(system.ListOfNodeF);

    for (int i = 0; i<nb_f; i++) {
        NodeFj = listGoFirst(system.ListOfNodeF);
        for (int j = 0; j<nb_f; j++) {
            matrixSetValue(Kff, i, j, matrixGetValue(K, EFNodeGetId(listGetElement(NodeFi)), EFNodeGetId(listGetElement(NodeFj))));
            NodeFj = listGetNext(NodeFj);
        }
        NodeFi = listGetNext(NodeFi);
    }

    return (pMatrix) Kff;

}

pMatrix EFExtract_Ff(EFMecanicalSystem system) {
    BOOLEAN bak = WorkWithTriangular;
    WorkWithTriangular = False; //Matrice non symétrique

    list Node = listGoFirst(system.ListOfNodeF);
    int size = listGetSize(Node);
    pMatrix Ff = matrixNew(size, 1, "Ff");

    for (int i = 0; i<size; i++) {
        matrixSetValue(Ff, i, 0, EFNodeGetStress((pEFNode) listGetElement(Node)));
        Node = listGetNext(Node);
    }

    WorkWithTriangular = bak;
    return (pMatrix) Ff;
    
}

pMatrix EFExtract_Kfr(EFMecanicalSystem system) {
    
    BOOLEAN bak = WorkWithTriangular;
    WorkWithTriangular = False; //Matrice non symétrique
    
    pMatrix K = MatrixListSearch(system.ListOfMatrix, "K");

    list NodeF = listGoFirst(system.ListOfNodeF);
    list NodeR = listGoFirst(system.ListOfNodeR);

    pMatrix Kfr = matrixNew(listGetSize(system.ListOfNodeF), listGetSize(system.ListOfNodeR), "Kfr" );

    for (int i = 0; i<listGetSize(system.ListOfNodeR); i++) {
        NodeF = listGoFirst(system.ListOfNodeF);
        for (int j = 0; j < listGetSize(system.ListOfNodeF); j++) {
            matrixSetValue(Kfr, j, i, matrixGetValue(K, EFNodeGetId(listGetElement(NodeR)), EFNodeGetId(listGetElement(NodeF))));
            NodeF = listGetNext(NodeF);
        }
        NodeR = listGetNext(NodeR);
    }
    //matrixShow(Kfr);

    WorkWithTriangular = bak;

    return (pMatrix) Kfr;

    
}

pMatrix EFExtract_Ur(EFMecanicalSystem system) {

    BOOLEAN bak = WorkWithTriangular;
    WorkWithTriangular = False; //Matrice non symétrique

    list Node = listGoFirst(system.ListOfNodeR);
    int size = listGetSize(Node);
    pMatrix Ur = matrixNew(size, 1, "Ur");

    for (int i = 0; i<size; i++) {
        matrixSetValue(Ur, i, 0, EFNodeGetDisplacement((pEFNode) listGetElement(Node)));
        Node = listGetNext(Node);
    }

    WorkWithTriangular = bak;

    return (pMatrix) Ur;

    
}

/**
 * @brief Fonction d'extraction des matrices pour la résolution du problème.
 * 
 * @param system Pointeur sur le system mécanique de travail.
 */

void EFExtractMatrixSolve(EFMecanicalSystem* system) {
    system->ListOfMatrix = listAddEnd(system->ListOfMatrix, EFExtract_Kff(*system));
    system->ListOfMatrix = listAddEnd(system->ListOfMatrix, EFExtract_Ff(*system));
    system->ListOfMatrix = listAddEnd(system->ListOfMatrix, EFExtract_Kfr(*system));
    system->ListOfMatrix = listAddEnd(system->ListOfMatrix, EFExtract_Ur(*system));

}

/**
 * @brief Fonction permettant de mettre en équation matriciel un system mécanique.
 * 
 * @param listOfEFNode Pointeur sur la liste chainée de noeuds représentant l'enssemble des noeuds du système.
 * @param listOfEFElement Pointeur sur la liste chainée d'éléments représentant l'enssemble des élémetns du système.
 * @param listOfMatrix Liste des matrices représentant le problème.
 */

void EFEquating(EFMecanicalSystem* system) {
    system->ListOfMatrix = listAddEnd(system->ListOfMatrix, (pMatrix) EFEquatingK (system)); //On ajoute la matrice K créer par la fonction EFEquatingK à la liste chainé de matrice.
    EFExtractMatrixSolve(system);
    //listAddEnd(system->ListOfMatrix, )


    BOOLEAN bak = WorkWithTriangular;
    WorkWithTriangular = False; //Matrice non symétrique
    
    pMatrix temp = matrixProduct(MatrixListSearch(system->ListOfMatrix, "Kfr"), MatrixListSearch(system->ListOfMatrix, "Ur"), "temp"); //Matrice permettant de réaliser les calculs
    matrixReplace(temp, matrixSubstraction(MatrixListSearch(system->ListOfMatrix, "Ff"), temp, "B"));
    listAddEnd(system->ListOfMatrix, temp);
    listAddEnd(system->ListOfMatrix, matrixSystemSolve(MatrixListSearch(system->ListOfMatrix, "Kff"), temp, "Uf"));

    WorkWithTriangular = bak;
    
    listAddEnd(system->ListOfMatrix, (pMatrix) EFEquatingU (system)); //On ajoute la matrice U créer par la fonction EFEquatingU à la liste chainée de matrice.
    listAddEnd(system->ListOfMatrix, (pMatrix) matrixProduct( MatrixListSearch(system->ListOfMatrix, "K"), MatrixListSearch(system->ListOfMatrix, "U"), "F")); // On réalise le produit matriciel F = KU et on stocke le résultat dans une matrice F.
    EFEquatingF( MatrixListSearch(system->ListOfMatrix, "F"), system->ListOfNode); //On remonte les efforts calculés dans le système mécanique.

}

/**
 * @brief Fonction permettant de revenir des équations matriciels au système mécanique.
 * 
 * @warning Cette fonction ne sera développé que lors du TD5.
 * 
 * @param ListOfEFNode Liste chainée de EFNode
 * @param listOfEFElement Liste chainée de EFElement
 * @param listOfMatrix Liste chainée de Matrix
 */


void EFRestitution(list ListOfEFNode, list listOfEFElement, list listOfMatrix) {

}

