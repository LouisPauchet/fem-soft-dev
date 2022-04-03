

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

    #ifndef NameLenth
/**
 * @brief Définition de la longueur des noms utilisables dans les matrices
 * 
 */
    #define NameLenth 20
    #endif


/**
 * @brief Définition d'un structure permettant de stocker un matrice, ses dimenssions et son nom.
 * 
 */

typedef struct Matrix {
    char name[NameLenth]; /**< @brief Tableau de caractère pour contenir le nom de la matrice*/
    double **tab; /**< @brief Tableau de double contenant les éléments de la matrice*/
    int SizeX; /**< @brief Taille de la matrice dans la direction X*/
    int SizeY; /**< @brief Taille de la matrice dans la direction Y*/
    BOOLEAN isSym; /**< @brief Valeur BOOLEAN permettant de savoir si la matrice est triangulaire ou non*/
} Matrix;

/**
 * @brief Définition d'un type de pointeur sur une matrice permettant d'augmenter la lisibilité du code.
 * 
 */

typedef Matrix* pMatrix;

#endif

pMatrix matrixNew(int, int, char*);
void matrixDel(pMatrix);
pMatrix matrixProduct(pMatrix, pMatrix);
pMatrix matrixTranspose(pMatrix);
pMatrix matrixSum(pMatrix, pMatrix);
pMatrix matrixScalar(pMatrix, double);

BOOLEAN matrixIsEqual(pMatrix, pMatrix);

void matrixShow(pMatrix);


