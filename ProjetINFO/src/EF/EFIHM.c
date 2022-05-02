/**
 * @file EFIHM.c
 * @author Louis Pauchet (louis.pauchet@insa-rouen.fr)
 * @brief 
 * @version 0.1
 * @date 2022-04-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../../include/privateEF.h"

#ifndef DEf
#include "../../include/privateEF.h"
#define DEf
#endif

#ifndef DList
#include "../../include/List.h"
#define DList
#endif

#include <stdio.h>

void PrintData(double data) {
    if (data  <  0)
        {
            printf(" (%1.3e) |", data);
        }

    else
        {
            printf(" (%1.4e) |", data);
        }
}

void printLine(int n, char a) {
    for (int i = 0; i<n; i++) {
        printf("%s", a);
    }
    printf ("\n");
}

void EFDispFirstLigne(int NbNode) {
    //Affichage de la première ligne avec la liste des noeuds.
    printf("Noeud        |"); // 14 caractère
    for (int i = 0; i<NbNode; i++) {
        printf("     (%2d)     |", i); // 15 caractère
    }
    printf("\n");

    printLine((14 + NbNode * 15), '-'); // On affiche une séparation.
}

void EFDispNodeData( list ListOfNode) {
    list BacListOfNode = ListOfNode;

    printf("Force        |"); //14 caractères

    do
    {
        PrintData(EFNodeGetStress(listGetElement(ListOfNode)));        
        
    } while ( ! listIsEmpty(listGetNext(ListOfNode))  );

    ListOfNode = BacListOfNode;
    printf("\nDéplacement  |"); //14 caractères

        do
    {
        PrintData(EFNodeGetDisplacement(listGetElement(ListOfNode)));
        
        
    } while ( ! listIsEmpty(listGetNext(ListOfNode))  );

    printf("\n");

    printLine((14 + listGetSize(BacListOfNode) * 15), '-');
        
}

void EFDispElemUnit( pEFElement elem) {
    int a, b, eccart;
    printf("Element (%2d) |", EFElementGetId(elem)); //14 caractère

    if (EFElementGetNode(elem, 1) < EFElementGetNode(elem, 2)) {
        a = EFElementGetNode(elem, 1);
        b = EFElementGetNode(elem, 2);
    }

    else
    {
        b = EFElementGetNode(elem, 1);
        a = EFElementGetNode(elem, 2);
    }

    for (int i = 0; i < a; i++) {
        printf("               "); //15 espaces
    }

    printf("       <"); //7 espaces

    eccart = b - a;

    if ((eccart % 2) == 0) {
        for (int i = 0; i < ((15 * eccart - 14)/2); i++) printf("-");
        PrintData(EFElementGetSpringRate(elem));
        for (int i = 0; i < ((15 * eccart - 14)/2); i++) printf("-");
        printf(">\n");        
    }

    else
    {
        for (int i = 0; i < ((15 * (eccart) - 15)/2); i++) printf("-");
        PrintData(EFElementGetSpringRate(elem));
        for (int i = 0; i < ((15 * eccart - 15)/2 + 1); i++) printf("-");
        printf(">\n"); 
    }
    

    


}

/**
 * @brief Fonction permettant d'afficher un système mécanique.
 * 
 * @param ListOfEFNode 
 * @param ListOfEFElement 
 */

void EFDispSystem (list ListOfEFNode, list ListOfEFElement) {
    EFDispFirstLigne(listGetSize(ListOfEFNode));
    EFDispNodeData(ListOfEFNode);

    do
    {
        EFDispElemUnit( (pEFElement) listGetElement(ListOfEFNode));
        ListOfEFNode = listGetNext(ListOfEFNode);
    } while (!listIsEmpty(listGetNext(ListOfEFNode)));
    
    

}

/**
 * @brief Fonction permettant de demander à l'utilisateur de saisir un noeud
 * 
 * @param Noeud Pointeur sur le noeud devant être saisie.
 * @return pEFNode Pointeur sur le noeud dont les données ont été saisies
 */

pEFNode EFAskEFNode (pEFNode Noeud) {

}

/**
 * @brief Fonction permettant de demander à l'utilisateur de saisir les données d'un noeud.
 * 
 * @param Element Pointeur sur l'élément dont l'utilisateur doit saisie les données.
 * @return pEFElement Pointeur sur l'élément dont les données ont été saisies
 */

pEFElement EFAskElement (pEFElement Element) {

}