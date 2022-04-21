#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0

typedef int BOOLEAN;


int main(void) {
    BOOLEAN* pTest;
    pTest = malloc(sizeof(BOOLEAN));
    printf("%d", *pTest);
    printf("%d", pTest);

}