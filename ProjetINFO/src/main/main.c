/**
 * @file main.c
 * @author Louis Pauchet (louis.pauchet@insa-rouen.fr)
 * @brief Programme principale du logiciel de calcul par élément finis.
 * @version 0.1
 * @date 2022-05-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */


//#include "../../include/List.h"


#include "../../include/EF.h"
#include "../../include/Matrix.h"

#include <stdio.h>

extern BOOLEAN WorkWithTriangular;

int main(int argc, char const *argv[])
{
    list ListOfMatrix = listEmpty();
    list ListOfNode = listEmpty();
    list ListOfElement = listEmpty();
    char choice = 'n';

    //printf("Voulez-vous travailler avec des matrices creuses ? (y/n)");
    //scanf("%c", &choice);

    if (choice == 'y') WorkWithTriangular = True;

    EFCreateSystem(&ListOfNode, &ListOfElement);

    EFEquating(ListOfNode, ListOfElement, ListOfMatrix);

    EFDispSystem(ListOfNode, ListOfElement);

    listDelList(ListOfNode, EFNodeFree);
    listDelList(ListOfElement, EFElementFree);
    listDelList(ListOfMatrix, matrixDel);   


    return 0;
}
