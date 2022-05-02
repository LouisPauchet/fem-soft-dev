
#ifndef DEf
#include "./EF.h"
#define dEF
#endif


//EFElementStruct//

int EFElementGetId(pEFElement);
pEFElement EFElementSetId(pEFElement, int);
int EFElementGetNode (pEFElement, int);
pEFElement EFElementSetNode (pEFElement, int, int);
double EFElementGetSpringRate(pEFElement);
pEFElement EFElementSetSpringRate(pEFElement, double);




//EFNodeStruct//

int EFNodeGetId (pEFNode);
pEFNode EFNodeSetId (pEFNode, int);
double EFNodeGetStress (pEFNode);
pEFNode EFNodeSetStress (pEFNode, double);
double EFNodeGetDisplacement (pEFNode);
pEFNode EFNodeSetDisplacement (pEFNode, double);