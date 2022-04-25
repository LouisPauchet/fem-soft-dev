#include "../../include/EF.h"

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Fonction permettant d'obtenir le numéro d'un élément
 * 
 * @param Element Poiteur sur un élément
 * @return int Renvoie un entier correspondant au numéro de l'élément.
 */

int EFElementGetId(pEFElement Element) {
    return Element->id;
}

/**
 * @brief Fonction permettant de définir le numéro d'un élément
 * 
 * @param Element Pointeur sur un élément
 * @param id Numéro de l'élément
 * @return pEFElement Pointeur sur l'élément modifié.
 */

pEFElement EFElementSetId(pEFElement Element, int id) {
    Element->id = id;
    return Element;
}

/**
 * @brief Fonction permettant d'obtenir le numéro des noeuds attachés à un élément
 * 
 * @param Element Pointeur sur l'élément voulue
 * @param nodePosition Numéro d'attache du noeud.
 * @return int Renvoie le numéro du noeud voulue. En cas d'érreur sur nodePosition, renvoie NULL.
 */

int EFElementGetNode (pEFElement Element, int nodePosition) {
    switch (nodePosition)
    {
    case 1:
        return (Element->node[1]);
        break;

    case 2:
        return (Element->node[2]);
        break;
    
    default:
        fprintf(stderr, "EFElementGetNode - Index is out of node list !");
        return(NULL);
        break;
    }
}

/**
 * @brief Fonction permettant de définir un noeud attaché à un élément.
 * 
 * @param Element Pointeur sur l'élément à modifier
 * @param nodePosition Position du noeud à ajouter
 * @param nodeId Numéro du noeud à lier
 * @return pEFElement Renvoie un pointeur sur l'élément qui a été modifié sauf en cas d'erreur où le retour sera NULL.
 */

pEFElement EFElementSetNode (pEFElement Element, int nodePosition, int nodeId) {
    switch (nodePosition)
    {
    case (int) 1:
        Element->node[1] = nodeId;
        return Element;
        break;

    case (int) 2:
        Element->node[2] = nodeId;
        return Element;
        break;
    
    default:
        fprintf(stderr, "EFElementSetNode - Index is out of node list !");
        return(NULL);
        break;
    }
}

/**
 * @brief Fonction permettant d'obtenir la raideur d'un élément
 * 
 * @param Element Pointeur sur un élément
 * @return double Renvoie la raideur du ressort associé à l'élément.
 */

double EFElementGetSpringRate(pEFElement Element) {
    return Element->rate;
}

/**
 * @brief Fonction permettant de modifier la raideur du ressort associé à un élément
 *  
 * @param Element Pointeur sur l'élément à modifier
 * @param rate Raideur du ressort à associer
 * @return pEFElement Renvoie un pointeur sur l'élément modifier
 */

pEFElement EFElementSetSpringRate(pEFElement Element, double rate) {
    Element->rate = rate;
    return Element;
}