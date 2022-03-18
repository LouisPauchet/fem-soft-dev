
#include "./Matrix.h"

int main() {
    struct Matrix mat1;
    struct Matrix mat2;

    initMatrix(&mat1);
    initMatrix(&mat2);

    fillMatrix(&mat1);
    fillMatrix(&mat2);

    dispMatrix(matrixProduct(&mat1, &mat2));
}


