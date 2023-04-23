/*
name: Daniel Gil
class: csc352
desc: This class contains the code for the header file 3d. This is a library that creates stl
files by using various methods
*/
#include "3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <math.h>

Scene3D *Scene3D_create()
{
    Scene3D* new3d = malloc(sizeof(Scene3D));
    new3d->count = 0;
    new3d->root = NULL;
    return new3d;
}

/// @brief helper function for scene3d_destroy
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

/// @brief writes a x,y,z into the file
/// @param point 
/// @param file 
void write_point(Coordinate3D point, FILE* file){
    fprintf(file, "      vertex %.5f %.5f %.5f\n", point.x, point.y, point.z);
    fflush(file);
}

/// @brief recursively finds and writes the triangle into a file
/// @param target_shape 
/// @param file 
/// @param node 
/// @param cur_shape 
void find_triangle(int target_shape, FILE* file, Triangle3DNode* node, int cur_shape){
    if (cur_shape == target_shape){
        write_point(node->triangle.a, file);
        write_point(node->triangle.b, file);
        write_point(node->triangle.c, file);
    }
    else{
        find_triangle(target_shape, file, node->next, ++cur_shape);
    }
}

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
        fprintf(file, "  facet normal %.1f %.1f %.1f\n", 0.0, 0.0, 0.0);
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

/// @brief allocates and initialices a new triangle3dnode object
/// @param triangle 
/// @return 
Triangle3DNode* get_triangle(Triangle3D triangle){
    Triangle3DNode* node = malloc(sizeof(Triangle3DNode));
    node->triangle.a.x = triangle.a.x;
    node->triangle.a.y = triangle.a.y;
    node->triangle.a.z = triangle.a.z;

    node->triangle.b.x = triangle.b.x;
    node->triangle.b.y = triangle.b.y;
    node->triangle.b.z = triangle.b.z;

    node->triangle.c.x = triangle.c.x;
    node->triangle.c.y = triangle.c.y;
    node->triangle.c.z = triangle.c.z;

    node->next = NULL;

    return node;
}

/// @brief adds triangle to a scene
/// @param scene 
/// @param triangle 
void Scene3D_add_triangle(Scene3D *scene, Triangle3D triangle){
    if (scene->root == NULL){
        scene->root = get_triangle(triangle);
        scene->count++;
    }
    else{
        Triangle3DNode* cur = scene->root;
        while (cur->next != NULL){
            cur = cur->next;
        }
        cur->next = get_triangle(triangle);
        scene->count++;

    }
    
}

