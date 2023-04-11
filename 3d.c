#include "3d.h"
#include <stdlib.h>

Scene3D *Scene3D_create()
{
    Scene3D* new3d = malloc(sizeof(Scene3D));
    new3d->count = 0;
    new3d->root = NULL;
    return new3d;
}

void destroy(Triangle3DNode* node){
    if (node == NULL){
        return;
    }
    else{
        destroy(node->next);
        free(node);
    }
}

void Scene3D_destroy(Scene3D *scene)
{
    if (scene->count == 0){
        free(scene);
    }
    else{
        destroy(scene->root);
        free(scene);
    }
    
}

/*
should write every object in
the scene to an STL file with the name file_name. It should write the objects / triangles to the file in the order
that they appear in the scene object. After you write a file, you can test if it works by opening it in an STL file
viewer. Use “scene” for the name of the solid for the stl file output. The coordinates of the triangle corners in
the output should be rounded to 5 decimal places.
*/
void Scene3D_write_stl_text(Scene3D *scene, char *file_name)
{
}

void Scene3D_add_pyramid(Scene3D *scene, Coordinate3D origin, double width, double height, char *orientation)
{
}

void Scene3D_add_cuboid(Scene3D *scene, Coordinate3D origin, double width, double height, double depth)
{
}

void Scene3D_add_quadrilateral(Scene3D *scene, Coordinate3D a, Coordinate3D b, Coordinate3D c, Coordinate3D d)
{
}

void Scene3D_write_stl_binary(Scene3D *scene, char *file_name)
{
}

void Scene3D_add_sphere(Scene3D *scene, Coordinate3D origin, double radius, double increment)
{
}

void Scene3D_add_fractal(Scene3D *scene, Coordinate3D origin, double size, int levels)
{
}
