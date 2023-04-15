#include "3d.h"
#include <stdlib.h>

int main(){
    //star
    Scene3D* something = Scene3D_create();

    //char* directions[] = {"up", "down", "left", "right", "forward", "backward"};
    Coordinate3D origin = (Coordinate3D){0, 0, 0};

    Scene3D_add_cuboid(something, origin, 10, 15,20);

    Scene3D_write_stl_text(something, "output.stl");
    Scene3D_destroy(something);
}