void Scene3D_add_pyramid(Scene3D *scene, Coordinate3D origin, double width, double height, char *orientation)
{
    // Calculate half of the width and height
    double halfWidth = width / 2.0;

    if (strcmp(orientation, "forward") == 0){
        //forward/backward refers to +/- on the Y axis
        Coordinate3D cordenadaA;
        cordenadaA = (Coordinate3D){(origin.x + halfWidth), (origin.y), (origin.z + halfWidth)};

        Coordinate3D cordenadaB;
        cordenadaB = (Coordinate3D){(origin.x - halfWidth), (origin.y), (origin.z + halfWidth)};

        Coordinate3D cordenadaC;
        cordenadaC = (Coordinate3D){(origin.x - halfWidth), (origin.y), (origin.z - halfWidth)};

        Coordinate3D cordenadaD;
        cordenadaD = (Coordinate3D){(origin.x + halfWidth), (origin.y), (origin.z - halfWidth)};

        Coordinate3D tip;
        tip = (Coordinate3D){(origin.x), (origin.y + height), (origin.z)};
        
        //base
        Scene3D_add_quadrilateral(scene, cordenadaA, cordenadaB, cordenadaC, cordenadaD);

        //tip
        Triangle3D triangle_1 = (Triangle3D) {cordenadaA, cordenadaB, tip};
        Triangle3D triangle_2 = (Triangle3D) {cordenadaA, cordenadaD, tip};
        Triangle3D triangle_3 = (Triangle3D) {cordenadaD, cordenadaC, tip};
        Triangle3D triangle_4 = (Triangle3D) {cordenadaC, cordenadaB, tip};

        Scene3D_add_triangle(scene, triangle_1);
        Scene3D_add_triangle(scene, triangle_2);
        Scene3D_add_triangle(scene, triangle_3);
        Scene3D_add_triangle(scene, triangle_4);
    }
    else if (strcmp(orientation, "backward") == 0){
        //forward/backward refers to +/- on the Y axis
        Coordinate3D cordenadaA;
        cordenadaA = (Coordinate3D){(origin.x + halfWidth), (origin.y), (origin.z + halfWidth)};

        Coordinate3D cordenadaB;
        cordenadaB = (Coordinate3D){(origin.x - halfWidth), (origin.y), (origin.z + halfWidth)};

        Coordinate3D cordenadaC;
        cordenadaC = (Coordinate3D){(origin.x - halfWidth), (origin.y), (origin.z - halfWidth)};

        Coordinate3D cordenadaD;
        cordenadaD = (Coordinate3D){(origin.x + halfWidth), (origin.y), (origin.z - halfWidth)};

        Coordinate3D tip;
        tip = (Coordinate3D){(origin.x), (origin.y - height), (origin.z)};

        Scene3D_add_quadrilateral(scene, cordenadaA, cordenadaB, cordenadaC, cordenadaD);

        Triangle3D triangle_1 = (Triangle3D) {cordenadaA, cordenadaB, tip};
        Triangle3D triangle_2 = (Triangle3D) {cordenadaA, cordenadaD, tip};
        Triangle3D triangle_3 = (Triangle3D) {cordenadaD, cordenadaC, tip};
        Triangle3D triangle_4 = (Triangle3D) {cordenadaC, cordenadaB, tip};

        Scene3D_add_triangle(scene, triangle_1);
        Scene3D_add_triangle(scene, triangle_2);
        Scene3D_add_triangle(scene, triangle_3);
        Scene3D_add_triangle(scene, triangle_4);
    }
    else if (strcmp(orientation, "up") == 0){
        //up/down refers to +/- on the Z axis
        Coordinate3D cordenadaA;
        cordenadaA = (Coordinate3D){(origin.x - halfWidth), (origin.y - halfWidth), (origin.z)};

        Coordinate3D cordenadaB;
        cordenadaB = (Coordinate3D){(origin.x - halfWidth), (origin.y + halfWidth), (origin.z)};

        Coordinate3D cordenadaC;
        cordenadaC = (Coordinate3D){(origin.x + halfWidth), (origin.y - halfWidth), (origin.z)};

        Coordinate3D cordenadaD;
        cordenadaD = (Coordinate3D){(origin.x + halfWidth), (origin.y + halfWidth), (origin.z)};

        Coordinate3D tip;
        tip = (Coordinate3D){(origin.x), (origin.y), (origin.z + height)};

        Scene3D_add_quadrilateral(scene, cordenadaA, cordenadaB, cordenadaC, cordenadaD);

        Triangle3D triangle_1 = (Triangle3D) {cordenadaA, cordenadaB, tip};
        Triangle3D triangle_2 = (Triangle3D) {cordenadaB, cordenadaD, tip};
        Triangle3D triangle_3 = (Triangle3D) {cordenadaD, cordenadaC, tip};
        Triangle3D triangle_4 = (Triangle3D) {cordenadaC, cordenadaA, tip};

        Scene3D_add_triangle(scene, triangle_1);
        Scene3D_add_triangle(scene, triangle_2);
        Scene3D_add_triangle(scene, triangle_3);
        Scene3D_add_triangle(scene, triangle_4);
    }
    else if (strcmp(orientation, "down") == 0){
        //up/down refers to +/- on the Z axis
        Coordinate3D cordenadaA;
        cordenadaA = (Coordinate3D){(origin.x - halfWidth), (origin.y - halfWidth), (origin.z)};

        Coordinate3D cordenadaB;
        cordenadaB = (Coordinate3D){(origin.x - halfWidth), (origin.y + halfWidth), (origin.z)};

        Coordinate3D cordenadaC;
        cordenadaC = (Coordinate3D){(origin.x + halfWidth), (origin.y - halfWidth), (origin.z)};

        Coordinate3D cordenadaD;
        cordenadaD = (Coordinate3D){(origin.x + halfWidth), (origin.y + halfWidth), (origin.z)};

        Coordinate3D tip;
        tip = (Coordinate3D){(origin.x), (origin.y), (origin.z - height)};

        Scene3D_add_quadrilateral(scene, cordenadaA, cordenadaB, cordenadaC, cordenadaD);

        Triangle3D triangle_1 = (Triangle3D) {cordenadaA, cordenadaB, tip};
        Triangle3D triangle_2 = (Triangle3D) {cordenadaB, cordenadaD, tip};
        Triangle3D triangle_3 = (Triangle3D) {cordenadaD, cordenadaC, tip};
        Triangle3D triangle_4 = (Triangle3D) {cordenadaC, cordenadaA, tip};

        Scene3D_add_triangle(scene, triangle_1);
        Scene3D_add_triangle(scene, triangle_2);
        Scene3D_add_triangle(scene, triangle_3);
        Scene3D_add_triangle(scene, triangle_4);
    }
    else if (strcmp(orientation, "right") == 0){
        //right/left refers to +/- on the X axis
        Coordinate3D cordenadaA;
        cordenadaA = (Coordinate3D){(origin.x), (origin.y + halfWidth), (origin.z + halfWidth)};

        Coordinate3D cordenadaB;
        cordenadaB = (Coordinate3D){(origin.x), (origin.y + halfWidth), (origin.z - halfWidth)};

        Coordinate3D cordenadaC;
        cordenadaC = (Coordinate3D){(origin.x), (origin.y - halfWidth), (origin.z - halfWidth)};

        Coordinate3D cordenadaD;
        cordenadaD = (Coordinate3D){(origin.x), (origin.y - halfWidth), (origin.z + halfWidth)};

        Coordinate3D tip;
        tip = (Coordinate3D){(origin.x + height), (origin.y), (origin.z)};

        Scene3D_add_quadrilateral(scene, cordenadaA, cordenadaB, cordenadaC, cordenadaD);

        Triangle3D triangle_1 = (Triangle3D) {cordenadaA, cordenadaB, tip};
        Triangle3D triangle_2 = (Triangle3D) {cordenadaA, cordenadaD, tip};
        Triangle3D triangle_3 = (Triangle3D) {cordenadaD, cordenadaC, tip};
        Triangle3D triangle_4 = (Triangle3D) {cordenadaC, cordenadaB, tip};

        Scene3D_add_triangle(scene, triangle_1);
        Scene3D_add_triangle(scene, triangle_2);
        Scene3D_add_triangle(scene, triangle_3);
        Scene3D_add_triangle(scene, triangle_4);
    }
    else if (strcmp(orientation, "left") == 0){
        //right/left refers to +/- on the X axis
        Coordinate3D cordenadaA;
        cordenadaA = (Coordinate3D){(origin.x), (origin.y + halfWidth), (origin.z + halfWidth)};

        Coordinate3D cordenadaB;
        cordenadaB = (Coordinate3D){(origin.x), (origin.y + halfWidth), (origin.z - halfWidth)};

        Coordinate3D cordenadaC;
        cordenadaC = (Coordinate3D){(origin.x), (origin.y - halfWidth), (origin.z - halfWidth)};

        Coordinate3D cordenadaD;
        cordenadaD = (Coordinate3D){(origin.x), (origin.y - halfWidth), (origin.z + halfWidth)};

        Coordinate3D tip;
        tip = (Coordinate3D){(origin.x - height), (origin.y), (origin.z)};

        Scene3D_add_quadrilateral(scene, cordenadaA, cordenadaB, cordenadaC, cordenadaD);

        Triangle3D triangle_1 = (Triangle3D) {cordenadaA, cordenadaB, tip};
        Triangle3D triangle_2 = (Triangle3D) {cordenadaA, cordenadaD, tip};
        Triangle3D triangle_3 = (Triangle3D) {cordenadaD, cordenadaC, tip};
        Triangle3D triangle_4 = (Triangle3D) {cordenadaC, cordenadaB, tip};

        Scene3D_add_triangle(scene, triangle_1);
        Scene3D_add_triangle(scene, triangle_2);
        Scene3D_add_triangle(scene, triangle_3);
        Scene3D_add_triangle(scene, triangle_4);
    }
    else{
        printf("Invalid direction %s", orientation);
    }
}

