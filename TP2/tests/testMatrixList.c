//#include "../include/Matrix.h"
#include "../include/MatrixList.h"

int main () {
    struct MatrixList* Liste = NULL;
    Liste = listInit();
        
    setMatrix(Liste, newMatrix());
    fillMatrix(getMatrix(Liste));

    newNodeEnd(Liste);
    setMatrix(getLast(Liste), newMatrix());
    fillMatrix(getMatrix(getLast(Liste)));

    dispMatrix(getMatrix(Liste));
    dispMatrix(getMatrix(getFirst(Liste)));

}