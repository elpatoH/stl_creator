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
    Scene3D_write_stl_text(star, "output.stl");

    Scene3D_destroy(star);
}