void Scene3D_add_cuboid(Scene3D *scene, Coordinate3D origin, double width, double height, double depth)
{
    double halfWidth = width / 2.0;
    double halfHeight = height / 2.0;
    double halfDepth = depth / 2.0;

    //get four points to create four quadrilaterals with these points
    Coordinate3D cordenadaA;
    cordenadaA = (Coordinate3D){(origin.x - halfWidth), (origin.y + halfHeight), (origin.z + halfDepth)};

    Coordinate3D cordenadaB;
    cordenadaB = (Coordinate3D){(origin.x - halfWidth), (origin.y + halfHeight), (origin.z - halfDepth)};

    Coordinate3D cordenadaC;
    cordenadaC = (Coordinate3D){(origin.x + halfWidth), (origin.y + halfHeight), (origin.z - halfDepth)};

    Coordinate3D cordenadaD;
    cordenadaD = (Coordinate3D){(origin.x + halfWidth), (origin.y + halfHeight), (origin.z + halfDepth)};

    Coordinate3D cordenadaE;
    cordenadaE = (Coordinate3D){(origin.x - halfWidth), (origin.y - halfHeight), (origin.z + halfDepth)};

    Coordinate3D cordenadaF;
    cordenadaF = (Coordinate3D){(origin.x - halfWidth), (origin.y - halfHeight), (origin.z - halfDepth)};

    Coordinate3D cordenadaG;
    cordenadaG = (Coordinate3D){(origin.x + halfWidth), (origin.y - halfHeight), (origin.z - halfDepth)};

    Coordinate3D cordenadaH;
    cordenadaH = (Coordinate3D){(origin.x + halfWidth), (origin.y - halfHeight), (origin.z + halfDepth)};

    Scene3D_add_quadrilateral(scene, cordenadaA, cordenadaB, cordenadaC, cordenadaD);
    Scene3D_add_quadrilateral(scene, cordenadaD, cordenadaC, cordenadaG, cordenadaH);
    Scene3D_add_quadrilateral(scene, cordenadaE, cordenadaF, cordenadaG, cordenadaH);
    Scene3D_add_quadrilateral(scene, cordenadaA, cordenadaB, cordenadaF, cordenadaE);
    Scene3D_add_quadrilateral(scene, cordenadaA, cordenadaD, cordenadaH, cordenadaE);
    Scene3D_add_quadrilateral(scene, cordenadaB, cordenadaC, cordenadaG, cordenadaF);
}

