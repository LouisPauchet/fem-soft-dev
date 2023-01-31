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





#include "../../include/EF.h"
#include "../../include/Matrix.h"

#include <stdio.h>
#include <stdlib.h>

extern BOOLEAN WorkWithTriangular;

int main(void)
{
    system("clear");
    //On crée le système mécanique.

    EFMecanicalSystem System;
    EFSystemInit(&System);

    char choice = 'n';

    printf("Voulez-vous travailler avec des matrices creuses ? (y/n)");
    scanf("%c", &choice);

    if (choice == 'y') WorkWithTriangular = True;

    EFCreateSystem(&System); //Créarion du système

    EFEquating(&System); //Mise en équations et résolution

    system("clear");

    listDoForList(System.ListOfMatrix, matrixShow); //Affichage des matrices
    //listDoForList(system.ListOfMatrix, matrixWrite);

    printf("\n\n\n *** Système résolu ***\n\n\n");

    EFDispSystem(System); //Affichage système final.

    printf("\n\n\n");

    EFSystemDelete(&System);

    return 0;
}
