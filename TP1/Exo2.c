#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Matrix.h"

int main() {
    struct Matrix mat1;
    struct Matrix mat2;

    initMatrix(&mat1);
    fillMatrix(&mat1);
    
    initMatrix(&mat2);
    fillMatrix(&mat2);
    

    system("clear");
    dispMatrix(mat1);
    dispMatrix(mat2);
    dispMatrix(matrixProduct(&mat1, &mat2));
    //dispMatrix(matrixTranspose(&mat1));
}


