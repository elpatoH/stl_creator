#include "3d.h"
#include <stdlib.h>

int main(){
    Scene3D* perro = Scene3D_create();
    Triangle3DNode* caca = malloc(sizeof(Triangle3DNode));

    Coordinate3D a;
    a.x = 1.0;
    a.y = 1.0;
    a.z = 1.0;

    Coordinate3D b;
    b.x = 2.0;
    b.y = 2.0;
    b.z = 2.0;

    Coordinate3D c;
    c.x = 3.0;
    c.y = 3.0;
    c.z = 3.0;

    caca->triangle.a = a;
    caca->triangle.b = b;
    caca->triangle.c = c;
    caca->next = NULL;

    perro->root = caca;
    perro->count = 1;

    Scene3D_write_stl_text(perro, "ahi.stl");

    Scene3D_destroy(perro);
}