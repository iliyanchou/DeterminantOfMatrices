#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define EPS 1e-9

typedef struct Matrix {
    int rows;
    int cols;
    double **data;
} Matrix;

void cleanBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int readPositiveInt(const char *prompt) {
    int value;

    while (1) {
        printf("%s", prompt);

        if (scanf("%d", &value) != 1 || value <= 0) {
            printf("The value must be a positive integer!\n");
            cleanBuffer();
            continue;
        }

        cleanBuffer();
        return value;
    }
}

double readDouble(const char *prompt) {
    double value;

    while (1) {
        printf("%s", prompt);

        if (scanf("%lf", &value) != 1) {
            printf("The inserted value must be a number!\n");
            cleanBuffer();
            continue;
        }

        cleanBuffer();
        return value;
    }
}

Matrix createMatrix(int rows, int cols) {
    Matrix matrix;
    matrix.rows = rows;
    matrix.cols = cols;

    matrix.data = malloc(rows * sizeof(double *));
    if (matrix.data == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        matrix.data[i] = malloc(cols * sizeof(double));
        if (matrix.data[i] == NULL) {
            printf("Memory allocation failed!\n");

            for (int j = 0; j < i; j++) {
                free(matrix.data[j]);
            }

            free(matrix.data);
            exit(1);
        }
    }

    return matrix;
}

void freeMatrix(Matrix *matrix) {
    if (matrix == NULL || matrix->data == NULL) {
        return;
    }

    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }

    free(matrix->data);

    matrix->data = NULL;
    matrix->rows = 0;
    matrix->cols = 0;
}

Matrix copyMatrix(Matrix matrix) {
    Matrix copy = createMatrix(matrix.rows, matrix.cols);

    for (int r = 0; r < matrix.rows; r++) {
        for (int c = 0; c < matrix.cols; c++) {
            copy.data[r][c] = matrix.data[r][c];
        }
    }

    return copy;
}

Matrix inputMatrix(void) {
    printf("Please insert dimensions of matrix:\n");

    int rows = readPositiveInt("Insert rows: ");
    int cols = readPositiveInt("Insert columns: ");

    Matrix matrix = createMatrix(rows, cols);

    for (int r = 0; r < rows; r++) {
        printf("Enter elements of row %d one by one:\n", r + 1);

        for (int c = 0; c < cols; c++) {
            char prompt[64];
            snprintf(prompt, sizeof(prompt), "Enter element %d%d: ", r + 1, c + 1);
            matrix.data[r][c] = readDouble(prompt);
        }
    }

    return matrix;
}

void printMatrix(Matrix matrix) {
    for (int r = 0; r < matrix.rows; r++) {
        for (int c = 0; c < matrix.cols; c++) {
            if (fabs(matrix.data[r][c]) < EPS) {
                printf("%10.2lf ", 0.0);
            } else {
                printf("%10.2lf ", matrix.data[r][c]);
            }
        }

        printf("\n");
    }
}

int transformMatrixToTriangle(Matrix *matrix) {
    int sign = 1;
    int pivotRow = 0;

    for (int col = 0; col < matrix->cols && pivotRow < matrix->rows; col++) {
        int bestRow = pivotRow;

        while (bestRow < matrix->rows && fabs(matrix->data[bestRow][col]) < EPS) {
            bestRow++;
        }

        if (bestRow == matrix->rows) {
            continue;
        }

        if (bestRow != pivotRow) {
            double *temp = matrix->data[pivotRow];
            matrix->data[pivotRow] = matrix->data[bestRow];
            matrix->data[bestRow] = temp;
            sign *= -1;
        }

        for (int r = pivotRow + 1; r < matrix->rows; r++) {
            if (fabs(matrix->data[r][col]) < EPS) {
                continue;
            }

            double multiplier = matrix->data[r][col] / matrix->data[pivotRow][col];

            for (int c = col; c < matrix->cols; c++) {
                matrix->data[r][c] -= multiplier * matrix->data[pivotRow][c];

                if (fabs(matrix->data[r][c]) < EPS) {
                    matrix->data[r][c] = 0.0;
                }
            }
        }

        pivotRow++;
    }

    return sign;
}

double determinant(Matrix matrix) {
    if (matrix.rows != matrix.cols) {
        printf("Determinant can only be calculated for square matrices!\n");
        return NAN;
    }

    Matrix temp = copyMatrix(matrix);
    int sign = transformMatrixToTriangle(&temp);

    double det = (double)sign;

    for (int i = 0; i < temp.rows; i++) {
        det *= temp.data[i][i];
    }

    if (fabs(det) < EPS) {
        det = 0.0;
    }

    freeMatrix(&temp);
    return det;
}

int rankOfMatrix(Matrix matrix) {
    Matrix temp = copyMatrix(matrix);
    transformMatrixToTriangle(&temp);

    int rank = 0;

    for (int r = 0; r < temp.rows; r++) {
        bool nonZeroRow = false;

        for (int c = 0; c < temp.cols; c++) {
            if (fabs(temp.data[r][c]) > EPS) {
                nonZeroRow = true;
                break;
            }
        }

        if (nonZeroRow) {
            rank++;
        }
    }

    freeMatrix(&temp);
    return rank;
}

Matrix addOrSubtractMatrices(Matrix matrix1, Matrix matrix2, int operation) {
    if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols) {
        printf("Matrices must have the same dimensions!\n");
        return createMatrix(0, 0);
    }

    Matrix result = createMatrix(matrix1.rows, matrix1.cols);

    for (int r = 0; r < matrix1.rows; r++) {
        for (int c = 0; c < matrix1.cols; c++) {
            if (operation == 1) {
                result.data[r][c] = matrix1.data[r][c] + matrix2.data[r][c];
            } else {
                result.data[r][c] = matrix1.data[r][c] - matrix2.data[r][c];
            }
        }
    }

    return result;
}

Matrix transposeMatrix(Matrix matrix) {
    Matrix result = createMatrix(matrix.cols, matrix.rows);

    for (int r = 0; r < matrix.rows; r++) {
        for (int c = 0; c < matrix.cols; c++) {
            result.data[c][r] = matrix.data[r][c];
        }
    }

    return result;
}

void printMenu(void) {
    printf("\n========== MATRIX TOOL ==========\n");
    printf("1. Print matrix\n");
    printf("2. Transform matrix to triangular form\n");
    printf("3. Calculate determinant\n");
    printf("4. Calculate rank\n");
    printf("5. Transpose matrix\n");
    printf("0. Exit\n");
    printf("=================================\n");
}

int main(void) {
    Matrix matrix = inputMatrix();

    while (1) {
        printMenu();

        int choice = readPositiveInt("Choose option: ");

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1:
                printf("\nMatrix:\n");
                printMatrix(matrix);
                break;

            case 2: {
                Matrix triangular = copyMatrix(matrix);
                transformMatrixToTriangle(&triangular);

                printf("\nTriangular form:\n");
                printMatrix(triangular);

                freeMatrix(&triangular);
                break;
            }

            case 3: {
                double det = determinant(matrix);

                if (!isnan(det)) {
                    printf("\nDeterminant: %.2lf\n", det);
                }

                break;
            }

            case 4: {
                int rank = rankOfMatrix(matrix);
                printf("\nRank: %d\n", rank);
                break;
            }

            case 5: {
                Matrix transposed = transposeMatrix(matrix);

                printf("\nTransposed matrix:\n");
                printMatrix(transposed);

                freeMatrix(&transposed);
                break;
            }

            default:
                printf("Invalid option!\n");
                break;
        }
    }

    freeMatrix(&matrix);

    printf("Program closed.\n");
    return 0;
}
