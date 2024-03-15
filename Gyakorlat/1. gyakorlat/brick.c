#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    float height;
    float length;
    float width;
} Brick;

void set_size(Brick *brick, float height, float length, float width) {
    brick->height = height;
    brick->length = length;
    brick->width = width;
}

float calc_volume(Brick brick) {
    return brick.height * brick.length * brick.width;
}

float calc_surface(Brick brick) {
    return 2 * (brick.height * brick.length + brick.length * brick.width + brick.height * brick.width);
}

bool has_square_face(Brick brick) {
    float volume = calc_volume(brick);
    return (brick.height * brick.height == volume || brick.length * brick.length == volume || brick.width * brick.width == volume);
}

float read_input(const char *msg) {
    float number = 0;
    printf("%s", msg);
    while (scanf("%f", &number) != 1) {
        printf("Invalid input. Please enter a valid number: ");
        while (getchar() != '\n');
    }
    return number;
}

int main() {
    Brick brick;

    float height = read_input("Enter brick height: ");
    float length = read_input("Enter brick length: ");
    float width = read_input("Enter brick width: ");
   
    set_size(&brick, height, length, width);

    printf("Brick volume: %.2f\n", calc_volume(brick));
    printf("Brick surface area: %.2f\n", calc_surface(brick));
    
    if (has_square_face(brick))
        printf("The brick has a square face.\n");
    else
        printf("The brick doesn't have a square face.\n");

    return 0;
}
