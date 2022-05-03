#include "../../include/privateMatrix.h"
#ifndef DMatrix
#include "../../include/Matrix.h"
#define DMatrix
#endif

#include <stdio.h>

#define DEBUG

extern BOOLEAN WorkWithTriangular;

void main(void)
{
    //printf("%d\n", WorkWithTriangular);
    //printf("%d\n", WorkWithTriangular);
    WorkWithTriangular = True;
    pMatrix mat1 = matrixNew(2,2,"Toto");
    pMatrix mat2 = matrixNew(3,2,"Titi");
    printf("%d", matrixIsSym(mat1));
    matrixShow(mat1);
    matrixSetValue(mat1, 0, 1, (double) 3.);
    matrixSetValue(mat1, 0, 0, (double) 5.);
    
    matrixSetValue(mat1, 1, 1, 6.);
    matrixShow(mat1);
    matrixShow(mat2);

    matrixShow(mat1);

    matrixWrite(mat1, "./");

    pMatrix matAA = matrixNew(2,2,"matAA");
    matrixSetValue(matAA,0,0,5);
    matrixSetValue(matAA,0,1,-6);
    matrixSetValue(matAA,1,0,12);
    matrixSetValue(matAA,1,1,8);
        
    matrixShow(matAA);

    matrixReplace(mat2, matrixSum(matAA, mat1));
    matrixShow(mat2);

    matrixReplace(mat2, matrixScalar(mat2, 42.6));
    matrixShow(mat2);

    matrixReplace(mat2, matrixTranspose(mat2));
    matrixShow(mat2);

    matrixReplace(mat2, matrixProduct(mat2, matAA,  "Test1"));
    matrixShow(mat2);

}
