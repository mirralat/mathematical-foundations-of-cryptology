#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int gcd(int a, int b);
int PrimarityTest(int a, int i);
int FindT(int a, int m, int n);
int FastExponention(int bit, int n, int* y, int* a);
int inverse(int a, int b);
int KeyGeneration();
char* Encryption(const char* input);