void Scene3D_add_quadrilateral(Scene3D *scene, Coordinate3D a, Coordinate3D b, Coordinate3D c, Coordinate3D d)
{
    Triangle3D triangle_1 = (Triangle3D) {a, b, c};
    Triangle3D triangle_2 = (Triangle3D) {b, c, d};
    Triangle3D triangle_3 = (Triangle3D) {a, c, d};
    Triangle3D triangle_4 = (Triangle3D) {a, b, d};

    // The Scene3D_add_triangle is one you should create!
    Scene3D_add_triangle(scene, triangle_1);
    Scene3D_add_triangle(scene, triangle_2);
    Scene3D_add_triangle(scene, triangle_3);
    Scene3D_add_triangle(scene, triangle_4);
}

/// @brief 
/// @param point 
/// @param file 
void write_point_binary(Coordinate3D point, FILE* file){
    float points[] = {point.x, point.y, point.z};
    fwrite(points, sizeof(float), 3, file);
    fflush(file);
}

/// @brief 
/// @param target_shape 
/// @param file 
/// @param node 
/// @param cur_shape 
void find_triangle_binary(int target_shape, FILE* file, Triangle3DNode* node, int cur_shape){
    if (cur_shape == target_shape){
        write_point_binary(node->triangle.a, file);
        write_point_binary(node->triangle.b, file);
        write_point_binary(node->triangle.c, file);
    }
    else{
        find_triangle_binary(target_shape, file, node->next, ++cur_shape);
    }
}

void Scene3D_write_stl_binary(Scene3D *scene, char *file_name)
{
    //open file
    FILE* file = fopen(file_name, "wb");
    if (file == NULL) {
        fprintf(stderr, "Opening file failed with code %d.\n", errno);
        return;
    }

    //start file 80 bytes of zeroed memory
    void* buffer = calloc(80, 1);
    fwrite(buffer, 80, 1, file);
    fflush(file);
    
    //write number of triangles
    uint32_t my_uint32 = scene->count;
    fwrite(&my_uint32, sizeof(uint32_t), 1, file);

    //write triangles
    int amount_shapes = scene->count;
    for (int target_shape = 0; target_shape < amount_shapes; target_shape++){ 
        float facet = 0.0;
        fwrite(&facet, sizeof(facet), 1, file);
        fwrite(&facet, sizeof(facet), 1, file);
        fwrite(&facet, sizeof(facet), 1, file);

        find_triangle_binary(target_shape, file, scene->root, 0);

        //last two bytes
        uint16_t end = 0;
        fwrite(&end, sizeof(uint16_t), 1, file);
        fflush(file);
    }

    //end file
    fflush(file);
    fclose(file);
    free(buffer);
}

/// @brief 
/// @param radius 
/// @param phi 
/// @return 
float sphere_to_car_z(float radius, float phi){
    // convert angles to radians
    float phi_radians = phi * PI / 180.0; 
    return (radius * cos(phi_radians));
}

