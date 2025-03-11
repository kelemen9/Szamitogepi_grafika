#include <stdio.h>
#include <math.h>

#define MATRIX_SIZE 3 // Matrix merete (3x3), mert homogen koordinatakkal dolgozunk

// Matrix struktura definicioja
typedef struct {
    float data[MATRIX_SIZE][MATRIX_SIZE]; // Matrix adatai
} Matrix;

// Egysegmatrix inicializalasa
void init_identity_matrix(Matrix* m) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            m->data[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

// Matrix skalarral valo szorzasa
void scalar_multiply_matrix(Matrix* m, float scalar) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            m->data[i][j] *= scalar;
        }
    }
}

// Matrixok szorzasa
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

// Pont transzformalasa a matrix alapjan
void transform_point(const Matrix* m, float* x, float* y) {
    float tempX = *x * m->data[0][0] + *y * m->data[0][1] + m->data[0][2];
    float tempY = *x * m->data[1][0] + *y * m->data[1][1] + m->data[1][2];
    *x = tempX;
    *y = tempY;
}

// Skalazas (origo kozepontu)
void scale(Matrix* m, float scaleX, float scaleY) {
    Matrix scaleMatrix;
    init_identity_matrix(&scaleMatrix);
    scaleMatrix.data[0][0] = scaleX;
    scaleMatrix.data[1][1] = scaleY;
    Matrix temp;
    multiply_matrices(&scaleMatrix, m, &temp);
    *m = temp;
}

// Eltolas (origo kozepontu)
void shift(Matrix* m, float shiftX, float shiftY) {
    Matrix shiftMatrix;
    init_identity_matrix(&shiftMatrix);
    shiftMatrix.data[0][2] = shiftX;
    shiftMatrix.data[1][2] = shiftY;
    multiply_matrices(&shiftMatrix, m, m);
}

// Forgatas (origo kozepontu)
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

// Matrix kiirasa (ellenorzeshez)
void print_matrix(const Matrix* m) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%f ", m->data[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Matrix m;
    init_identity_matrix(&m);

    printf("Kezdeti Matrix:\n");
    print_matrix(&m);

    scale(&m, 2.0f, 2.0f);
    printf("\nSkalazas utan:\n");
    print_matrix(&m);

    shift(&m, 5.0f, 10.0f);
    printf("\nEltolas utan:\n");
    print_matrix(&m);

    rotate(&m, 45.0f);
    printf("\nForgatas utan:\n");
    print_matrix(&m);

    float x = 1.0f, y = 1.0f;
    transform_point(&m, &x, &y);
    printf("\nTranszformalt pont: (%f, %f)\n", x, y);

    return 0;
}
