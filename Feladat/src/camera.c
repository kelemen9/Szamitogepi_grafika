#include "camera.h"
#include "scene.h"
#include <GL/gl.h>
#include <math.h>

void init_camera(Camera* camera)
{
    camera->position.x = -6;
    camera->position.y = 1.0;
    camera->position.z = 1.5;
    camera->rotation.x = -5.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = -10.0;
    camera->speed.x = 0;
    camera->speed.y = 0;
    camera->speed.z = 0;

    camera->is_preview_visible = 0;
    camera->is_guide_visible = 1;
    camera->is_lose_visible = 0;
    camera->is_win_visible = 0;
}

void update_camera(Camera* camera, double time)
{
    double angle;
    double side_angle;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

    camera->position.x += cos(angle) * camera->speed.y * time;
    camera->position.y += sin(angle) * camera->speed.y * time;
    camera->position.x += cos(side_angle) * camera->speed.x * time;
    camera->position.y += sin(side_angle) * camera->speed.x * time;
    
    camera->position.z += camera->speed.z * time;
}

void reset_camera(Camera* camera)
{
    camera->position.x = -6;
    camera->position.y = 1.0;
    camera->position.z = 1.5;
    camera->rotation.x = -5.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = -10.0;
    camera->speed.x = 0;
    camera->speed.y = 0;
    camera->speed.z = 0;
}

void set_view(Camera* camera) //const Camera
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

void set_camera_vertical_speed(Camera* camera, double speed)
{
    camera->speed.z = speed;
}

void show_texture_preview()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void show_guide()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, 1);
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1.9, 1.4, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1.9, 1.4, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1.9, -1.4, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1.9, -1.4, -3);
    glEnd();
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void show_lose()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, 2);
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1.9, 1.4, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1.9, 1.4, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1.9, -1.4, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1.9, -1.4, -3);
    glEnd();
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void show_win()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, 3);
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1.9, 1.4, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1.9, 1.4, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1.9, -1.4, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1.9, -1.4, -3);
    glEnd();
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}
