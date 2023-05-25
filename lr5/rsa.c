
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#pragma warning(disable:4996)

int gcd(int a, int b);
int PrimarityTest(int a, int i);
int FindT(int a, int m, int n);
int FastExponention(int bit, int n, int* y, int* a);
int inverse(int a, int b);
int KeyGeneration();
char* Encryption(const char* input);

int e, d, n;


int gcd(int a, int b)
{
    int q, r1, r2, r;

    if (a > b)
    {
        r1 = a;
        r2 = b;
    }
    else {
        r1 = b;
        r2 = a;
    }

    while (r2 > 0)
    {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;
    }

    return r1;
}

int PrimarityTest(int a, int i)
{
    int n = i - 1;
    int k = 0;
    int j, m, T;

    while (n % 2 == 0)
    {
        k++;
        n = n / 2;
    }

    m = n;
    T = FindT(a, m, i);

    if (T == 1 || T == i - 1) {
        return 1;
    }

    for (j = 0; j < k; j++)
    {
        T = FindT(T, 2, i);
        if (T == 1) {
            return 0;
        }
        if (T == i - 1) {
            return 1;
        }
    }
    return 0;
}

int FindT(int a, int m, int n)
{
    int r;
    int y = 1;

    while (m > 0)
    {
        r = m % 2;
        FastExponention(r, n, &y, &a);
        m = m / 2;
    }
    return y;
}

int FastExponention(int bit, int n, int* y, int* a)
{
    if (bit == 1) {
        *y = (*y * (*a)) % n;
    }

    *a = (*a) * (*a) % n;
    return *a;
}

int inverse(int a, int b)
{
    int inv;
    int q, r, r1 = a, r2 = b, t, t1 = 0, t2 = 1;

    while (r2 > 0)
    {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;

        t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }

    if (r1 == 1) {
        inv = t1;
    }

    if (inv < 0) {
        inv = inv + a;
    }

    return inv;
}

int KeyGeneration()
{
    int p, q;
    int phi_n;

    do {
        do
            p = rand();
        while (p % 2 == 0);

    } while (!PrimarityTest(2, p));

    do {
        do
            q = rand();
        while (q % 2 == 0);
    } while (!PrimarityTest(2, q));

    n = p * q;
    phi_n = (p - 1) * (q - 1);

    do
        e = rand() % (phi_n - 2) + 2; // 1 < e < phi_n
    while (gcd(e, phi_n) != 1);

    d = inverse(phi_n, e);
    return d;
}

char* Encryption(const char* input)
{
    KeyGeneration();

    int inputLength = strlen(input);
    int maxCipherLength = (inputLength * 6) + 1;  // Максимальная длина зашифрованной строки с учетом пробелов и завершающего символа '\0'
    char* cipher = (char*)malloc(maxCipherLength * sizeof(char));  // Выделяем память для зашифрованной строки
    cipher[0] = '\0';  // Обнуляем строку перед использованием strcat()

    for (int i = 0; i < inputLength; i++)
    {
        int value = input[i];
        int encrypted = FindT(value, e, n);  // Используем функцию FindT() для шифрования
        char temp[12];  // Устанавливаем достаточный размер буфера
        sprintf(temp, "%d ", encrypted);  // Преобразуем зашифрованное число в строку
        strcat(cipher, temp);
    }
    char occurrence = '-';
    int occurrenceIndex = -1;
    int i = 0;
    while (cipher[i] != '\0') {
        if (cipher[i] == occurrence) {
            occurrenceIndex = i;
            break;
        }
        i++;
    }
    if (occurrenceIndex != -1) {
        cipher[occurrenceIndex] = '\0';
    }

    return cipher;
}