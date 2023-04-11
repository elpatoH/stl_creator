#include "3d.h"
#include <stdlib.h>

int main(){
    Scene3D* perro = Scene3D_create();
    Triangle3DNode* caca = malloc(sizeof(Triangle3DNode));
    Triangle3DNode* caca2 = malloc(sizeof(Triangle3DNode));
    Triangle3DNode* caca3 = malloc(sizeof(Triangle3DNode));
    Triangle3DNode* caca4 = malloc(sizeof(Triangle3DNode));
    Triangle3DNode* caca5 = malloc(sizeof(Triangle3DNode));

    perro->root = caca;
    caca->next = caca2;
    caca2->next = caca3;
    caca3->next = caca4;
    caca4->next = caca5;
    perro->count = 5;

    Scene3D_destroy(perro);
}