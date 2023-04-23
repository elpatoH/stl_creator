/*
name: Daniel Gil
class: csc352
desc: This class uses the 3d.c library to create one castle wall which can be used to create any amount
of walls.
*/
#include "3d.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    Scene3D* s = Scene3D_create();

    Coordinate3D origin = (Coordinate3D){-50, 0 ,0};
    Scene3D_add_sphere(s, origin, 45, 5);

    origin = (Coordinate3D){50, 0 ,0};
    Scene3D_add_sphere(s, origin, 45, 5);

    origin = (Coordinate3D){0, 0, 0};
    Scene3D_add_cuboid(s, origin, 20, 20, 20);

    Scene3D_write_stl_binary(s, "ion.stl");
    Scene3D_destroy(s);
}