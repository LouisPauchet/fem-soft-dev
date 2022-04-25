/**
 * @file MatrixCalc.c
 * @author Louis Pauchet (louis.pauchet@insa-rouen.fr)
 * @brief Définition des fonctions publiques permettant de réaliser des opérations mathématiques élémentaires sur les matrices.
 * @version 0.1
 * @date 2022-04-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef Matrix
#include "../../include/Matrix.h"

#endif

/**
 * @brief Fonction permettant de réaliser le produit matriciel de deux matrices AB.
 * 
 * La fonction matrixProduct permet de réaliser le produit matriciel AB entre deux matrices en vérifiant la compatiblité des deux matrices.
 * 
 * La gestion d'une matrice creuse ou plein est réalisée directeur grâce à l'accesseur getValue.
 * 
 * @param matA Pointeur sur la matrice A
 * @param matB Pointeur sur la matrice B
 * @param Name Nom à donner à la nouvelle matrice
 * 
 * @return On revoie un pointeur sur une nouvelle matrice.
 */
pMatrix matrixProduct(pMatrix matA, pMatrix matB, char* Name) {

}

/**
 * @brief Fonction permettant de réaliser la transposée d'une matrice A
 * 
 * @param matA Pointeur sur la matrice A
 * 
 * @return On revoie un pointeur sur une nouvelle matrice.
 */

pMatrix matrixTranspose(pMatrix matA) {
    
}

/**
 * @brief Fonction permettant de réaliser la somme de deux matrices A + B
 * 
 * @param matA Pointeur sur la matrice A
 * @param matB Pointeur sur la matrice B
 * 
 * @return On revoie un pointeur sur une nouvelle matrice. 
 */

pMatrix matrixSum(pMatrix matA, pMatrix matB) {

}
 /**
  * @brief Fonction permettant de réaliser la multiplication d'une matrice A par un scalaire lambda.
  * 
  * @param matA Pointeur sur la matrice A
  * @param lambda Scalaire double précision
  * 
  * @return On revoie un pointeur sur une nouvelle matrice. 
  */

pMatrix matrixScalar(pMatrix matA, double lambda) {

}

/**
 * @brief Fonction permettant de comparer deux matrices A et B.
 * 
 * Cette fonction permet de vérifie successivement si les dimenssions de la matrice sont identiques, puis si les valeurs de la matrices sont identiques.
 * La comparaison des noms semble ne pas avoir de sens et n'est donc pas réalisé.
 * 
 * @param matA Pointeur sur la matrice A
 * @param matB Pointeur sur la matrice B
 * 
 * @return On retourne une valeur BOOLEAN True = 1 or False = 0.
 */

BOOLEAN matrixIsEqual(pMatrix matA, pMatrix matB) {

}