/**
 * @file EFMecanicalSystemStruct.c
 * @author Louis Pauchet
 * @brief Définision des fonctions permettant de manipuler le type @ref EFMecanicalSystem
 * @version 0.1
 * @date 2022-05-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../../include/privateEF.h"
#include "../../include/Matrix.h"

/**
 * @brief Fonction de susppression de toutes les listes chainées d'un system mécanique.
 * 
 * @param System 
 */

void* NoFree(void* node) {
    return node;
}

void EFSystemDelete ( EFMecanicalSystem* System ) {
    
    listDelList(System->ListOfNode, EFNodeFree);
    listDelList(System->ListOfElement, EFElementFree);
    listDelList(System->ListOfMatrix, matrixDel);
    listDelList(System->ListOfNodeF, NoFree); //Les noeuds ont déjà été supprimés lors de la suppression de System->ListOfNode
    listDelList(System->ListOfNodeR, NoFree);

}

/**
 * @brief Fonction d'initialisation de toutes les listes chainées d'un system mécanique.
 * 
 * @param system 
 */

void EFSystemInit ( EFMecanicalSystem* system) {
    system->ListOfMatrix = listEmpty();
    system->ListOfNode = listEmpty();
    system->ListOfElement = listEmpty();
    system->ListOfNodeR = listEmpty();
    system->ListOfNodeF = listEmpty();
}