#ifndef DList
#include "./List.h"
#define DList
#endif

#ifndef True

/**
 * @brief Définition des valeurs True = 1 pour augmenter la lisibilité du code
 */

#define True 1

/**
 * @brief Définition des valeurs False = 0 pour augmenter la lisibilité du code
 */

#define False 0

/**
 * @brief Définition d'un type BOOLEAN permettant d'utiliser True et False
 */

typedef int BOOLEAN;

#endif

#ifndef Matrix

    #ifndef NameLength
/**
 * @brief Définition de la longueur des noms utilisables dans les matrices
 * 
 */
    #define NameLength 20
    #endif

/**
 * @brief Définition d'un structure permettant de stocker un matrice, ses dimenssions et son nom.
 * 
 */

typedef struct Matrix {
    char name[NameLength]; /**< @brief Tableau de caractère pour contenir le nom de la matrice*/
    double **tab; /**< @brief Tableau de double contenant les éléments de la matrice*/
    int SizeX; /**< @brief Taille de la matrice dans la direction X*/
    int SizeY; /**< @brief Taille de la matrice dans la direction Y*/
    BOOLEAN isSym; /**< @brief Valeur BOOLEAN permettant de savoir si la matrice est triangulaire ou non
    * Par défaut, la matrice est considéré comme plein, c'est-à-dire non triangulaire.
    */
    BOOLEAN isInit; /** < @brief Valeur booléan permettant de vérifier si la matrice est initiatliser ou pas. Voir matrixInit */
    BOOLEAN isAlloc; /** < @brief Valeur booléan permettant de savoir si la matrice est alloué ou pas. Voir matrixAlloc */
} Matrix;

/**
 * @brief Définition d'un type de pointeur sur une matrice permettant d'augmenter la lisibilité du code.
 * 
 */

typedef Matrix* pMatrix;

#endif

extern BOOLEAN WorkWithTriangular;

pMatrix matrixNew(int, int, char*);
void matrixDel(pMatrix);
pMatrix matrixProduct(pMatrix, pMatrix, char*);
pMatrix matrixTranspose(pMatrix);
pMatrix matrixSum(pMatrix, pMatrix);
pMatrix matrixScalar(pMatrix, double);
pMatrix matrixReplace(pMatrix, pMatrix);
void matrixShow(pMatrix);
void matrixWrite (pMatrix, char* );
pMatrix matrixLoad (pMatrix, char*);
pMatrix MatrixListSearch ( list, char*);
void matrixListShow( list);


