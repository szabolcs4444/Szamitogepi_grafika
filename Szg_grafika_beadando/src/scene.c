#include "scene.h"

#include <GL/glut.h>

#include <time.h>
#include <obj/load.h>
#include <obj/draw.h>

double dragon_x=0;
double dragon_y=0;
double dragon_rotate=0;

double brightness=0;
double my_brightnesss=-2;

double tree1_moves=0;
double tree2_moves=0;



void init_scene(Scene* scene)
{
    load_model(&(scene->mountain), "obj/mountain.obj");
    scene->texture_mountain = load_texture("textures/mountain.png"); 	
	
    load_model(&(scene->pine_tree1), "obj/pinetree.obj");
    scene->texture_pinetree = load_texture("textures/pinetree.jpg");
	
	
		
    load_model(&(scene->pine_tree2), "obj/pinetree.obj");

    load_model(&(scene->dragon), "obj/dragon.obj");
    scene->texture_dragon = load_texture("textures/dragon.png"); 	
	
    load_model(&(scene->ice), "obj/ice.obj");
    scene->texture_ice = load_texture("textures/ice.png"); 
	
	load_model(&(scene->sky), "obj/ice.obj");
    scene->texture_sky = load_texture("textures/sky.jpg");
	
	
	scene->help = load_texture("textures/help.png"); 

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;
	
    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 6.0;
}

void set_lighting()
{
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = { 1.0f+brightness, 1.0f+brightness, 1.0f+brightness, 1.0f+brightness };
    float specular_light[] = { 1.0f+my_brightnesss, 1.0f+my_brightnesss, 1.0f+my_brightnesss, 1.0f+my_brightnesss };
    float position[] = { 40.0f, 20.0f, 10.0f, 2.0f };
 
	GLfloat light_position[] = {300, 0, -1000, 0.};
    GLfloat light_color[] = {0, 1, 0, 1};
	
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void update_lighting(Scene* scene, double value)
{
	brightness+=value;
	
}	

void my_light(int value){
	if(value==0){
			my_brightnesss=2;
	}	
	if(value==1){
			my_brightnesss=-2;
	}		
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
	
}

void draw_scene(const Scene* scene)
{
	glRotatef(90,1,0,0);
    set_material(&(scene->material));
    set_lighting();
	glBindTexture(GL_TEXTURE_2D, scene->texture_mountain);	
    draw_model(&(scene->mountain));
	
	glBindTexture(GL_TEXTURE_2D, scene->texture_ice);	
	glPushMatrix();	
		
		draw_model(&(scene->ice));
	glPopMatrix();	
	
	glBindTexture(GL_TEXTURE_2D, scene->texture_sky);	
	glPushMatrix();
		glTranslatef(0,90,0);
		
		draw_model(&(scene->sky));
	glPopMatrix();
	
	
	
	glBindTexture(GL_TEXTURE_2D, scene->texture_pinetree);
	glPushMatrix();
		glTranslatef(0.9,0.0,1+tree1_moves);
    draw_model(&(scene->pine_tree1));
	glPopMatrix();	
	
	glBindTexture(GL_TEXTURE_2D, scene->texture_pinetree);	
	glPushMatrix();
		glRotatef(180,0,1,0);
		glTranslatef(-0.9,0.0,-1.3+tree2_moves);
	draw_model(&(scene->pine_tree2));
	glPopMatrix();	

	glBindTexture(GL_TEXTURE_2D, scene->texture_dragon);	
	glPushMatrix();
		glRotatef(180+dragon_rotate,0,1,0);
		glTranslatef(-1.3+dragon_x,0+dragon_y,-0.2);
	draw_model(&(scene->dragon));
	glPopMatrix();	
	
	glBindTexture(GL_TEXTURE_2D, scene->help);	
}

void dragon_move(double time){
	if(dragon_rotate<90){
	dragon_x=dragon_x-time/100;	
	dragon_y=dragon_y+time/7;
	dragon_rotate=dragon_rotate+time*10;
	
	}
	else if(dragon_rotate>90&&dragon_rotate<180){
		dragon_x=dragon_x-time/100;	
		dragon_y=dragon_y-time/10;
		dragon_rotate=dragon_rotate+time*10;
		
		
	}
	else if(dragon_rotate>180&&dragon_rotate<270){
	dragon_x=dragon_x-time/100;	
	dragon_y=dragon_y+time/7;
	dragon_rotate=dragon_rotate+time*10;
	
	}
	
	else if(dragon_rotate>270&&dragon_rotate<360){
		dragon_x=dragon_x-time/100;	
		dragon_y=dragon_y-time/10;
		dragon_rotate=dragon_rotate+time*10;
		
		
	}else{
		dragon_rotate=0;
	}
}		

void tree_move(double time){
	if(tree1_moves<0.054){
		tree1_moves+=time/100;
		tree2_moves+=time/100;
	}
}
void tree_move_back(double time){
	if(tree1_moves>0){
		tree1_moves-=time/100;
		tree2_moves-=time/100;
	}
}	

	
