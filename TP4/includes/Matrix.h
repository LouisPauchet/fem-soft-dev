/*##################*/
/*Définition du type*/
/*##################*/

#define NameLenth 20

typedef struct Matrix
{  
    char name[NameLenth];
    double** tab;
    int sizeX;
    int sizeY;
    int isTriangular;
} Matrix;

typedef Matrix* pMatrix;

/*################################*/
/*Signature des fonction publiques*/
/*################################*/


pMatrix matrixNew(); //Création d'une matrice
void matrixDel(pMatrix); //Suppression d'une matrice

Matrix matrixProduct(pMatrix, pMatrix); //Fonction de calcul d'un produit matriciel
Matrix matrixTranspose(pMatrix); //Foonction de détermination de la transposée
Matrix matrixSum(pMatrix, pMatrix); //fonction pour réaliser une somme de matrice
Matrix matrixScalar(pMatrix, double); //fonction pour multiplier par un scalaire

int matrixCompare(pMatrix, pMatrix); //fonction permettant de comparer deux matrices

void matrixShow(pMatrix); //fonction permettant d'afficher une matrice
