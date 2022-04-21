//#include "../include/Matrix.h"
#include "../include/MatrixList.h"

int main (void) {

    struct MatrixList* Liste = NULL;
    Liste = listInit();
        
    setMatrix(Liste, newMatrix());
    fillMatrix(getMatrix(Liste));

    newNodeEnd(Liste);
    setMatrix(getLast(Liste), newMatrix());
    fillMatrix(getMatrix(getLast(Liste)));


    //struct Matrix* mat1 = getMatrix(Liste);
    
    dispMatrix(getMatrix(getLast(Liste)));
    dispMatrix(getMatrix(getFirst(Liste)));

    //struct Matrix result = matrixProduct(getMatrix(getNodeByName(Liste,"toto")),getMatrix(getNodeByName(Liste,"titi")));

    newNodeEnd(Liste);
    struct Matrix result = matrixProduct(getMatrix(getNodeByName(Liste,"toto")),getMatrix(getNodeByName(Liste,"titi")));
    setMatrix(getLast(Liste),&result);

    dispMatrix(getMatrix(getNodeByName(Liste,"PM_toto-titi"))); 
    
    }