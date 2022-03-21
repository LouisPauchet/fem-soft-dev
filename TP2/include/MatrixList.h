#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Matrix.h"

#define firstIndex 0

/*##################*/
/*Définition du type*/
/*##################*/

struct MatrixList
{
    struct MatrixList *prec;
    struct Matrix *mat;
    struct MatrixList *next;
};

/*########################*/
/*Signatures des fonctions*/
/*########################*/

/*Getteurs*/

struct Matrix* getMatrix(struct MatrixList*); //Permet un pointeur sur la matrice d'un maillon la matrice d'un maillon
struct MatrixList* getNext(struct MatrixList*); //Permet d'obtenir un pointeur sur le maillon suivant
struct MatrixList* getPrec(struct MatrixList*); //Permet d'obtenir un pointeur sur le maillon précédent
char* getName (struct MatrixList*); //Obtenir le nom de la matrice du maillon
int getNodeIndex(struct MatrixList*); //Permet d'obtenir l'indice de l'élément
struct MatrixList* getNodeByIndex(struct MatrixList*, int); //Permet d'onbtenir le maillon à partir d'un décalage
struct MatrixList* getNodeByName(struct MatrixList*, char*); //Permet d'onbtenir le maillon à partir de son nom

/*Setteur*/

void setMemory(struct MatrixList*); //Permet d'allouer la mémoire d'un maillon de la chaine
void setMatrix(struct MatrixList*, struct Matrix*); //Permet d'ajouter une matrice à un maillon
void setNext(struct MatrixList*, struct MatrixList*); //Permet d'ajouter l'élément suivant à un maillon
void setPrec(struct MatrixList*, struct MatrixList*); //Permet d'ajouter l'élément précédent à un maillon
void setEnd(struct MatrixList*); //Permet de définir le maillon comme le dernier
void setBegin(struct MatrixList*); //Permet de définir le maillon comme le premier

/*Opérateur de type*/

void newNodeEnd(struct MatrixList*); //permet de créer un noeud à la fin de la liste
void newNodeBegin(struct MatrixList*); //permet de créer un noued au début de la liste
void newNodeIndex(struct MatrixList*, int); //permet de créer un noeud dans la liste

void delNodeEnd(struct MatrixList*); //permet de supprimer le dernier noeud
void delNodeBegin(struct MatrixList*); //permet de supprimer le premier noeud de la liste
void delNodeIndex(struct MatrixList*); //permet de supprimer un noeud dans la liste


/*####################*/
/*Codage des fonctions*/
/*####################*/

/*Permet d'obtenir une pointeur sur la matrice d'un noeud*/

struct Matrix* getMatrix(struct MatrixList* node) {
    return node->mat;
}

/*Obtenir un pointeur sur le maillon suivant*/

struct MatrixList* getNext(struct MatrixList* node) {
    return node->next;
}

/*Obtenir un pointeur sur le maillon précédent*/

struct MatrixList* getPrec(struct MatrixList* node) {
    return node->prec;
}

/*Obtient le nom de la matrice du noeud*/

char* getName (struct MatrixList* node) {
    return getName(getMatrix(node));
}

/*Obtenir l'indice de l'élément*/

int getNodeIndex(struct MatrixList* node) {
    if (getPrec(node) == NULL) {
        return (int) firstIndex;
    }

    else {
        return (getNodeIndex(getPrec(node)) + 1);
    }
}

/*Obtenir un élément par son indice */

struct MatrixList* getNodeByIndex(struct MatrixList* node, int index) {
    if (getNodeIndex(node) == index) {
        return node;
    }

    else {
        if (getNodeIndex(node) < index) {
            return getNodeByIndex(getNext(node), index + 1 );
        }

        else {
            return getNodeByIndex(getPrec(node), index - 1 );
        }
    }
}

/* Permet d'obtenir un élément par son nom*/

struct MatrixList* getNodeByName(struct MatrixList* node, char* name) {
    if (strcmp(name, getName(node)) == 0) {
        return node;
    }

    else {
        node = getNodeByIndex(node, 0);
        while (getNext(node) == NULL) {
            if (strcmp(name, getName(node)) == 0) {
                return node;
            }
        }
    }
}

/*Setteur*/


/*On alloue un espace mémoire à un maillon*/

void setMemory(struct MatrixList* node) {
    node = malloc(sizeof(struct MatrixList));
}

/* On ajout une matrice à un maillon */

void setMatrix(struct MatrixList* node, struct Matrix* mat) {
    node->mat = mat;
}

/* On ajoute l'élément suivant à un maillon */

void setNext(struct MatrixList* node, struct MatrixList* node_next){
    node->next = node_next;
}

/* On ajoute l'élément précédent à un maillon */

void setPrec(struct MatrixList* node, struct MatrixList* node_prec) {
    node->prec = node_prec;
}

/* On définie le maillon comme le dernier */

void setEnd(struct MatrixList* node) {
    node->next = NULL;
}

/* On définie le maillon comme le premier */

void setBegin(struct MatrixList* node) {
    node->prec = NULL;
}


/*Opérateur de type*/

/*Création d'un noeud à la fin de la liste*/

void newNodeEnd(struct MatrixList*) {

}
void newNodeBegin(struct MatrixList*); //permet de créer un noued au début de la liste
void newNodeIndex(struct MatrixList*, int); //permet de créer un noeud dans la liste

void delNodeEnd(struct MatrixList*); //permet de supprimer le dernier noeud
void delNodeBegin(struct MatrixList*); //permet de supprimer le premier noeud de la liste
void delNodeIndex(struct MatrixList*); //permet de supprimer un noeud dans la liste
