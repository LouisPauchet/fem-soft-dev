/**
 * @file EFIHM.c
 * @author Louis Pauchet (louis.pauchet@insa-rouen.fr)
 * @brief Fichier contenant la définission des fonctions permettant à l'utilisateur d'intéragir avec les types @ref EFElement, @ref EFNode, @ref pEFElement et @ref pEFNode.
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

BOOLEAN stringIsEmpty (char* string) {
    return  (int)( ! (strlen(string) > 1));
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

void EFDispSystem (EFMecanicalSystem System) {
    EFDispFirstLigne(listGetSize(System.ListOfNode));
    EFDispNodeData(System.ListOfNode);

    if (! listIsEmpty(System.ListOfElement)) System.ListOfElement = listGoFirst(System.ListOfElement);

    while (!listIsEmpty(System.ListOfElement))
    {
        EFDispElemUnit( (pEFElement) listGetElement(System.ListOfElement));
        System.ListOfElement = listGetNext(System.ListOfElement);

    }
       

}

/**
 * @brief Fonction permettant de demander à l'utilisateur de saisir les éléments du système.
 * 
 * On ne retourne rien car on modifie directement le system via le passage en paramètre d'un pointeur sur une structure @ref EFMecanicalSystem .
 * 
 * @param System Pointeur sur le system de travail.
 */

void EFAskEFNodes (EFMecanicalSystem* System) {

    list ListOfNode = System->ListOfNode;
    list ListOfNodeR = System->ListOfNodeR;
    list ListOfNodeF = System->ListOfNodeF;

    pEFNode pNewNode = NULL;

    char choice[4] = "n";
    char buffer[20] = "\0";



    do
    {   
        system("clear");

            int node_id = listGetSize(ListOfNode); //définition des varaibles
            double node_stress = 0, node_displacement = 0;

            printf("Création du noeud n°%d \nSaisir le déplacement du noeud ou Entrer pour saisir un effort : ", node_id);

            getchar();

            fgets(buffer, 20, stdin); //récupération de la saisie de l'utilisateur

            printf("\n");
            if ( ! stringIsEmpty(buffer)) { //si la liste n'est pas vide = un déplacement a été saisie.
                node_displacement = (double) strtod(buffer, NULL);
                pNewNode = EFNodeNew (node_id, node_displacement, (double) 0.); //On crée le noeud et on l'ajoute le noeud à la liste des noeuds sans déplacement
                ListOfNodeR = listAddEnd(ListOfNodeR, pNewNode);
            }

            else {
                system("clear");
                printf("Création du noeud n°%d \nPas de déplacement saisie\nSaisir l'effort du noeud : ", node_id);
                scanf("%lf", &node_stress);
                pNewNode = EFNodeNew (node_id, (double) 0., node_stress);
                ListOfNodeF = listAddEnd(ListOfNodeF, pNewNode);
            }

        ListOfNode = listAddEnd(ListOfNode, (pEFNode) pNewNode);

        printf("Avez-vous finis de saisir tous les noeuds ? (y / n) ");
        scanf("%s", choice);

    } while (! strcmp(&choice, "n"));


    System->ListOfNode = ListOfNode;
    System->ListOfNodeR = ListOfNodeR;
    System->ListOfNodeF = ListOfNodeF;

    return 0;

}

/**
 * @brief Fonction permettant de demander à l'utilisateur de saisir les données d'un noeud.
 * 
 * @param Element Pointeur sur l'élément dont l'utilisateur doit saisie les données.
 * @return pEFElement Pointeur sur l'élément dont les données ont été saisies
 */

pEFElement EFAskEFElement (list listOfEFElement, int systemsize) {
    int element_id = listGetSize(listOfEFElement);
    double elem_rate = 0;
    int node1 = 0;
    int node2 = 0;

    printf("Création de l'élément n°%2d \nSaisir la raideur de l'élément : ", element_id);
    scanf("%lf", &elem_rate);

    printf("Saisir le numéto du premier noeud d'attache : ");
    scanf("%d", &node1);
    while ((node1 < 0) || (node1 > systemsize))
    {
        printf("ERREUR\nSaisir le numéto du premier noeud d'attache compris entre 0 et %d : ", systemsize - 1);
        scanf("%d", &node1);
    }
    

    printf("Saisir le numéro du deuxième noeud d'attache : ");
    scanf("%d", &node2);
    while ((node2 < 0) || (node2 > systemsize) || (node2 == node1))
    {
        printf("ERREUR\nSaisir le numéto du deuxième noeud d'attache compris entre 0 et %d et différent du noeud %d : ", systemsize, node1);
        scanf("%d", &node2);
    }

    return EFElementNew(element_id, node1, node2, elem_rate);
}


/**
 * @brief Fonction permettant de créer un système mécanique
 * 
 * Dans un premier temps on demande à l'utilisateur de saisir la liste des noeuds puis des élements.
 * Une fois tous les noeuds saisies, on affiche le system et on affiche les éléments au fur et à mesure.
 * 
 * @param System System mécanique de travail de type @ref EFMecanicalSystem
 */

void EFCreateSystem (EFMecanicalSystem* System) {

    char choice[4] = "n";

    EFAskEFNodes(System);

    int systemsize = listGetSize(System->ListOfNode);
    do
    {   
        system("clear");
        EFDispSystem(*System);
        System->ListOfElement = listAddEnd(System->ListOfElement, (pEFNode) EFAskEFElement(System->ListOfElement, systemsize));

        system("clear");
        EFDispSystem(*System);

        printf("Avez-vous finis de saisir tous les elements ? (y / n) ");
        scanf("%s", choice);

    } while (! strcmp(&choice, "n"));


    system("clear");
    EFDispSystem(*System);
    
}