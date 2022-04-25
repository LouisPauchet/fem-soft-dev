#include "../../include/Matrix.h"
#include <stdio.h>


void main(void)
{
    pMatrix mat1 = matrixNew(2,2,"Toto");
    pMatrix mat2 = matrixNew(3,2,"Titi");
    matrixShow(mat1);
    matrixSetValue(mat1, 0, 0, (double) 5);
    matrixShow(mat1);
    matrixShow(mat2);
    matrixDel(mat1);
    matrixDel(mat2);
}
