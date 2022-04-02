#include "Matrix.h"


/*Procédure pour afficher une matrice*/

void Ligne() {
    for (int i=0; i<20; i++){
        printf("-");
    }
    printf("\n");
}

void dispMatrix( struct Matrix* Mat){

    Ligne();

/* On créer la première ligne en affichant les numéros de colonnes */
    printf("Affichage matrice : ");
    printf("%s \n",getNameMatrix(Mat));
    printf("     "); //5 espaces

    for (int j=0;j<getSizeY(*Mat);j++) {
        printf("    (%2d)   ", j);
    }

/*On affiche le tableau avec le numéro de ligne*/

    printf(" \n");

        for (int i=0;i<getSizeX(*Mat);i++){
            printf("(%2d) ", i);
            for (int j=0;j<getSizeY(*Mat);j++){
                printf("|%1.4e",getValue(*Mat,i,j));
            }
            printf("|\n");
        }
    Ligne();
}

/*Libère l'espace mémoire d'une matrice*/

void freeMatrix( struct Matrix* mat) {
    for (int i=0; i<getSizeX(*mat); i++)
        free(mat->tab[i]);
    free(mat->tab);
    mat = NULL;
}


/*Calcul du produit matriciel*/

struct Matrix matrixProduct(struct Matrix* mat1, struct Matrix* mat2) {

    //creation de la matrice

    struct Matrix result;
    char _name[NameLenth] = "\0";
    strcat(_name, "PM_");
       
    strncat(_name, getNameMatrix(mat1), (int)((NameLenth-3)/2));
    strcat(_name, "-");
    strncat(_name, getNameMatrix(mat2), (int)((NameLenth-3)/2));

    setName(&result, _name);


    // Vérification de la compatibilité et initialisation du résultat
    if (mat1->sizeY == mat2->sizeX) {
        setSizeX(&result, getSizeX(*mat1));
        setSizeY(&result, getSizeY(*mat2));
        //printf("%s", _name);

        initMatrixSilent(&result);

        //Produit Matriciel

        for (int i=0; i < getSizeX(result); i++) {
            for (int j=0; j < getSizeY(result); j++) {
                double somme = 0;
                for (int k=0; k < getSizeY(*mat2); k++) {
                    somme += getValue(*mat1, i , k ) * getValue(*mat2, k , j );
                    //printf("%d %d %d %lf \n",i,j,k,somme);
                }
                setValue(&result, somme, i, j);
            }
        }

       

    }

    else {
        printf("ERREUR - Produit Matriciel- Defaut de comptatibilité ! \n");
        setSizeX(&result,0); setSizeY(&result,0);
        initMatrixSilent(&result);
        exit;
    }

    return result;
}

struct Matrix matrixTranspose(struct Matrix* mat) {

    //creation de la matrice

    struct Matrix result;
    char _name[NameLenth] = "\0";
    strcat(_name, "TR_");
       
    strncat(_name, getNameMatrix(mat), (int)(NameLenth-1));
    setName(&result, _name);


    setSizeX(&result, getSizeY(*mat));
    setSizeY(&result, getSizeX(*mat));
    //printf("%s", _name);

    initMatrixSilent(&result);

    //Produit Matriciel

    for (int i=0; i < getSizeX(result); i++) {
        for (int j=0; j < getSizeY(result); j++) {
            setValue(&result, getValue(*mat,j,i), i, j);
        }
    }

    return result;
}

/*Calcul la somme de deux matrices*/

struct Matrix matrixSum(struct Matrix* mat1, struct Matrix* mat2) {

    struct Matrix result;
    char _name[NameLenth] = "\0";
    strcat(_name, "SUM_");
       
    strncat(_name, getNameMatrix(mat1), (int)((NameLenth-3)/2));
    strcat(_name, "-");
    strncat(_name, getNameMatrix(mat2), (int)((NameLenth-3)/2));

    if ((getSizeX(*mat1)==getSizeX(*mat2))&&(getSizeY(*mat1)==getSizeY(*mat2))) {
        setSizeX(&result, getSizeX(*mat1));
        setSizeY(&result, getSizeY(*mat1));
        initMatrixSilent(&result);

        for (int i=0; i<getSizeX(*mat1); i++) {
            for (int j=0; i<getSizeY(*mat1); j++){
                setValue(&result, getValue(*mat1,i,j)+getValue(*mat2,i,j), i, j);
            }
        }        
    }

    else {
        printf("ERREUR - Somme Matrice - Defaut de comptatibilité ! \n");
        initMatrixSilent(&result);
        exit;
    }
    return result;
}

/*Multiplication d'une matrice par un scalaire*/

struct Matrix matrixScalar(struct Matrix* mat, double a) {
    struct Matrix result;
    char _name[NameLenth] = "\0";
    strcat(_name, "SCP_");
       
    strncat(_name, getNameMatrix(mat), (int)((NameLenth-3)/2));
    

    setSizeX(&result, getSizeX(*mat));
    setSizeY(&result, getSizeY(*mat));
    initMatrixSilent(&result);
    for (int i=0; i<getSizeX(*mat); i++) {
        for (int j=0; i<getSizeY(*mat); j++){
            setValue(&result, getValue(*mat,i,j) * a, i, j);
        }
    }

    return result;

}

int matrixEqual(struct Matrix* mat1, struct Matrix* mat2) {
    int result = 1;

    if ((getSizeX(*mat1)==getSizeX(*mat2))&&(getSizeY(*mat1)==getSizeY(*mat2))) {
        for (int i=0; i<getSizeX(*mat1); i++) {
            for (int j=0; i<getSizeY(*mat1); j++){
                if (getValue(*mat1,i,j)!=getValue(*mat1,i,j)) {
                    result = 0;
                    break;
                }
                if (result == 0) {
                    break;
                }
            }
        }
    }

    else {
        result = 0;
    }

    return result;
}


