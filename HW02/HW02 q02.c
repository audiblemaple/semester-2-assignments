#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// declaring the used functions.
struct RationalNum calculateRational(struct RationalNum* NumArray, int len);
void PrintSum(struct RationalNum* NumArray, struct RationalNum sum, int len);
// declaring the structure for the number.
struct RationalNum {
	int mone;
	int mehane;
};
// main function.
int main() {
	// declaring the structure array and the used variables.
	struct RationalNum* NumArray;
	int counter = 1;
	NumArray = (struct RationalNum*)malloc(counter * sizeof(struct RationalNum));  /// add a check if the allocation has failed.
	printf("Enter fractions by pairs of integers (0 0 to finish):");
	printf("\n%d (mone mehane): ", counter);
	scanf("%d %d", &NumArray[counter -1].mone, &NumArray[counter - 1].mehane);
	int flg = 0;
	// checking if the input is 0 0.
	if ((NumArray[counter - 1].mone == 0) && (NumArray[counter - 1].mehane == 0)) {
		flg = 1;
	}
	// here we get the numbers of the user until the last number is 0 0.
	while (flg == 0){
		// also we check if the user divides by zero and give them the cance to choose another number.
		while (NumArray[counter - 1].mehane == 0){
			printf("Can't divide by zero, choose another number: ");
			scanf("%d", &NumArray[counter - 1].mehane);
		}
		counter += 1;
		// each time we increase the lenght of the array by 1 until the input is 0 0.
		NumArray = realloc(NumArray, counter * sizeof(struct RationalNum));
		if (NumArray == NULL) {
			printf("Memory reallocation error.");
			free(NumArray);
			exit(1);
		}
		printf("%d (mone mehane): ", counter);
		scanf("%d %d", &NumArray[counter - 1].mone, &NumArray[counter - 1].mehane);
		// checking if the input is 0 0 again.
		if ((NumArray[counter - 1].mone == 0) && (NumArray[counter - 1].mehane == 0)) {
			flg = 1;
		}
	}
	// declaring the sum of the numbers in the array.
	struct RationalNum sum = calculateRational(NumArray, counter);
	// printing the sum of the numbers that the user chose.
	PrintSum(NumArray, sum, counter);
	// freeing up the space we allocated for the NumArray before quitting.
	free(NumArray);
}

// a function that calculates the sum of all the numbers in the array,
// accurding to the structures variable name.
struct RationalNum calculateRational(struct RationalNum* NumArray, int len) {
	struct RationalNum sum;
	sum.mone = NumArray[0].mone;
	sum.mehane = NumArray[0].mehane;
	// int common;
	for (int i = 1; i < len - 1; i++) {
		// calculating all the mone numbers.
		// calculating all the mehane variables.
		sum.mone = (sum.mone * NumArray[i].mehane) + (sum.mehane * NumArray[i].mone);
		sum.mehane = sum.mehane * NumArray[i].mehane;
	}

	// returning the structure with the sum.
	return sum;
}

//a function that prints the sum of the numbers.
void PrintSum(struct RationalNum* NumArray,  struct RationalNum sum, int len) {
	// these variables will be used if mone > mehane.
	int whole, mehane, mone;
	double check_mone , check_mehane, check_whole;
	// this variable will help us to minimize the fraction.
	int denominator;
	
	// printing all the numbers in the according order.
	for (int i = 0; i < len - 1; i++) {
		if (i != len - 2) {
			printf("%d/%d+", NumArray[i].mone, NumArray[i].mehane);
		}
		if (i == len - 2) {
			printf("%d/%d=", NumArray[i].mone, NumArray[i].mehane);
		}
	}
	// checking if the number composes a 1 then we print it.
	if (sum.mone == sum.mehane) {
		whole = sum.mone / sum.mehane;
		denominator = sum.mone;
		while (denominator > 1) {
			if (sum.mone % denominator == 0 && sum.mehane % denominator == 0) {
				break;
			}
			denominator -= 1;
		}
		printf("%d/%d=%d", sum.mone / denominator, sum.mehane / denominator, whole);
	}
	// checking if the sum mone is bigger than the sum mehane.
	// if yes then we print the whole number and the fraction left.
	if (sum.mone > sum.mehane) {
		////// variables for checking if the fraction is whole //////
		check_mone = sum.mone;
		check_mehane = sum.mehane;
		check_whole = check_mone / check_mehane;
		whole = sum.mone / sum.mehane;
		mone = (sum.mone - (sum.mehane * whole));
		mehane = sum.mehane;
		int denominator = mone;
		//////////////////////////////////////////////////////////////
		// if the fraction is whole then we print its value.
		if (check_whole == whole) {
			printf("%d/%d=%d", sum.mone, sum.mehane, whole);
		}
		// if the fraction is not whole then we minimize the fractions using the common DENOMINATOR.
		else {
			while (denominator > 1) {
				if (mone % denominator == 0 && mehane % denominator == 0) {
					break;
				}
				denominator -= 1;
			}
			mone /= denominator;
			mehane /= denominator;
			printf("%d/%d=%d and %d/%d", sum.mone / denominator, sum.mehane / denominator, whole, mone, mehane);
		}
	}

	// if mone is smaller than the mehane then we simplify the fraction numbers so that we get the smallest possible fraction.
	// we do that by finding the commom DENOMINATOR.
	if (sum.mone < sum.mehane) {
		denominator = sum.mone;
		while (denominator > 1) {
			if (sum.mone % denominator == 0 && sum.mehane % denominator == 0) {
				break;
			}
			denominator -= 1;
		}
		printf("%d/%d", sum.mone / denominator, sum.mehane / denominator);
	}
}



/*	for (int i = 1; i < len -1; i++) {
		if (sum.mehane == NumArray[i].mehane) {
			sum.mone += NumArray[i].mone;
			continue;
		}
		// a case that the right number is smaller then the left one but they have a common denominator
		if (sum.mehane % NumArray[i].mehane == 0) {
			common = abs(sum.mehane);
			while (common > 1) {
				if (NumArray[i].mehane * common == sum.mehane) {
					NumArray[i].mone *= common;
					NumArray[i].mehane *= common;
					break;
				}
				common -= 1;
			}
		}
		if (NumArray[i].mehane % sum.mehane == 0) {
			common = abs(NumArray[i].mehane);
			while (common > 1) {
				if (sum.mehane * common == NumArray[i].mehane) {
					sum.mone *= common;
					sum.mehane *= common;
					break;
				}
				common -= 1;
			}
		}
		if (sum.mehane == NumArray[i].mehane) {
			sum.mone += NumArray[i].mone;
			continue;
		}
		else {
			sum.mone = (sum.mone * NumArray[i].mehane) + (sum.mehane * NumArray[i].mone);
			sum.mehane *= NumArray[i].mehane;
		}
	}*/