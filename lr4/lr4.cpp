#include <stdio.h>
#include <stdlib.h>

int countDigits(long a) {
    int count = 0;

    while (a > 0) {
        a /= 10;
        count++;
    }

    return count;
}

void performMultiplication(long x, long y, int n, int m) {
    int* linearConvolution = (int*)malloc(sizeof(int) * (n + m - 1));

    if (linearConvolution == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    for (int i = 0; i < (n + m - 1); i++)
        linearConvolution[i] = 0;

    long p = x;

    for (int i = 0; i < m; i++) {
        x = p;

        for (int j = 0; j < n; j++) {
            linearConvolution[i + j] += (y % 10) * (x % 10);
            x /= 10;
        }

        y /= 10;
    }

    printf("The linear convolution result is: ( ");
    for (int i = (n + m - 2); i >= 0; i--)
        printf("%d ", linearConvolution[i]);
    printf(")");

    long product = 0;
    int nextCarry = 0, base = 1;

    for (int i = 0; i < n + m - 1; i++) {
        linearConvolution[i] += nextCarry;
        product = product + (base * (linearConvolution[i] % 10));
        nextCarry = linearConvolution[i] / 10;
        base *= 10;
    }

    printf("\nThe product of the numbers is: %ld", product);

    free(linearConvolution);
}

int main(int argc, char** argv) {
    printf("Enter two numbers:");
    long a, b;
    scanf("%ld", &a);
    scanf("%ld", &b);
    int n = countDigits(a);
    int m = countDigits(b);
    performMultiplication(a, b, n, m);

    return 0;
}
