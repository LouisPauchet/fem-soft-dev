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


#include "../../include/privateMatrix.h"
#ifndef DMatrix
#include "../../include/Matrix.h"
#define DMatrix
#endif

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Fonction permettant de vérifier la compatibilité de deux matrice pour le produit matricielle.
 * 
 * @param matA Pointeur sur la matrice A
 * @param matB Pointeur sur la matrice B
 * @return BOOLEAN Renvoie True si les matrices sont compatible, False sinon.
 */
BOOLEAN matrixProductDimCheck(pMatrix matA, pMatrix matB) {
  if (matrixGetSize(matA,'Y') == matrixGetSize(matB, 'X')) {
    return True;
  }
  else {
    return False;
  }
}

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
  if (matrixProductDimCheck(matA,matB)) {
    char _name[NameLength] = "\0";
    strcpy(_name, Name);

    pMatrix result = matrixNew(matrixGetSize(matA, 'X'), matrixGetSize(matB, 'Y'), _name);

    double SUM = 0;

    for (int i = 0; i < matrixGetSize(result, 'X'); i++) {
      for (int j =0; j < matrixGetSize(result, 'Y'); j++) {
        SUM = 0;
        for (int k = 0; k < matrixGetSize (matA, 'Y'); k++) {
          SUM += matrixGetValue(matA, i, k) * matrixGetValue(matB, k, j);
          
        }
        //printf("%lf \n", SUM);
        matrixSetValue( result, i, j, SUM );
      }
    }
    matrixShow(result);
    return result;
  }

  else {
    fprintf(stderr, "matrixProduct - Incompatible Dimensions");
    exit(EXIT_FAILURE);
    return (pMatrix) 0;
  }
    
}

/**
 * @brief Fonction permettant de réaliser la transposée d'une matrice A
 * 
 * @param matA Pointeur sur la matrice A
 * 
 * @return On revoie un pointeur sur une nouvelle matrice.
 */

pMatrix matrixTranspose(pMatrix matA) {
  pMatrix matB = matrixNew(
    matrixGetSize(matA,'Y'),
    matrixGetSize(matA,'X'),
    matrixGetName(matA)
  );
  
  for (int i = 0; i < matrixGetSize(matA,'Y'); i++) {
    for (int j=0; j < matrixGetSize(matA,'X'); j++) {
      matrixSetValue(matB, j, i, matrixGetValue(matA, i, j));
    }
  }

  return matB;
}

/**
 * @brief Fonction permettant de réaliser la somme de deux matrices A + B
 * 
 * Pour réaliser la somme, la compatibilité des deux matrices est vérifié.
 * 
 * @param matA Pointeur sur la matrice A
 * @param matB Pointeur sur la matrice B
 * 
 * @return On revoie un pointeur sur une nouvelle matrice. En cas de défaut de compatibilité on renvéra un pointeur null.
 */

pMatrix matrixSum(pMatrix matA, pMatrix matB) {


  if (
    (matrixGetSize(matA,'X') == matrixGetSize(matB,'X')) && 
    (matrixGetSize(matA,'Y') == matrixGetSize(matB,'Y'))
    ) {
      char _name[NameLength] = "\0";
      strcat(_name, "SUM_");
      strncat(_name, matA->name, (int)((NameLength-3)/2));
      strcat(_name, "-");
      strncat(_name, matB->name, (int)((NameLength-3)/2));

      pMatrix matResult = matrixNew(
      matrixGetSize(matA,'X'),
      matrixGetSize(matA,'Y'),
      _name
      );

      for (int i = 0; i < matrixGetSize(matA,'X'); i++) {
        for (int j=0; j < matrixGetSize(matA,'Y'); j++) {
          //double x = matrixGetValue(matA, i, j);
          //double y = matrixGetValue(matB, i, j);
          //double r = x+y;
          matrixSetValue(
            matResult,
            i, 
            j, 
            (double) matrixGetValue(matA, i, j) + (double) matrixGetValue(matB, i, j)
          );
        } 
      } 

      return matResult;

    }
  
  else {
    fprintf(stderr, "matrixSum - Incompatible Dimensions");
    exit(EXIT_FAILURE);
    return (pMatrix) 0;
  }
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

  char _name[NameLength] = "\0";
  strcat(_name, "SCA_");
  strncat(_name, matA->name, (int)(NameLength-4));

  pMatrix matResult = matrixNew(
  matrixGetSize(matA,'X'),
  matrixGetSize(matA,'Y'),
  _name
  );

  for (int i = 0; i < matrixGetSize(matA,'Y'); i++) {
    for (int j=0; j < matrixGetSize(matA,'X'); j++) {
      matrixSetValue(
        matResult,
        i, 
        j, 
        matrixGetValue(matA, i, j) * lambda
      );
    } 
  } 

  return (pMatrix) matResult;
  
}
