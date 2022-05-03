#include <stdio.h>


#include "../../include/List.h"

#include <stdlib.h>


int* test(void) {
    int* a = malloc(sizeof(int));
    *a = 2;
    return a;
}

void main() {
    /*int a,b,c,d,e;
    a= 1;
    b =2;
    c=3;
    d=4;
    e=5;

    list MaListe = listNew();

    listAddBegin(MaListe, &a);
    listAddBegin(MaListe, &b);

    printf("%d\n", *(int*) listGetElement(MaListe));
    printf("%d\n", *(int*) listGetElement(listGetNext(MaListe)));
    */

   printf("%d\n", *test());
    
}