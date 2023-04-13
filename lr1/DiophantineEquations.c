#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b)
{
    while ((a != 0) && (b != 0)) {
        if (a > b) {
            a = a % b;
        }
        else {
            b = b % a;
        }
    }
    return(a + b);
}

bool isDivisible(int a, int b)
{
    if (a % b == 0) {
        return true;
    }

    return false;
}

int* extended_gcd(int a, int b)
{
    int* ret = (int*)malloc(sizeof(int) * 3);
    int x1, y1, x, y;

    if (a == 0) {
        ret[0] = b;
        ret[1] = 0;
        ret[2] = 1;
    }
    else {
        int temp_a = b % a;
        int* temp = extended_gcd(temp_a, a);
        y1 = temp[2];
        x1 = temp[1];
        x = y1 - (b / a) * x1;
        y = x1;
        ret[0] = temp[0];
        ret[1] = x;
        ret[2] = y;
        free(temp);
    }
    return ret;
}


int main()
{
    int a, b, c, d;
    bool isSolving;
    int* ret = (int*)malloc(sizeof(int) * 3);

    printf("\n%s", "Input a ");
    scanf("%d", &a);
    printf("\n%s", "Input b ");
    scanf("%d", &b);
    printf("\n%s", "Input c ");
    scanf("%d", &c);

    d = gcd(a, b);;
    isSolving = isDivisible(c, d);
    if (isSolving == false) {
        printf("%s", "No solutions");
        return 0;
    }
    else {
        printf("\n%s", "Solving");
        ret = extended_gcd(a, b);
        printf("\nAnswer x = %d, y = %d\n", c * ret[1] / ret[0], c * ret[2] / ret[0]);
    }

    return 0;
}

