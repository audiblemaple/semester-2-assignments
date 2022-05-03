#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define N 8
// declaring the used functions.
int neg_appearance(int* arr, int length);
int is_zero(int* arr, int length);
// main function.
int main()
{
	// declaring 2 counters that whould store the consecutive appearances of negative numbers,
	// then assigning the value to the second counter and each time comparing
	// if the last row is bigger than the current biggest.
	int max_count1 = 0, max_count2 = 0, j;
	int arr[N];
	int flag = 1;
	while (flag == 1)
	{
		// asking the user to enter an array of numbers.
		printf("Enter the array: ");
		for (j = 0; j < N; j++)
			scanf("%d", &arr[j]);
		// checking if the array is filled with zeros.
		flag = is_zero(arr, N);
		// if the array is not filled with zeros we count the largest consecutive negative number appearances.
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
	// printing the maximal negative appearance number.
	printf("Maximal negative sequence is: %d", max_count1);
	return 0;
}
// a function that checks if the array is filled with zeros.
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
// a function that counts the appearances of negative numbers and returns the largest.
int neg_appearance(int* arr, int length)
{
	// declaring 2 counters.
	int count_1 = 0, count_2 = 0;
	// in a loop counting the consecutive negative appearances
	for (int i = 0; i < length; i++)
	{
		if (arr[i] < 0)
		{
			count_2 += 1;
		}
		else {
			// if a negative sequence ended (or never started) we compare the 2 counters and assign the larger value to count_1.
			if (count_2 > count_1) {
				count_1 = count_2;
				count_2 = 0;
			}
			else {
				// reseting counter_ 2 for more potential sequences.
				count_2 = 0;
			}
		}
	}
	// returning the largest number of negative number appearances
	return count_1;
}

/*arr{ 13,4124,-1412,-4124,-241,-4124,412 };

max_count_1 = neg_appearance()
arr{-1,-224,-2412,-4124,-22,-4122,-4 };

max_count_2 = */