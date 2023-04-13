#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


bool isDataTrue(int *a, int *n)
{
	if ((*n < 3) || (*a < 0) || (*a >= *n))
	{
		return false;
	}

	return true;
}

bool isEven(int *k)
{
	if (*k % 2 == 0)
	{
		return true;
	}

	return false;
}

int sSolve(int* n)
{
	if ((*n % 8 == 1) || (*n % 8 == -1))
	{
		return -1;
	}
	else if ((*n % 8 == 3) || (*n % 8 == 5))
	{
		return 1;
	}
}

bool isModule(int *a, int *n)
{
	if ((*n % 4 == 3) && (*a % 4 == 5))
	{
		return true;
	}
	return false;
}


int main()
{
	int n, a, g, k, s, a_1;
	int *pn, *pa, *pk;
	bool isSolving, isEv, isMod;

	printf("\n%s", "Input a ");
	scanf("%d", &a);
	printf("\n%s", "Input n ");
	scanf("%d", &n);

	pn = &n;
	pa = &a;
	g = 1;

	isSolving = isDataTrue(pa, pn);
	if (isSolving == false)
	{
		printf("%s", "\nYour data is weak!");
		return 0;
	}

	while (true){
		if (*pa == 0)
		{
			printf("\n(a/n) = %d", 0);
			break;
		}
		else if (*pa == 1)
		{
			printf("\n(a/n) = g = %d", 1);
			break;
		}
		k = 0;
		pk = &k;
		a_1 = a;
		while (a_1 % 2 == 0)
		{
			k++;
			a_1 /= 2;
		}
		isEv = isEven(pk);
		if (isEv == true)
		{
			s = 1;
		}
		else 
		{
			s = sSolve(pn);
		}
		if (a_1 == 1)
		{
			printf("\n(a/n) = g*s = %d", g * s);
			break;
		}
		isMod = isModule(pa, pn);
		if (isMod == true)
		{
			printf("\n(a/n) = -s = %d", s*-1);
		}
		a = n % a_1;
		n = a_1;
		g = g * s;
	}
	
	return 0;
}