/// @brief 
/// @param radius 
/// @param theta 
/// @param phi 
/// @return 
float sphere_to_car_y(float radius, float theta, float phi){
    // convert angles to radians
    float theta_radians = theta * PI / 180.0; 
    float phi_radians = phi * PI / 180.0; 
    return (radius * sin(phi_radians) * sin(theta_radians));
}

/// @brief 
/// @param radius 
/// @param theta 
/// @param phi 
/// @return 
float sphere_to_car_x(float radius, float theta, float phi){
    // convert angles to radians
    float theta_radians = theta * PI / 180.0; 
    float phi_radians = phi * PI / 180.0; 
    return (radius * sin(phi_radians) * cos(theta_radians));
}

float round2(float value) {
    return round(value * 10000.0) / 10000.0;
}

void Scene3D_add_sphere(Scene3D *scene, Coordinate3D origin, double radius, double increment)
{
    for (float phi = increment; phi <= 180; phi += increment){
        for (float theta = 0; theta < 360; theta += increment){
           Coordinate3D cordinate1;
           cordinate1.x = round2(sphere_to_car_x(radius, theta, phi));
           cordinate1.y = round2(sphere_to_car_y(radius, theta, phi));
           cordinate1.z = round2(sphere_to_car_z(radius, phi));

           Coordinate3D cordinate2;
           cordinate2.x = round2(sphere_to_car_x(radius, theta, phi - increment));
           cordinate2.y = round2(sphere_to_car_y(radius, theta, phi - increment));
           cordinate2.z = round2(sphere_to_car_z(radius, phi - increment));

           Coordinate3D cordinate3;
           cordinate3.x = round2(sphere_to_car_x(radius, theta - increment, phi));
           cordinate3.y = round2(sphere_to_car_y(radius, theta - increment, phi));
           cordinate3.z = round2(sphere_to_car_z(radius, phi));

           Coordinate3D cordinate4;
           cordinate4.x = round2(sphere_to_car_x(radius, theta - increment, phi - increment));
           cordinate4.y = round2(sphere_to_car_y(radius, theta - increment, phi - increment));
           cordinate4.z = round2(sphere_to_car_z(radius, phi - increment));

           //offset
           cordinate1.x += origin.x;
           cordinate1.y += origin.y;
           cordinate1.z += origin.z;

           cordinate2.x += origin.x;
           cordinate2.y += origin.y;
           cordinate2.z += origin.z;
           
           cordinate3.x += origin.x;
           cordinate3.y += origin.y;
           cordinate3.z += origin.z;

           cordinate4.x += origin.x;
           cordinate4.y += origin.y;
           cordinate4.z += origin.z;

           Scene3D_add_quadrilateral(scene, cordinate1, cordinate2, cordinate3, cordinate4);
        }
    }
}

void Scene3D_add_fractal(Scene3D *scene, Coordinate3D origin, double size, int levels)
{
    if (levels >= 1){
        Scene3D_add_cuboid(scene, origin, size, size, size);

        int newSize = size / 2;

        Coordinate3D newOriginY1;
        newOriginY1.x = origin.x;
        newOriginY1.y = origin.y + (size / 2);
        newOriginY1.z = origin.z;
        Scene3D_add_fractal(scene, newOriginY1, newSize, levels - 1);

        Coordinate3D newOriginY2;
        newOriginY2.x = origin.x;
        newOriginY2.y = origin.y - (size / 2);
        newOriginY2.z = origin.z;
        Scene3D_add_fractal(scene, newOriginY2, newSize, levels - 1);

        Coordinate3D newOriginX1;
        newOriginX1.x = origin.x + (size / 2);
        newOriginX1.y = origin.y;
        newOriginX1.z = origin.z;
        Scene3D_add_fractal(scene, newOriginX1, newSize, levels - 1);

        Coordinate3D newOriginX2;
        newOriginX2.x = origin.x - (size / 2);
        newOriginX2.y = origin.y;
        newOriginX2.z = origin.z;
        Scene3D_add_fractal(scene, newOriginX2, newSize, levels - 1);

        Coordinate3D newOriginZ1;
        newOriginZ1.x = origin.x;
        newOriginZ1.y = origin.y;
        newOriginZ1.z = origin.z + (size / 2);
        Scene3D_add_fractal(scene, newOriginZ1, newSize, levels - 1);

        Coordinate3D newOriginZ2;
        newOriginZ2.x = origin.x;
        newOriginZ2.y = origin.y;
        newOriginZ2.z = origin.z - (size / 2);
        Scene3D_add_fractal(scene, newOriginZ2, newSize, levels - 1);
    }
}
