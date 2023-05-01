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
    int levels = 1;
    for (int i = 1; i >= 0; i--) {
        for (int j = 0; j < 3; j++) {
            Coordinate3D origin = (Coordinate3D){j*100, i*100, 0};
            Scene3D_add_fractal(s, origin, 50, levels);
            printf("count for level %d: %ld\n", levels, s->count);
            levels += 1;
        }
    }
    Scene3D_write_stl_binary(s, "fractal.stl");
    Scene3D_destroy(s);

}