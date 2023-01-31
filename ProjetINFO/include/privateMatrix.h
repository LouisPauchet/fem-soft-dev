#ifndef DMatrix
#include "./Matrix.h"
#define DMatrix
#endif

//MatrixStruct//

int matrixGetSize(pMatrix, char);
void matrixSetSize(pMatrix, char, int);
void matrixSetName(pMatrix, char* );
char* matrixGetName(pMatrix);
void matrixShowName(pMatrix);
BOOLEAN matrixFieldExist(pMatrix, int, int);
BOOLEAN matrixIsSym(pMatrix);
void matrixSetSym(pMatrix);
void matrixSetValue(pMatrix, int, int, double);
double matrixGetValue(pMatrix, int, int);
pMatrix matrixAlloc();
pMatrix matrixUnAlloc(pMatrix);
void matrixUnInit(pMatrix);
void matrixInit(pMatrix);
void matrixSetZero(pMatrix);
pMatrix matrixNew(int, int, char*);