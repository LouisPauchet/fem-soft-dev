/**
 * @file ListStruct.c
 * @author Louis Pauchet (louis.pauchet@insa-rouen.fr)
 * @brief Développement des fonctions permettant d'utiliser le type de liste chainées.
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef dList
#include "../../include/List.h"
#endif

#include <stddef.h>
#include <string.h>
#include <stdlib.h>


/**
 * @brief Fonction permettant d'alloue la mémoire d'une maillon de liste.
 * 
 * @return list Renvoie un pointeur de type list sur l'espace mémoire alloué.
 */


list listAlloc() {
    list workList = (list) malloc(sizeof(listNode));
    return workList;
}


/**
 * @brief Fonction permettant d'initialiser une nouvelle liste vide.
 * 
 * @return list Renvoie un élément de type pointeur sur un élément de liste.
 */

list listEmpty() {
    return NULL;
}


list listNew (list node) {
    node = (list) listAlloc();
    listSetNext(node, listEmpty());
    listSetPrec(node, listEmpty());
}


/**
 * @brief Fonction permettant de savoir si une liste est vide ou pas.
 * 
 * @param node 
 * @return list 
 */

list listIsEmpty(list node) {
    return (BOOLEAN) (node == NULL);
}

/**
 * @brief Fonction permettant d'obtenir le maillon suivant.
 * 
 * @param node Maillon de départ
 * @return list Maillon précédant.
 */

list listGetNext(list node) {
    return (list) node->next;
}

/**
 * @brief Fonction permettant d'obtenir le maillon précédent.
 * 
 * @param node Maillon d'entré
 * @return list Maillon suivant.
 */

list listGetPrec(list node) {
    return (list) node->previous;

}


/**
 * @brief Fonction permettant de définir le maillon suivnat dans une liste chainée.
 * 
 * @param node Maillon à modifier.
 * @param next Maillon à définir comme suivant.
 * @return list 
 */

list listSetNext(list node, list next) {
    node->next = (list) next;
    return node;
}

/**
 * @brief Fonction permettant de définie le précédent dans une liste chainée
 * 
 * @param node Maillon de liste à modifier.
 * @param prec Maillon à définie comme précédent.
 * @return list Renvoie un pointeur sur le maillon modifié.
 */

list listSetPrec(list node, list prec) {
    node->previous = (list) prec;
    return node;
}


/**
 * @brief Fonction permettant d'ajouter un élément en tête de liste.
 * 
 * @param WorkList List a laquelle ajouter le maillon
 * @param elementToAdd Element à ajouter au maillon
 * @return list 
 */

list listAddBegin(list WorkList, void* elementToAdd) {
    if (listIsEmpty(listGetPrec(WorkList))) {
        list newnode = listAlloc();
        listSetPrec(newnode, listEmpty());
        listSetNext(newnode, WorkList);
        listSetElement(newnode, elementToAdd);

        listSetPrec(WorkList, newnode);

        return newnode;

    }

    else {
        listAddBegin(listGetPrec(WorkList), elementToAdd);
    }


}

/**
 * @brief Fonction permettant d'obtenir le pointeur sur l'élément stoqué dans le maillon de liste
 * 
 * @param node Maillon où l'on cherche à obtenir l'élément
 * @return void* Pointeur sur l'élément.
 */

void* listGetElement(list node) {
    return node->element;
}

/**
 * @brief Fonction permettant de définir l'élément stocké dans le maillon de chaine.
 * 
 * @param node Maillon de chaine
 * @param elem Pointeur sur l'élément.
 * @return list 
 */

list listSetElement(list node, void* elem) {
    node->element = elem;
    return node;
}


/**
 * @brief Fonction permettant de rechercher un maillon de la liste en fonction d'un attribue du type recherché.
 * 
 * @param workList Liste de travail 
 * @param pf Fonction renvoyant l'attribut
 * @param Id Attribut à comparer.
 * @param Methode Mode de comparaison 's' pour une chaine de caractère, 'd' pour un entier
 * @return list Renvoie un pointeur sur l'élément. 
 */
/*
list listGetNodeBy(list workList, union IdType (*pf)(void*), char* Id, char Methode) {
    switch (Methode)
    {
    case 's' :
        if (strcmp((char*) pf(listGetElement(workList)), Id))
        {
            return workList;
        }

        else {
            listGetNodeBy(listGetPrec(workList), pf, Id, Methode);
            listGetNodeBy(listGetNext(workList), pf, Id, Methode);
        }
        

        break;

    case 'd' :

            if (((int) pf(listGetElement(workList))) == ((int) Id))
        {
            return workList;
        }

        else {
            listGetNodeBy(listGetPrec(workList), pf, Id, Methode);
            listGetNodeBy(listGetNext(workList), pf, Id, Methode);
        }
        

        break;
    
    default:
        break;
    }
}
*/


/**
 * @brief Fonction permettant de supprimer un maillon de la liste.
 * 
 * @param node Maillon à supprimer
 * @return list Renvoie un pointeur sur un maillon de la liste.
 */

list listDelNode(list node) {
    if (!(listIsEmpty(node))) {
        listSetNext(listGetPrec(node), listGetNext(node));
        listSetPrec(listGetNext(node), listGetPrec(node));
        free(node);
    }

    return node;
}

/**
 * @brief Fonction permettant de supprimer la list 
 * 
 * @param node List à supprimer 
 * @return list Renvoie un pointeur sur la list.
 */

list listDelList(list node) {

    while ( ! listIsEmpty(listGetPrec(node)))
    {
        listDelNode(listGetPrec(node));
    }
    
    while ( ! listIsEmpty(listGetNext(node)))
    {
        listDelNode(listGetNext(node));
    }

    listDelNode(node);
    node = listEmpty();
    

}