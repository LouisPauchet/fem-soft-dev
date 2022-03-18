#include <stdio.h>
#include <cstdlib>

struct Vecteur
{
    char name[20];
    double *Vec;
    int size;
};

int main() {
    int n = 3;
    
    Vecteur Vec1;
    Vecteur Vec2;
    Vec1.size = n;
    Vec2.size = n;
    Vec1.Vec = (double*)malloc(Vec1.size*sizeof(double));
    Vec2.Vec = (double*)malloc(Vec2.size*sizeof(double));

    printf("Saisir le nom du vecteur : ");
    scanf("%s", Vec1.name);

    for (int j=0; j<Vec1.size; j++){
        printf("Saisir la ligne n° %d %s : ", j, Vec1.name);
        scanf("%lf",&Vec1.Vec[j]);
    }

    printf("Saisir le nom du vecteur : ");
    scanf("%s", Vec2.name);

    for (int j=0; j<Vec2.size; j++){
       printf("Saisir la ligne n° %d %s : ", j, Vec2.name);
        scanf("%lf",&Vec2.Vec[j]);
    }

    printf("        %s     |   %s \n", Vec1.name, Vec2.name);
    for (int j=0; j<n; j++){
        printf("(%d)    %f  |   %f \n", j, Vec1.Vec[j], Vec2.Vec[j]);
    }

    double _PScalaire = 0;

    for (int i=0; i<n; i++) {
        _PScalaire += Vec1.Vec[i] * Vec2.Vec[i];
    }

    printf("Le produit scalaire entre %s et %s vaut %f \n", Vec1.name, Vec2.name, _PScalaire);

}