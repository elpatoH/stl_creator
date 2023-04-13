#include "3d.h"
#include <stdlib.h>

int main(){
    //perro
    Scene3D* perro = Scene3D_create();

    Coordinate3D coordinate;
    coordinate = (Coordinate3D){0, 0, 0};

    Scene3D_add_pyramid(perro, coordinate, 10, 10, "down");

    //perro2
    Scene3D* perro2 = Scene3D_create();

    Coordinate3D coordinate2;
    coordinate2 = (Coordinate3D){0, 0, 0};

    Scene3D_add_pyramid(perro2, coordinate2, 10, 10, "up");

    //perro3
    Scene3D* perro3 = Scene3D_create();

    Coordinate3D coordinate3;
    coordinate3 = (Coordinate3D){0, 0, 0};

    Scene3D_add_pyramid(perro3, coordinate3, 10, 10, "right");

    //perro4
    Scene3D* perro4 = Scene3D_create();

    Coordinate3D coordinate4;
    coordinate4 = (Coordinate3D){0, 0, 0};

    Scene3D_add_pyramid(perro4, coordinate4, 10, 10, "left");

    //perro5
    Scene3D* perro5 = Scene3D_create();

    Coordinate3D coordinate5;
    coordinate5 = (Coordinate3D){0, 0, 0};

    Scene3D_add_pyramid(perro5, coordinate5, 10, 10, "backward");

    //perro6
    Scene3D* perro6 = Scene3D_create();

    Coordinate3D coordinate6;
    coordinate6 = (Coordinate3D){0, 0, 0};

    Scene3D_add_pyramid(perro6, coordinate6, 10, 10, "forward");

    //star
    Scene3D* star = Scene3D_create();
    char* directions[] = {"up", "down", "left", "right", "forward", "backward"};
    Coordinate3D origin = (Coordinate3D){100, 100, 100};
    for (int i = 0; i <= 5; i ++) {
        Scene3D_add_pyramid(star, origin, 20, 30, directions[i]);
    }
    Scene3D_write_stl_text(star, "star.stl");

    //write
    Scene3D_write_stl_text(perro, "ahi.stl");
    Scene3D_write_stl_text(perro2, "ahi2.stl");
    Scene3D_write_stl_text(perro3, "ahi3.stl");
    Scene3D_write_stl_text(perro4, "ahi4.stl");
    Scene3D_write_stl_text(perro5, "ahi5.stl");
    Scene3D_write_stl_text(perro6, "ahi6.stl"); 
    Scene3D_write_stl_text(star, "star.stl"); 

    Scene3D_destroy(perro);
}