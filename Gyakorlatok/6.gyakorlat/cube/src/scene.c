#include "scene.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>

void init_scene(Scene* scene)
{
    // Ambient/diffuse alapértékek
    scene->ambient_light[0] = 0.2f;
    scene->ambient_light[1] = 0.2f;
    scene->ambient_light[2] = 0.2f;

    scene->diffuse_light[0] = 0.8f;
    scene->diffuse_light[1] = 0.8f;
    scene->diffuse_light[2] = 0.8f;

    scene->cat_forward = 0.0f;
    scene->cat_forward_speed = 1.0f;
}

void set_lighting(Scene* scene)
{
    float ambient[] = { scene->ambient_light[0], scene->ambient_light[1], scene->ambient_light[2], 1.0f };
    float diffuse[] = { scene->diffuse_light[0], scene->diffuse_light[1], scene->diffuse_light[2], 1.0f };
    float position[] = { 5.0f, 5.0f, 5.0f, 1.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float shininess[] = {100.0f}; // fémes hatás

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material->diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void update_scene(Scene* scene, double delta_time)
{
    // egyszerű forgatás
    scene->cat_forward += scene->cat_forward_speed * delta_time;
}

void render_scene(const Scene* scene)
{
    glPushMatrix();

    // forgatás idő függvényében
    glRotatef(scene->cat_forward * 50.0f, 0.0f, 1.0f, 0.0f);

    // Egyszerű kocka rajzolása
    glColor3f(0.8f, 0.1f, 0.1f);
    glutSolidCube(1.0);

    glPopMatrix();
}

void draw_origin()
{
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0,0,0); glVertex3f(1,0,0);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(0,0,0); glVertex3f(0,1,0);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(0,0,0); glVertex3f(0,0,1);
    glEnd();
}

//textúra váltás, eltelt idő függvényében

void update_scene(Scene*scene, double time) {
    scene -> modell_forward += scene -> modell_forward_speed * time;

    double t = SDL_GetTicks()/360.0;
    scene -> current_texture = ((int t % max_textures))
}