#include "app.h"

#include <SDL2/SDL_image.h>

void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);

    if (error_code != 0)
    {
        printf("SDL init error\n");
        return;
    }

    app->window = SDL_CreateWindow(
        "Cube",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL);

    if(app->window == NULL)
    {
        printf("Window error\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);

    if(inited_loaders == 0)
    {
        printf("IMG error\n");
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);

    init_opengl();
    reshape(width,height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1,0.1,0.1,1);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-.08,.08,-.06,.06,.1,10);
}

void handle_app_events(App* app)
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {

        case SDL_KEYDOWN:

            switch(event.key.keysym.scancode)
            {

            case SDL_SCANCODE_ESCAPE:
                app->is_running=false;
                break;

            case SDL_SCANCODE_UP:
                app->scene.cat_y +=0.2;
                break;

            case SDL_SCANCODE_DOWN:
                app->scene.cat_y -=0.2;
                break;

            case SDL_SCANCODE_LEFT:
                app->scene.cat_x -=0.2;
                break;

            case SDL_SCANCODE_RIGHT:
                app->scene.cat_x +=0.2;
                break;

            }

            break;

        case SDL_QUIT:
            app->is_running=false;
            break;
        }
    }
}

void update_app(App* app)
{
    update_scene(&(app->scene));
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    set_view(&(app->camera));

    render_scene(&(app->scene));

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app)
{
    SDL_GL_DeleteContext(app->gl_context);

    SDL_DestroyWindow(app->window);

    SDL_Quit();
}