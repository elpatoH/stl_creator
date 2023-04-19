/*
name: Daniel Gil
class: csc352
desc: This class uses the 3d.c library to create one castle wall which can be used to create any amount
of walls.
*/
#include "3d.h"
#include <stdlib.h>

int main(){
    //star
    Scene3D* star = Scene3D_create();
    
    char* directions[] = {"up", "down", "left", "right", "forward", "backward"};
    Coordinate3D origin = (Coordinate3D){100, 100, 100};
    for (int i = 0; i <= 5; i ++) {
        Scene3D_add_pyramid(star, origin, 20, 30, directions[i]);
    }

    Scene3D_add_sphere(star, origin, 5, 1);

    //Scene3D_write_stl_text(star, "output.stl");
    //Scene3D_write_stl_binary(star, "chetos.stl");
    Scene3D_destroy(star);
}