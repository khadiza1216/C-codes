#include <stdio.h>
#include <math.h>

#define MAX_POINTS 10

void printMatrix(int n, double A[MAX_POINTS][MAX_POINTS], double b[MAX_POINTS]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2lf\t", A[i][j]);
        }
        printf("| %.2lf\n", b[i]);
    }
    printf("\n");
}

void gaussianElimination(int n, double A[MAX_POINTS][MAX_POINTS], double b[MAX_POINTS], double coeffs[MAX_POINTS]) {
    // Forward Elimination
    for (int k = 0; k < n - 1; k++) {
        // Partial Pivoting
        int max_row = k;
        for (int i = k + 1; i < n; i++) {
            if (fabs(A[i][k]) > fabs(A[max_row][k])) {
                max_row = i;
            }
        }
        // Swap rows if needed
        if (max_row != k) {
            for (int j = k; j < n; j++) {
                double temp = A[k][j];
                A[k][j] = A[max_row][j];
                A[max_row][j] = temp;
            }
            double temp = b[k];
            b[k] = b[max_row];
            b[max_row] = temp;
        }

        // Elimination
        for (int i = k + 1; i < n; i++) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < n; j++) {
                A[i][j] -= factor * A[k][j];
            }
            b[i] -= factor * b[k];
        }
    }

    // Back Substitution
    for (int i = n - 1; i >= 0; i--) {
        coeffs[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            coeffs[i] -= A[i][j] * coeffs[j];
        }
        coeffs[i] /= A[i][i];
    }
}

void directInterpolation(int n, double x[MAX_POINTS], double y[MAX_POINTS], double coeffs[MAX_POINTS]) {
    double A[MAX_POINTS][MAX_POINTS], b[MAX_POINTS];

    // Construct Vandermonde matrix A and vector b
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = pow(x[i], j); // x_i^j
        }
        b[i] = y[i];
    }

    printf("Vandermonde Matrix (A|b):\n");
    printMatrix(n, A, b);

    // Solve the system A * coeffs = b
    gaussianElimination(n, A, b, coeffs);
}

int main() {
    int n;
    double x[MAX_POINTS], y[MAX_POINTS], coeffs[MAX_POINTS];

    printf("Enter the number of data points: ");
    scanf("%d", &n);

    printf("Enter the data points (x, y):\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d], y[%d]: ", i, i);
        scanf("%lf %lf", &x[i], &y[i]);
    }

    directInterpolation(n, x, y, coeffs);

    printf("\nInterpolating Polynomial Coefficients:\n");
    for (int i = 0; i < n; i++) {
        printf("a%d (x^%d term) = %.6lf\n", i, i, coeffs[i]);
    }

    printf("\nPolynomial Form:\nP(x) = ");
    for (int i = n - 1; i >= 0; i--) {
        if (i == 0) {
            printf("%.6lf", coeffs[i]);
        } else {
            printf("%.6lf x^%d + ", coeffs[i], i);
        }
    }
    printf("\n");

    return 0;
}
