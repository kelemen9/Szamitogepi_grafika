#include <stdio.h>
#include <math.h>

#define MATRIX_SIZE 3
#define MAX_STACK_SIZE 10

typedef struct {
    float data[MATRIX_SIZE][MATRIX_SIZE];
} Matrix;

typedef struct {
    Matrix stack[MAX_STACK_SIZE];
    int top;
} MatrixStack;

void init_identity_matrix(Matrix* m) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            m->data[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

void multiply_matrices(const Matrix* a, const Matrix* b, Matrix* result) {
    Matrix tempResult;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            tempResult.data[i][j] = 0.0f;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                tempResult.data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result->data[i][j] = tempResult.data[i][j];
        }
    }
}

void scalar_multiply_matrix(Matrix* m, float scalar) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            m->data[i][j] *= scalar;
        }
    }
}

void transform_point(const Matrix* m, float* x, float* y) {
    float tempX = *x * m->data[0][0] + *y * m->data[0][1] + m->data[0][2];
    float tempY = *x * m->data[1][0] + *y * m->data[1][1] + m->data[1][2];
    *x = tempX;
    *y = tempY;
}

void init_matrix_stack(MatrixStack* stack) {
    stack->top = -1;
}

void push_matrix(MatrixStack* stack, const Matrix* m) {
    if (stack->top < MAX_STACK_SIZE - 1) {
        stack->top++;
        stack->stack[stack->top] = *m;
    } else {
        printf("Verem tulcsordulas!\n");
    }
}

void pop_matrix(MatrixStack* stack, Matrix* m) {
    if (stack->top >= 0) {
        *m = stack->stack[stack->top];
        stack->top--;
    } else {
        printf("A verem ures!\n");
    }
}

void scale(Matrix* m, float scaleX, float scaleY) {
    Matrix scaleMatrix;
    init_identity_matrix(&scaleMatrix);
    scaleMatrix.data[0][0] = scaleX;
    scaleMatrix.data[1][1] = scaleY;
    Matrix temp;
    multiply_matrices(&scaleMatrix, m, &temp);
    *m = temp;
}

void shift(Matrix* m, float shiftX, float shiftY) {
    Matrix shiftMatrix;
    init_identity_matrix(&shiftMatrix);
    shiftMatrix.data[0][2] = shiftX;
    shiftMatrix.data[1][2] = shiftY;
    multiply_matrices(&shiftMatrix, m, m);
}

void rotate(Matrix* m, float angle) {
    Matrix rotateMatrix;
    init_identity_matrix(&rotateMatrix);
    float rad = angle * M_PI / 180.0f;
    rotateMatrix.data[0][0] = cos(rad);
    rotateMatrix.data[0][1] = -sin(rad);
    rotateMatrix.data[1][0] = sin(rad);
    rotateMatrix.data[1][1] = cos(rad);
    multiply_matrices(&rotateMatrix, m, m);
}

void print_matrix(const Matrix* m) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%f ", m->data[i][j]);
        }
        printf("\n");
    }
}

int main() {
    MatrixStack stack;
    init_matrix_stack(&stack);

    Matrix m;
    init_identity_matrix(&m);
    printf("Kezdeti Matrix:\n");
    print_matrix(&m);

    scale(&m, 2.0f, 2.0f);
    printf("\nSkalazott Matrix:\n");
    print_matrix(&m);

    push_matrix(&stack, &m);

    shift(&m, 5.0f, 10.0f);
    printf("\nEltolt Matrix:\n");
    print_matrix(&m);

    push_matrix(&stack, &m);

    rotate(&m, 45.0f);
    printf("\nForgatott Matrix:\n");
    print_matrix(&m);

    pop_matrix(&stack, &m);
    printf("\nVisszavont Matrix (Forgatas utan):\n");
    print_matrix(&m);

    pop_matrix(&stack, &m);
    printf("\nVisszavont Matrix (Eltolas utan):\n");
    print_matrix(&m);

    return 0;
}
