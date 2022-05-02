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

#include "../../include/privateMatrix.h"
#ifndef DMatrix
#include "../../include/Matrix.h"
#define DMatrix
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
#define RowLenth 30
#endif


/** 
 * @brief Fonction permettant d'afficher une ligne de caractère de longueur n
 * 
 * @param n Nombre de répétition du caractère à afficher
 * @param c Le caractère à répéter
 *
*/

void PrintRow(int n, char c) {
        for (int i=0; i<n; i++){
            printf("%c", c);
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
    PrintRow(RowLenth, '-');

/* On créer la première ligne en affichant les numéros de colonnes */
    printf("Affichage matrice : ");
    matrixShowName(pmat);
    printf("\n");
    printf("     "); //5 espaces

    for (int j=0;j<matrixGetSize(pmat, 'Y');j++) {
        printf("     (%2d)    ", j);
    }

/*On affiche le tableau avec le numéro de ligne*/

    printf(" \n");

        for (int i=0;i<matrixGetSize(pmat, 'X');i++){
            printf("(%2d) ", i);
            for (int j=0;j<matrixGetSize(pmat, 'Y');j++){
                double a = matrixGetValue(pmat,i,j);
                if (matrixGetValue(pmat,i,j) < 0) {
                    printf("|%1.4e ",(double) matrixGetValue(pmat,i,j));
                }

                else {
                    printf("| %1.4e ",(double) matrixGetValue(pmat,i,j));
                }
                
            }
            printf("|\n");
        }
    PrintRow(RowLenth, '-');
}

#define MaxLength 50
/*
pMatrix matrixLoad (pMatrix mat, char* filePath) {
    matrixAlloc(mat);
    char fileName[60] = "\0";
    strcpy(fileName, filePath);
    FILE *doc = fopen(fileName, "r");
    
    char *buf = (char*) malloc( MaxLength );

    while (strcmp(buf, "name;") != 5) {
        fgets( buf, MaxLength, doc );
    }

    fscanf(doc,"name;%s\n", mat->name);
    fscanf(doc,"sizeX;%s\n", mat->SizeX );
    fscanf(doc, "sizeX;%s\n", mat->SizeY );
    
    matrixInit(mat);

    fclose(doc);

    return mat;
}
*/

/**
 * @brief Fonction permettant d'écrire une matrice dans un fichier texte au format CSV avec ";" comme séparateur.
 * 
 * Le fichier portera l'extension ".cMat" et sera nommé du nom de la matrice préfixé de "mat_"
 * 
 * @param mat Un pointeur sur la matrice à écrire.
 * @param filePath Le répertoire où écrire la matrice.
 */
void matrixWrite (pMatrix mat, char* filePath) {
    char fileName[60] = "\0";
    strcpy(fileName, filePath);
    strcat(fileName, "mat_");
    strcat(fileName, mat->name);
    strcat(fileName, ".cMat");
    FILE *doc = fopen(fileName,"a");

    fprintf(doc, "< MatrixBegin >\n");
    char _name[NameLength] = "\0";
    strcpy(_name, mat->name);
    fprintf(doc, "name; %s\n", _name);
    fprintf(doc, "sizeX; %d\n", matrixGetSize(mat, 'X'));
    fprintf(doc, "sizeY; %d\n", matrixGetSize(mat, 'Y'));
    
    for (int i = 0; i < matrixGetSize(mat, 'X'); i++) {
        for (int j = 0; j < matrixGetSize(mat, 'Y'); j++) {
            fprintf(doc,"%f;", matrixGetValue(mat, i, j));
        }
        fprintf(doc,"\n");
    }

    fprintf(doc, "< MatrixEnd >\n");

    fclose(doc);
}