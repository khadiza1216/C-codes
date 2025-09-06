#include <stdio.h>
#include <math.h>

// Define the function f(x) = x^3 - x - 2
double f(double x) {
    return x * x * x - x - 2;
}

// False Position Method using tolerance
void false_position(double low, double up, double tolerance) {

    if (f(low) * f(up) >= 0) {
        printf("Invalid interval! f(low) and f(up) must have opposite signs.\n");
        return;
    }

    double root, prev_root;
    int iteration = 1;

    printf("Iteration\tlow\t\tup\t\troot\t\tf(root)\t\tRelative Error\n");

    // Initial approximation
    root = (low * f(up) - up * f(low)) / (f(up) - f(low));
    prev_root = root;

    while (1) {
        double froot = f(root);

        // Print current iteration
        printf("%d\t\t%.6f\t%.6f\t%.6f\t%.6f", iteration, low, up, root, froot);

        // Update bounds
        if (f(low) * froot < 0)
            up = root;
        else
            low = root;

        // Store previous root and calculate new root
        prev_root = root;
        root = (low * f(up) - up * f(low)) / (f(up) - f(low));

        // Relative error
        double rel_error = fabs((root - prev_root) / root);

        printf("\t%.6f\n", rel_error);

        // Check if error is within the given tolerance
        if (rel_error < tolerance)
            break;

        iteration++;
    }

    printf("\nApproximate root after tolerance met: %.6f\n", root);
}

// Main function
int main() {
    double xl, xu, epsilon;

    printf("Enter the initial interval [xl, xu]: ");
    scanf("%lf %lf", &xl, &xu);

    printf("Enter the tolerance (epsilon): ");
    scanf("%lf", &epsilon);

    false_position(xl, xu, epsilon);

    return 0;
}
