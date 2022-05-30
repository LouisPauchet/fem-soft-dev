/**
 * @file EFNodeStruct.c
 * @author Louis Pauchet (louis.pauchet@insa-rouen.fr)
 * @brief Fonction permettant de manipuler les structures @ref EFNode et @ref pEFNode
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "../../include/privateEF.h"

#ifndef DEf
#include "../../include/privateEF.h"
#define DEf
#endif

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

pEFNode EFNodeFree(pEFNode node) {
    if (!(node = NULL)) {
    free(node);
    }
    return(node);
}

int EFNodeGetId (pEFNode node) {
    return node->id;
}

pEFNode EFNodeSetId (pEFNode node, int id) {
    node->id = id;
    return node;
}

double EFNodeGetStress (pEFNode node) {
    return node->stress;
}

pEFNode EFNodeSetStress (pEFNode node, double stress) {
    node->stress = stress;
    return node;
}

double EFNodeGetDisplacement (pEFNode node) {
    return node->displacement;
}

pEFNode EFNodeSetDisplacement (pEFNode node, double disp) {
    node->displacement = disp;
    return node;
}

pEFNode EFNodeNew( int id, double displacement, double stress) {

    pEFNode Node = malloc( sizeof(EFNode));
    EFNodeSetId(Node, id);
    EFNodeSetDisplacement(Node, displacement);
    EFNodeSetStress(Node, stress);

    return Node;

}