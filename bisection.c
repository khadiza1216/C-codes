#include <stdio.h>
#include <math.h>

// Define the function f(x) = x^3 - x - 2
double f(double x) {
    return x * x * x - x - 2;
}

// Bisection method using tolerance
void bisection(double low, double up, double tolerance) {

    if (f(low) * f(up) >= 0) {
        printf("Invalid interval! f(low) and f(up) must have opposite signs.\n");
        return;
    }

    double mid, prev_mid;
    int iteration = 1;

    printf("Iteration\tlow\t\tup\t\tmid\t\tf(mid)\t\tRelative Error\n");

    mid = (low + up) / 2.0;  // First midpoint
    prev_mid = mid;

    while (1) {
        double fmid = f(mid);

        // Print current iteration details
        printf("%d\t\t%.6f\t%.6f\t%.6f\t%.6f", iteration, low, up, mid, fmid);

        // Update bounds
        if (f(low) * fmid < 0)
            up = mid;
        else
            low = mid;

        // Calculate new midpoint
        prev_mid = mid;
        mid = (low + up) / 2.0;

        // Calculate relative approximate error
        double rel_error = fabs((mid - prev_mid) / mid);

        printf("\t%.6f\n", rel_error);

        // Break if relative error is less than tolerance
        if (rel_error < tolerance)
            break;

        iteration++;
    }

    printf("\nApproximate root after tolerance met: %.6f\n", mid);
}

// Main function
int main() {
    double xl, xu, epsilon;

    printf("Enter the initial interval [xl, xu]: ");
    scanf("%lf %lf", &xl, &xu);

    printf("Enter the tolerance (epsilon): ");
    scanf("%lf", &epsilon);

    bisection(xl, xu, epsilon);

    return 0;
}
