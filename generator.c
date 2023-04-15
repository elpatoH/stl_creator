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
    Scene3D* castle_wall = Scene3D_create();
    Coordinate3D origin;

    int index = 0;
    while (index < 5){
        origin = (Coordinate3D){0 + (index * 10), 0, 0};
        Scene3D_add_cuboid(castle_wall, origin, 10, 15, 20);

        origin = (Coordinate3D){0 + (index * 10), 0 + (5), 0 + 10};
        Scene3D_add_pyramid(castle_wall, origin, 5, 5, "up");

        if (index == 0){
            origin = (Coordinate3D){0 + (index * 10), 0 + (20), 0};
            Scene3D_add_cuboid(castle_wall, origin, 10, 5, 10);

            origin = (Coordinate3D){0 + (index * 10), 0 + (10), 0};
            Scene3D_add_cuboid(castle_wall, origin, 5, 20, 10);

            origin = (Coordinate3D){0 + (index * 10), 0 + (20), 0};
            Scene3D_add_pyramid(castle_wall, origin, 10, 20, "forward");
        }
        else if (index == 2){
            origin = (Coordinate3D){0 + (index * 10), 0 - (2), 0 + (10)};
            Scene3D_add_cuboid(castle_wall, origin, 5, 11, 3);
        }
        else if (index == 4){
            origin = (Coordinate3D){0 + (index * 10), 0 + (20), 0};
            Scene3D_add_cuboid(castle_wall, origin, 10, 5, 10);

            origin = (Coordinate3D){0 + (index * 10), 0 + (10), 0};
            Scene3D_add_cuboid(castle_wall, origin, 5, 20, 10);
            
            origin = (Coordinate3D){0 + (index * 10), 0 + (20), 0};
            Scene3D_add_pyramid(castle_wall, origin, 10, 20, "forward");
        }
        index++;
    }

    Scene3D_write_stl_text(castle_wall, "output.stl");
    Scene3D_destroy(castle_wall);
}