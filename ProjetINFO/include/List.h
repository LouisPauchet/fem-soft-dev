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
 * @brief Structure d'un maillon de la liste doublement chainée générique.
 * 
 */

typedef struct {
    list previous; /**< @brief Champ contenant la liste précédante*/
    void* element; /**< @brief Pointeur générique sur l'élément stoqué dans la liste.*/
    list next; /**< @brief Champ contenant la liste suivante*/
} listNode;

/**
 * @brief Type de pointeur sur un maillon de liste (listNode)
 * 
 */

typedef listNode* list;



