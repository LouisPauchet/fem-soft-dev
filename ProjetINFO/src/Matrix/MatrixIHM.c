/**
 * @file MatrixIHM.c
 * @author Louis Pauchet (louis.pauchet@insa-rouen.fr)
 * @brief Définition des fonction publiques permettant à l'utilisateur d'interragir avec une matrice.
 * @version 0.1
 * @date 2022-04-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef Matrix
#include "Matrix.h"
#endif

#ifndef VA
#define VA
#include <stdarg.h>
#endif

#ifndef yes 1
#define yes 1
#define no 0
typedef int choice;
#endif

#ifndef stdio
#include <stdio.h>
#endif

#ifndef RowLenth
#define RowLenth 20
#endif


/** 
 * @brief Fonction permettant d'afficher une ligne de caractère de longueur n
 * 
 * @param n Nombre de répétition du caractère à afficher
 * @param c Le caractère à répéter
 *
*/

void PrintRow(int n, char c) {
        for (int i; i<n; i++){
            printf("%s",c);
        }
        printf("\n");
    }

/**
 * @fn va_list* matrixUserCreate()
 * @brief Fonction permettant de demander à l'utilisateur de saisir les paramètres qui seront donnés à matrixNew.
 * 
 * @bug Cette fonction n'a finalement pas été implémenté car n'est pas utilisé et le retour des paramètres à passer dans matrixNew semble très compliqué à réaliser.
 * 
 */
/*

va_list* matrixUserCreate() {
        
    choice UserChoice = yes;
    int X = 0, Y = 0;
    char Name[NameLenth];
    BOOLEAN isTriangular = False;


    PrintRow(RowLenth, "#");
    printf("Vous vous apprétez à créer une nouvelle matrice. Voulez-vous continuer ? (default yes/no)");
    scanf("%s", &UserChoice);

    switch (UserChoice) {
        case yes:
                printf("Parfait ! \n Commençons par donner un nom à la matrice");
                scanf("%s", Name);

                printf("Est-ce que la matrice sera triangulaire ? (yes/ default no)");
                scanf("%s", &isTriangular);

                printf("Dimenssion X de la matrice : ");
                scanf("%d", &X);
                
                printf("Dimenssion Y de la matrice : ");
                scanf("%d", &Y);


            break;
        
        case no:
                
            break;
    }


}
*/

/**
 * @brief Fonction permettant d'afficher une matrice
 * 
 * @param pmat Pointeur sur une matrice
 * 
 * @return Aucun retour attendu
 *
 */

void matrixShow(pMatrix pmat) {
    PrintRow(RowLenth, "-");

/* On créer la première ligne en affichant les numéros de colonnes */
    printf("Affichage matrice : ");
    puts(getName(pmat));
    printf("     "); //5 espaces

    for (int j=0;j<getSizeY(pmat);j++) {
        printf("    (%2d)   ", j);
    }

/*On affiche le tableau avec le numéro de ligne*/

    printf(" \n");

        for (int i=0;i<getSizeX(pmat);i++){
            printf("(%2d) ", i);
            for (int j=0;j<getSizeY(pmat);j++){
                printf("|%1.4e",getValue(pmat,i,j));
            }
            printf("|\n");
        }
    PrintRow(RowLenth, "-");
}