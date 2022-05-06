/**
 * @file EF.h
 * @author Louis Pauchet (louis.pauchet@insa-rouen.fr)
 * @brief Fichier d'entête des fonctions publiques de la bibliothèque permettant de gérer des éléments finis.
 * @version 0.1
 * @date 2022-04-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef DList
#include "./List.h"
#define DList
#endif

#ifndef NodeLink
#define NodeLink 2
#endif

/**
 * @brief Définition d'un type de structure permettant de stocker des Noeuds d'éléments finis avec un numéro, un effort et un déplacement.
 * 
 */

typedef struct {
    int id; /**
     * @brief Entier permettant d'identifier le noeud
     * 
     */
    double stress; /**
     * @brief Double permettant de stocker les efforts appliqués au noeud
     * 
     */
    
    double displacement; /**
     * @brief Double permettant de stocker le déplacement du noeud
     * 
     */

} EFNode;

/**
 * @brief Structure permettant de stocker les éléments des éléments finis.
 * 
 */

typedef struct {
    int id; /**
     * @brief Numéro de l'élément
     * 
     */
    int node[NodeLink]; /**
     * @brief Tableau des noeuds connectés à l'éléments
     *
     * */
    double rate; /**
     *@brief Raideur de l'élément
     *
     */

} EFElement;

typedef EFNode* pEFNode;
typedef EFElement* pEFElement;

pEFElement EFElementFree(pEFElement);
pEFNode EFNodeFree(pEFNode);
void EFCreateSystem (list*, list*);
void EFDispSystem (list, list);
void EFEquating(list, list, list*);
void EFRestitution(list, list, list);