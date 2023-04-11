#include "3d.h"
#include <stdlib.h>
#include <stdio.h>

Scene3D *Scene3D_create()
{
    Scene3D* new3d = malloc(sizeof(Scene3D));
    new3d->count = 0;
    new3d->root = NULL;
    return new3d;
}

/// @brief 
/// @param node 
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

void write_point(Coordinate3D point, FILE* file){
    fprintf(file, "      vertex %.2f %.2f %.2f\n", point.x, point.y, point.z);
    fflush(file);
}

void find_triangle(int target_shape, FILE* file, Triangle3DNode* node, int cur_shape){
    if (cur_shape == target_shape){
        write_point(node->triangle.a, file);
        write_point(node->triangle.b, file);
        write_point(node->triangle.c, file);
    }
    else{
        find_triangle(target_shape, file, node->next, cur_shape++);
    }
}

/*
should write every object in
the scene to an STL file file_name. It should write the objects to file in order they appear.

Use “scene” for the name of the solid for the stl file output. The coordinates of the triangle corners in
the output should be rounded to 5 decimal places.
*/
void Scene3D_write_stl_text(Scene3D *scene, char *file_name)
{
    //open file
    FILE* file = fopen(file_name, "w");
    if (file == NULL) {
        fprintf(stderr, "Opening file failed with code %d.\n", errno);
        return;
    }

    //start file
    fprintf(file, "solid scene\n");
    fflush(file);

    //write triangles
    int amount_shapes = scene->count;
    for (int target_shape = 0; target_shape < amount_shapes; target_shape++){ 
        fprintf(file, "  facet normal %.2f %.2f %.2f\n", 0.0, 0.0, 0.0);
        fprintf(file, "    outer loop\n");
        find_triangle(target_shape, file, scene->root, 0);
        fprintf(file, "    endloop\n");
        fprintf(file, "  endfacet\n");
        fflush(file);
    }

    //end file
    fprintf(file, "endsolid scene\n");
    fflush(file);
    fclose(file);
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
