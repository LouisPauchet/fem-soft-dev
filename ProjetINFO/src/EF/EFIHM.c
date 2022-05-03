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
#include <stdlib.h>
#include <string.h>

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


void PrintDataElem(double data) {
    if (data  <  0)
        {
            printf("(%1.3e)", data);
        }

    else
        {
            printf("(%1.4e)", data);
        }
}

void printLine(int n, char a) {
    for (int i = 0; i<n; i++) {
        printf("%c", a);
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
    list BacListOfNode = listGoFirst(ListOfNode);

    printf("Force        |"); //14 caractères

    ListOfNode = BacListOfNode;

    while ( ! listIsEmpty(ListOfNode)  )
    {
        PrintData(EFNodeGetStress(listGetElement(ListOfNode)));
        ListOfNode = listGetNext(ListOfNode);   
        
    }

    ListOfNode = BacListOfNode;
    printf("\nDéplacement  |"); //14 caractères

    while ( ! listIsEmpty(ListOfNode)  )
    {
        PrintData(EFNodeGetDisplacement(listGetElement(ListOfNode)));
        ListOfNode = listGetNext(ListOfNode);   
        
    }

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
        PrintDataElem(EFElementGetSpringRate(elem));
        for (int i = 0; i < ((15 * eccart - 14)/2); i++) printf("-");
        printf(">\n");        
    }

    else
    {
        for (int i = 0; i < ((15 * (eccart) - 15)/2); i++) printf("-");
        PrintDataElem(EFElementGetSpringRate(elem));
        for (int i = 0; i < ((15 * eccart - 15)/2 + 1); i++) printf("-");
        printf(">\n"); 
    }
    

    


}

/**
 * @brief Fonction permettant d'afficher un système mécanique.
 * 
 * @param ListOfEFNode Liste chainée des noeuds du système mécanique.
 * @param ListOfEFElement Liste chainée des elements du système mécanique.
 */

void EFDispSystem (list ListOfEFNode, list ListOfEFElement) {
    EFDispFirstLigne(listGetSize(ListOfEFNode));
    EFDispNodeData(ListOfEFNode);

    if (! listIsEmpty(ListOfEFElement)) ListOfEFElement = listGoFirst(ListOfEFElement);

    while (!listIsEmpty(ListOfEFElement))
    {
        EFDispElemUnit( (pEFElement) listGetElement(ListOfEFElement));
        ListOfEFElement = listGetNext(ListOfEFElement);

    }
       

}

/**
 * @brief Fonction permettant de demander à l'utilisateur de saisir un noeud
 * 
 * @param Noeud Pointeur sur le noeud devant être saisie.
 * @return pEFNode Pointeur sur le noeud dont les données ont été saisies
 */

pEFNode EFAskEFNode (list listOfEFNode) {
    int node_id = listGetSize(listOfEFNode);
    //int node_id = 1;
    double node_displacement = 0;

    printf("Création du noeud n°%d \nSaisir le déplacement du noeud : ", node_id);
    scanf("%lf", &node_displacement);


    return EFNodeNew(node_id, node_displacement, 0);

}

/**
 * @brief Fonction permettant de demander à l'utilisateur de saisir les données d'un noeud.
 * 
 * @param Element Pointeur sur l'élément dont l'utilisateur doit saisie les données.
 * @return pEFElement Pointeur sur l'élément dont les données ont été saisies
 */

pEFElement EFAskEFElement (list listOfEFElement) {
    int element_id = listGetSize(listOfEFElement);
    double elem_rate = 0;
    int node1 = 0;
    int node2 = 0;

    printf("Création de l'élément n°%2d \nSaisir la raideur de l'élément : ", element_id);
    scanf("%lf", &elem_rate);

    printf("Saisir le numéto du premier noeud d'attache : ");
    scanf("%d", &node1);
    printf("Saisir le numéro du deuxième noeud d'attache : ");
    scanf("%d", &node2);

    return EFElementNew(element_id, node1, node2, elem_rate);
}


/**
 * @brief Fonction permettant de créer un système mécanique
 * 
 * @param listOfNode Liste servant à stocker les noeuds crées
 * @param listOfElement Liste servant à stocker les éléments crées
 */

void EFCreateSystem (list *listOfNode, list *listOfElement) {

    char choice[4] = "n";

    do
    {   
        system("clear");

        *listOfNode = listAddEnd(*listOfNode, (pEFNode) EFAskEFNode(*listOfNode));

        printf("Avez-vous finis de saisir tous les noeuds ? (y / n) ");
        scanf("%s", choice);

    } while (! strcmp(&choice, "n"));

    strcpy(choice, "n");

    do
    {   
        system("clear");
        EFDispSystem(*listOfNode, *listOfElement);
        *listOfElement = listAddEnd(*listOfElement, (pEFNode) EFAskEFElement(*listOfElement));

        system("clear");
        EFDispSystem(*listOfNode, *listOfElement);

        printf("Avez-vous finis de saisir tous les elements ? (y / n) ");
        scanf("%s", choice);

    } while (! strcmp(&choice, "n"));


    system("clear");
    EFDispSystem(*listOfNode, *listOfElement);
    
}