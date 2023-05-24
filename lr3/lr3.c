#include <stdio.h>

int extended_gcd(int a, int b, int *x, int *y)
{
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
 
    int _x, _y;
    int gcd = extended_gcd(b % a, a, &_x, &_y);
 
    *x = _y - (b/a) * _x;
    *y = _x;
 
    return gcd;
}

int modexp(int x, int y, int N)
{
	if (y == 0) return 1;
	int z = modexp(x, y / 2, N);
	if ((y % 2) == 0)
		return (z*z) % N;
	else
		return (x*z*z) % N;
}

int modinv(int a, int m)
{
	int x, y;
	int g = extended_gcd(a, m, &x, &y);
	
	if (g != 1)
		return -1;
	else 
	{
		x = (x % m + m) % m;
		return(x);
	}
}

int modmult(int a, int b, int m)
{
	int res = 0;  

	a %= m;
 
	while (b)
	{
		if (b & 1)
			res = (res + a) % m;
 
		a = (2 * a) % m;
 		b >>= 1; 
	}
 
	return res;
}

int main()
{
	int p, a, n;
	printf("Enter p: "); 
	scanf("%d", &p);
	printf("Enter a: ");
	scanf("%d", &a);
	printf("Enter n: ");
	scanf("%d", &n);
	
	int k, h = p - 1;
	while ((h % 2) == 0)
	{
		h /= 2;
		k++;
	}
	
	int a_1 = modexp(a, (h+1)/2, p), n_1 = modexp(n, h, p);
	int a_2 = modinv(a, p);
	int n_2 = 1, j = 0;
	
	for (int i = 0; i <= k - 2; i++)
	{
		int b = modmult(a_1, n_2, p);
		int c = modmult(a_2, b, p);
		c = modmult(c, b, p);
		
		int d = modexp(2, k - 2 - i, p);
		d = modexp(c, d, p);
		
		if (d == 1)
			j = 0;
		else if (d == p - 1)
			j = 1;
		
		int temp = modexp(2, i, p);
		temp = modexp(n_1, temp*j, p);
		n_2 = modmult(n_2, temp, p); 
	}
	
	int res = modmult(a_1, n_2, p);
	printf("x: %d and %d\n", res, -res);
	return 0;
}	
