#include <stdio.h>
#include <stdlib.h>
#include <time.h>
Randomized_Partition(int * A, int p, int r)
{
	srand(time(NULL));
	int i = p + (rand() % (r-p));

	swap(A, i, r);
	return Partition(A, p, r);

}

Randomized_Quicksort(int * A, int p, int r)
{
	if (p < r)
	{
		int q = Randomized_Partition(A, p, r);
		Randomized_Quicksort(A, p, q - 1);
		Randomized_Quicksort(A, q + 1, r);
	}
}


int totalcnt = 0;
Partition(int * A, int p, int r)
{
	int x = A[r];
	printf("현재 피봇은 %d\n", A[r]);
	int i = p - 1;

	int count = 0;
	for (int j = p; j < r; j++)
	{
		if (A[j] <= x)
		{
			i = i + 1;
			swap(A, i, j);
		}
		count++;
	}
	printf("이번 반복 횟수는 %d\n", count);
	totalcnt += count;
	swap(A, i + 1, r);
	return i + 1;
}

swap(int * A, int i, int j)
{
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

int main()
{
	int A[5][20] = {{ 3, 7, 4, 35, 24, 26, 21, 41, 23, 8, 10, 11, 74, 33, 38, 1, 17, 29, 89, 20 },
					{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
					{ 4, 7, 11, 13, 29, 31, 1, 94, 32, 74, 69, 15, 8, 20, 39, 41, 54, 5, 83, 3},
					{ 8, 41, 32, 52, 15, 17, 113, 42, 1, 9, 23,12, 73, 72, 19, 13, 72, 90, 91, 94},
					{ 31, 42, 32, 53, 4, 6, 9, 2, 7, 25, 63, 21, 36, 39, 20, 10, 14, 17, 83, 30} };

	for (int i = 0; i < 5; i++)
	{
		totalcnt = 0;
		Randomized_Quicksort(A[i], 0, 19);
		for (int j = 0; j < 20; j++)
		{
			printf("%d ", A[i][j]);
		}
		printf("\n");
		printf("전체 반복횟수는 : %d\n", totalcnt);
	}
	return 0;
}