/**
 * @file Liste.h
 * @author Louis Pauchet (louis.pauchet@insa-rouen.fr)
 * @brief Fichier d'entète des fonction publique de la bibliothèque permettant de créer des listes doublement chainées génériques.
 * @version 0.1
 * @date 2022-04-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef True
/**
 * @brief Définition des valeurs True = 1 pour augmenter la lisibilité du code
 */

#define True 1

/**
 * @brief Définition des valeurs False = 0 pour augmenter la lisibilité du code
 */

#define False 0

/**
 * @brief Définition d'un type BOOLEAN permettant d'utiliser True et False
 */

typedef int BOOLEAN;

#endif



/**
 * @brief Type de pointeur sur un maillon de liste (listNode)
 * 
 */

typedef struct listNode listNode;
typedef listNode* list;


/**
 * @brief Structure d'un maillon de la liste doublement chainée générique.
 * 
 */


struct listNode {
    listNode* previous; /**< @brief Champ contenant la liste précédante*/
    void* element; /**< @brief Pointeur générique sur l'élément stoqué dans la liste.*/
    listNode* next; /**< @brief Champ contenant la liste suivante*/
} ;

//typedef listNode* list;

#ifndef NameLength
/**
 * @brief Définition de la longueur des noms utilisables dans les matrices
 * 
 */
    #define NameLength 20
#endif

typedef void* (*FreeElement)(void*);
typedef void (*DispElement)(void*);

list listEmpty();
list listNew();
list listAddBegin(list, void*);
list listAddEnd(list, void*);
list listIsEmpty(list);
list listGetNext(list);
list listGetPrec(list);
list listSetNext(list, list);
list listSetPrec(list, list);
void* listGetElement(list);
list listSetElement(list, void*);

list listDelNode(list, FreeElement);
list listDelList(list, FreeElement);


int listGetSize(list);

list listGoFirst(list);

void listDoForList(list, DispElement);





