#include "scene.h"

#include <GL/gl.h>

#define CELL_SIZE 2

void init_scene(Scene* scene)
{
    scene->sphere_angle=0;
    scene->sphere_rotspeed=0.1;
}

void update_scene(Scene* scene)
{
     scene->sphere_angle+=scene->sphere_rotspeed;
    if(scene->sphere_angle>360)
    {
        scene->sphere_angle=0;
    }
}

void render_scene(const Scene* scene)
{
    draw_origin();
    draw_triangle();
    draw_board();
    draw_cylinder();
    draw_cone();
}

void draw_cylinder()
{
    int i;
    float angle;

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_triangle_strip);

    for (i = 0; i <= segments; i++)
    {
        angle = 2 * M_PI * i / segments;

        float x = cos(angle) * radius;
        float y = sin(angle) * radius;

        glVertex3f(x, y, 0.0);        
        glVertex3f(x, y, height);     
    }

    glEnd();
}

void draw_cone()
{
    int i;
    float angle;

    glColor3f(1.0, 0.2, 0.4);
    glBegin(GL_triangle_fan);
    glVertex3f(0.0, 0.0, height); 

    for (i = 0; i <= segments; i++)
    {
        angle = 2 * M_PI * i / segments;

        float x = cos(angle) * radius;
        float y = sin(angle) * radius;

        glVertex3f(x, y, 0.0);    
    }

    glEnd();
}

void draw_board()
{
    int i, j;

    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            int color = (i + j) % 2;
            drawSquare(i, j, color);
        }
    }
}

void draw_square(int i, int j, int color)
{
    float x = i * CELL_SIZE;
    float y = j * CELL_SIZE;

    if (color == 0)
        glColor3f(1.0, 1.0, 1.0);
    else
        glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_QUADS);

    glVertex3f(x, y, 0.0);
    glVertex3f(x + CELL_SIZE, y, 0.0);
    glVertex3f(x + CELL_SIZE, y + CELL_SIZE, 0.0);
    glVertex3f(x, y + CELL_SIZE, 0.0);

    glEnd();
}

void draw_triangle()
{   
    glBegin(GL_TRIANGLES);

    glColor3f(1,1,0); 
    glVertex3f(0.2,0.2,0.2);

    glColor3f(0,1,1); 
    glVertex3f(0.8,0.2,0.2);

    glColor3f(1,0,1); 
    glVertex3f(0.5,0.8,0.2);

    glEnd();
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}
