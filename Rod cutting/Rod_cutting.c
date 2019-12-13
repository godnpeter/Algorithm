#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define max(a,b) ((a)>(b)) ? (a) : (b)

typedef struct pointer {
	int *r;
	int *s;
}pointers;

pointers extendedbottomupcutrod(int *p, int n)
{
	int * r = malloc(sizeof(int)*(n + 1));
	int * s = malloc(sizeof(int)*(n + 1));
	r[0] = 0;
	for (int j = 1; j < n + 1; j++)
	{
		int q = -100000;
		for (int i = 1; i < j + 1; i++)
		{
			if (q < p[i] + r[j - i])
			{
				q = p[i] + r[j - i];
				s[j] = i;
			}
		}
		r[j] = q;
	}
	pointers pl;
	pl.r = r;
	pl.s = s;
	return pl;
}

void printcutrodsolution(int *p, int n)
{
	pointers pls = extendedbottomupcutrod(p, n);
	while (n > 0)
	{
		printf("%d\n", pls.s[n]);
		n = n - pls.s[n];
	}
}

int memoizedcutrod(int* p, int n)
{
	int * r = malloc(sizeof(int) * (n + 1));
	for (int i = 0; i < n + 1; i++)
	{
		r[i] = -10000;
	}

	return memoizedcutrodaux(p, n, r);
}
int memoizedcutrodaux(int * p, int n, int * r)
{
	int q;
	if (r[n] >= 0)
	{
		return r[n];
	}

	if (n == 0)
	{
		q = 0;
	}
	else
	{
		q = -100000;
		for (int i = 1; i < n + 1; i++)
		{
			q = max(q, p[i] + memoizedcutrodaux(p, n - i, r));
			
		}

	}


	r[n] = q;
	return q;

}
int main()
{
	int size;
	scanf("%d", &size);
	int price[11];
	for (int i = 1; i < 11; i++)
	{
		scanf("%d", &price[i]);
	}
	int q = memoizedcutrod(price, size);
	printf("%d\n", q);
	printcutrodsolution(price, size);
	return 0;
}