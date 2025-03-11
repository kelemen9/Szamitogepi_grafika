/* #include "circle.h"

void set_circle_data(Circle *circle, double x, double y, double radius, SDL_Color color)
{
	circle->x = x;
	circle->y = y;
	if (radius > 0.0)
	{
		circle->radius = radius;
	}
	else
	{
		circle->radius = NAN;
	}
}

double calc_circle_area(const Circle *circle)
{
	double area = circle->radius * circle->radius * M_PI;
	return area;
} */


#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define MAX_CIRCLES 100
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct {
    double x, y, radius;
    SDL_Color color;
} Circle;

Circle circles[MAX_CIRCLES];
int circle_count = 0;

int selected_circle = -1;

void add_circle(double x, double y, double radius, SDL_Color color) {
    if (circle_count < MAX_CIRCLES) {
        circles[circle_count].x = x;
        circles[circle_count].y = y;
        circles[circle_count].radius = radius;
        circles[circle_count].color = color;
        circle_count++;
    }
}

void draw_circle(SDL_Renderer *renderer, Circle *circle) {
    SDL_SetRenderDrawColor(renderer, circle->color.r, circle->color.g, circle->color.b, 255);
    for (int i = 0; i < 360; i++) {
        double angle = i * M_PI / 180.0;
        int x = circle->x + circle->radius * cos(angle);
        int y = circle->y + circle->radius * sin(angle);
        SDL_RenderDrawPoint(renderer, x, y);
    }
}

void draw_cross(SDL_Renderer *renderer, Circle *circle) {
    int size = circle->radius / 2;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black color
    SDL_RenderDrawLine(renderer, circle->x - size, circle->y - size, circle->x + size, circle->y + size); // Diagonal
    SDL_RenderDrawLine(renderer, circle->x - size, circle->y + size, circle->x + size, circle->y - size); // Other diagonal
}

int is_point_in_circle(int x, int y, Circle *circle) {
    return (pow(x - circle->x, 2) + pow(y - circle->y, 2) <= pow(circle->radius, 2));
}

void handle_mouse_motion(SDL_Event *e) {
    if (selected_circle != -1) {
        circles[selected_circle].x = e->motion.x;
        circles[selected_circle].y = e->motion.y;
    }
}

void handle_mouse_click(SDL_Event *e) {
    if (e->button.button == SDL_BUTTON_LEFT) {
        for (int i = 0; i < circle_count; i++) {
            if (is_point_in_circle(e->button.x, e->button.y, &circles[i])) {
                selected_circle = i;  // Select the circle
                return;
            }
        }

        // If no circle is selected, add a new one
        SDL_Color color = {rand() % 256, rand() % 256, rand() % 256};  // Random color
        add_circle(e->button.x, e->button.y, 50, color);  // New circle at mouse position
    } else if (e->button.button == SDL_BUTTON_RIGHT) {
        selected_circle = -1;  // Deselect circle on right click
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Circle Program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event e;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            } else if (e.type == SDL_MOUSEMOTION) {
                handle_mouse_motion(&e);
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                handle_mouse_click(&e);
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw all circles
        for (int i = 0; i < circle_count; i++) {
            draw_circle(renderer, &circles[i]);
            if (is_point_in_circle(e.motion.x, e.motion.y, &circles[i])) {
                draw_cross(renderer, &circles[i]);  // Draw cross if mouse is inside circle
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
