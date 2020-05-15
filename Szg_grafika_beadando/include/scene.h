#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Camera camera;
	Model mountain;
	Model pine_tree1;
	Model pine_tree2;
	Model dragon;
	Model ice;
        Model sky;
    Material material;
    GLuint texture_mountain;
    GLuint texture_pinetree;
    GLuint texture_dragon;
    GLuint texture_ice;
    GLuint texture_sky;
    GLuint help;
    

} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

void update_lighting(Scene* scene, double ertek);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene);

void dragon_move();


#endif /* SCENE_H */
