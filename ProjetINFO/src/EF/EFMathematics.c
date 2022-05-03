/**
 * @file EFMathematics.c
 * @author Louis Pauchet (louis.pauchet@insa-rouen.fr)
 * @brief Définition des fonctions permettant la mise en équation d'un système mécanique.
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

/**
 * @brief Fonction réalisant l'assemblage de la matrice K
 * 
 * La gestion des cas de matrice creuse ou plein est directement géré via les fonctions sur la structure de matrice et notamment la fonction matrixGetValue.
 * 
 * @param listOfEFElement Liste chainée de EFElement
 * 
 * @return K renvoie un pointeur sur matrice pMatrix contenant la matrice K assemblée.
 */

pMatrix EFEquatingK(list listOfEFElement, list listOfEFNode) {
    int n = listGetSize (listOfEFNode);
    pMatrix K = matrixNew(n,n, "K");

    listOfEFElement = listGoFirst(listOfEFElement);

    for (int i = 0; i < n ; i++ ) {
        int a = EFElementGetNode(listGetElement(listOfEFElement), 1);
        int b = EFElementGetNode(listGetElement(listOfEFElement), 2); //On définie les coordonnées correspondant aux noeux attachés à l'élément.

        double sr = EFElementGetSpringRate(listGetElement(listOfEFElement));

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
        
        listOfEFElement = listGetNext(listOfEFElement);
    }

    return (pMatrix) K;
}

/**
 * @brief Fonction permettant de créer la matrice des déplacement à partir d'une list de noeuds.
 * 
 * @param listOfEFNode Liste chainée des noeuds à traiter.
 * @return pMatrix Pointeur sur la matrice U des déplacements pour les noeuds du système.
 */

pMatrix EFEquatingU(list listOfEFNode) {
    int n = listGetSize(listOfEFNode);
    pMatrix U = matrixNew(n, n, "U");

    for (int i = 0; i < n; i++) { //On parcours l'enssemble des noeuds présents dans la liste.
        matrixSetValue(U, i, 0, EFNodeGetDisplacement( (pEFNode) listGetElement(listOfEFNode)));
        listOfEFNode = listGetNext( listOfEFNode ); //On récupère l'élément suivant.
    }

}

/**
 * @brief Fonction permettant de remonter les efforts de la matrice F dans les noeuds du system mécanique.
 * 
 * @param mat Pointeur sur la matrice F.
 * @param listOfNode Pointeur sur le premier maillon de la list des noeuds.
 */

void EFEquatingF( pMatrix mat, list listOfNode) {
    int n = matrixGetSize(mat, 'X');

    for (int i = 0; i < n; i++) {
        EFNodeSetStress( (pEFNode) listGetElement(listOfNode), matrixGetValue(mat, i, 0));
        listOfNode = listGetNext(listOfNode);
    }
}

/**
 * @brief Fonction permettant de mettre en équation matriciel un system mécanique.
 * 
 * @param listOfEFNode Pointeur sur la liste chainée de noeuds représentant l'enssemble des noeuds du système.
 * @param listOfEFElement Pointeur sur la liste chainée d'éléments représentant l'enssemble des élémetns du système.
 * @param listOfMatrix Liste des matrices représentant le problème.
 */

void EFEquating(list listOfEFNode, list listOfEFElement, list listOfMatrix) {
    listOfMatrix = listAddEnd(listOfMatrix, (pMatrix) EFEquatingK (listOfEFElement, listOfEFNode)); //On ajoute la matrice K créer par la fonction EFEquatingK à la liste chainé de matrice.
    listAddEnd(listOfMatrix, (pMatrix) EFEquatingU (listOfEFNode)); //On ajoute la matrice U créer par la fonction EFEquatingU à la liste chainée de matrice.
    listAddEnd(listOfMatrix, (pMatrix) matrixProduct( MatrixListSearch(listOfMatrix, "K"), MatrixListSearch(listOfMatrix, "U"), "F")); // On réalise le produit matriciel F = KU et on stocke le résultat dans une matrice F.
    EFEquatingF( MatrixListSearch(listOfMatrix, "F"), listOfEFNode); //On remonte les efforts calculés dans le système mécanique.

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

