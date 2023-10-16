#include <stdio.h>
#include <math.h>

int main() {
    double xc, yc, R, A, B, C;
    double alpha, beta, gamma, D;

    scanf("%lf %lf %lf %lf %lf %lf", &xc, &yc, &R, &A, &B, &C);

    alpha = A * A + B * B;
    beta = 2 * (xc * A * B - yc * A * A + B * C);
    gamma = 2 * xc * A * C + pow(xc * A, 2) + pow(C, 2) + pow(yc * A, 2) - pow(R * A, 2);
    D = pow(beta, 2) - 4 * alpha * gamma;

    if (D < 0) {
        printf("0\n");
    } else if (D == 0) {
        double y = -beta / (2 * alpha);
        double x = -(B * y + C) / A;
        printf("1\n");
        printf("%.5lf  %.5lf\n", x, y);
    } else {
        D = sqrt(D);
        double y = (-beta + D) / (2 * alpha);
        double x = -(B * y + C) / A;
        printf("2\n");
        printf("%.5lf  %.5lf\n", x, y);

        y = (-beta - D) / (2 * alpha);
        x = -(B * y + C) / A;
        printf("%.5lf  %.5lf\n", x, y);
    }

    return 0;
}
