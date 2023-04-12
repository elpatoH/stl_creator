#include "3d.h"
#include <stdlib.h>

int main(){
    Scene3D* perro = Scene3D_create();

    Coordinate3D coordinate;
    coordinate = (Coordinate3D){0, 0, 0};

    Scene3D_add_pyramid(perro, coordinate, 10, 10, "up");

    // Triangle3DNode* caca = malloc(sizeof(Triangle3DNode));

    // Coordinate3D coordinate;

    // // first
    // coordinate = (Coordinate3D){-25, 0, -25};
    // caca->triangle.a = coordinate;
    // coordinate = (Coordinate3D){25, 0, -25};
    // caca->triangle.b = coordinate;
    // coordinate = (Coordinate3D){0, 50, 0};
    // caca->triangle.c = coordinate;

    // Triangle3DNode* caca2 = malloc(sizeof(Triangle3DNode));

    // // second
    // coordinate = (Coordinate3D){-25, 0, -25};
    // caca2->triangle.a = coordinate;
    // coordinate = (Coordinate3D){-25, 0, 25};
    // caca2->triangle.b = coordinate;
    // coordinate = (Coordinate3D){0, 50, 0};
    // caca2->triangle.c = coordinate;

    // Triangle3DNode* caca3 = malloc(sizeof(Triangle3DNode));

    // // third
    // coordinate = (Coordinate3D){25, 0, 25};
    // caca3->triangle.a = coordinate;
    // coordinate = (Coordinate3D){-25, 0, 25};
    // caca3->triangle.b = coordinate;
    // coordinate = (Coordinate3D){0, 50, 0};
    // caca3->triangle.c = coordinate;

    // Triangle3DNode* caca4 = malloc(sizeof(Triangle3DNode));

    // //fourth
    // coordinate = (Coordinate3D){25, 0, 25};
    // caca4->triangle.a = coordinate;
    // coordinate = (Coordinate3D){25, 0, -25};
    // caca4->triangle.b = coordinate;
    // coordinate = (Coordinate3D){0, 50, 0};
    // caca4->triangle.c = coordinate;

    // perro->root = caca;
    // perro->count = 1;

    // caca->next = caca2;
    // perro->count = 2;

    // caca2->next = caca3;
    // perro->count = 3;

    // caca3->next = caca4;
    // perro->count = 4;

    // caca4->next = NULL;

    Scene3D_write_stl_text(perro, "ahi.stl");

    Scene3D_destroy(perro);
}