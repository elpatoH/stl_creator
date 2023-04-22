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
    double increments[] = {15, 10, 5, 36, 30, 20, 90, 60, 45};

    for (int i = 0; i < 3; i += 1) {
        for (int j = 0; j < 3; j += 1) {
            Coordinate3D origin = (Coordinate3D){j*100, i*100, 0};
            Scene3D_add_sphere(s, origin, 45, increments[(i*3) + j]);
            printf("count: %ld\n", s->count);
        }
    }

    Scene3D_write_stl_binary(s, "sphere.stl");
    Scene3D_destroy(s);


}