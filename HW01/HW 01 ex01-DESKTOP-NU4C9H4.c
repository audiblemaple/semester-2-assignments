#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define N 8

int neg_appearance(int* arr, int length);
int is_zero(int* arr, int length);

int main()
{
	int max_count1 = 0, max_count2 = 0, j;
	int arr[N];
	int flag = 1;
	while (flag == 1)
	{
		printf("Enter the array: ");
		for (j = 0; j < N; j++)
			scanf("%d", &arr[j]);
		flag = is_zero(arr, N);

		if (flag != 0)
		{
			max_count2 = neg_appearance(arr, N);

			if (max_count2 > max_count1)
			{
				max_count1 = max_count2;
				max_count2 = 0;
			}
		}
	}
	printf("Maximal negative sequence is: %d", max_count1);
	return 0;
}

int is_zero(int* arr, int length)
{
	int flg = 0;
	for (int i = 0; i < length; i++) {
		if (arr[i] != 0) {
			flg = 1;
		}
	}
	return flg;
}

int neg_appearance(int* arr, int length)
{
	int count_1 = 0, count_2 = 0;

	for (int i = 0; i < length; i++)//        {-13,4124,-1412,-4124,-241,-4124,412}
	{
		if (arr[i] < 0)
		{
			count_2 += 1;
		}
		else {
			if (count_2 > count_1) {
				count_1 = count_2;
				count_2 = 0;
			}
			else {
				count_2 = 0;
			}
		}
	}
	return count_1;
}

/*arr{ 13,4124,-1412,-4124,-241,-4124,412 };

max_count_1 = neg_appearance()
arr{-1,-224,-2412,-4124,-22,-4122,-4 };

max_count_2 = */