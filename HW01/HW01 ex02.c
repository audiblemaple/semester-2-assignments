# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>

#define N 4
// declaring the used functions.
void printarray(long* array);
void buildNum(int* num, int firstNum);
void leftCircularShift(long* array, int len);
int getFirstDigit(int num);
// the main function.
int main() {
	// declaring the array and calculating its length.
	long array[N] = {123, 4, 56789, 402};
	int len = sizeof(array) / sizeof(array[0]);
	// printing the array before doing any changes to it.
	printf("Before \"left circular shift\": ");
	printarray(array);
	// left circular shifting the array.
	leftCircularShift(array, len);
	// printing the array after the left circular shift.
	printf("After \"left circular shift\": ");
	printarray(array);
	return 0;
}
// a function that prints the array.
void printarray(long* array) {
	for (int i = 0; i < N; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}
// a function that gets the leftmost digit from a given number.
int getFirstDigit(int num) {
	while (num > 10) {
		num /= 10;
	}
	return num;
}
// a function that gets the "next" number in the array multiplies it by 10 and
// adds the first number from the "previous number".
void buildNum(int* num, int firstNum) {  
	*num *= 10;
	*num += firstNum;
}

// a function that makes the left circular shift.
void leftCircularShift(long* array, int len) {
	// we send each index in the array to the get first digit function,
	// then we send the "next" number in the array, along with the first digit that we got
	// to the build number function.
	for (int i = 0; i < len - 1; i++) {
		int firstDig = getFirstDigit(*(array + len  - (i + 1)));
		buildNum((array + len - (i + 2)), firstDig);
		if (len - (i + 2) == 0) {
			int firstDig = getFirstDigit(*(array + len - (i + 2)));
			buildNum((array + len - 1), firstDig);
		}
	}
	// at this point we have the array shifted BUT the leftmost numbers still remain,
	// so we need to remove them.
	// for each index in the array we count the number of its digits,
	// calculating 10 to the power of the number of digits, 
	// multiply the leftmost number by the product of the power of 10,
	// and subtract what we got from the number in the array.
	for (int j = 0; j < len; j++) {
		int index = *(array + j);
		int counter = 0;
		while (index > 10) {
			counter += 1;
			index /= 10;
		}
		for (int k = 0; k < counter; k++) {
			index *= 10;
		}
		*(array + j) -= index;
		continue;
	}
}

// the left circular shift works great but the left digit REMAIN
// so we just need to figure out where to put the next piece of code to remove the numebrs
/*
	int num_copy = *num;
	int counter = 0;
	int removerNum = 1;
	while (num_copy > 10) {
		counter += 1;
		num_copy /= 10;
	}
	for (int j = 0; j < counter; j++) {
		removerNum *= 10;
	}

	num_copy *= removerNum;
	*num -= num_copy;
*/
// this piece of code duplicates the number and counts the digits of the number,
// then it raises the number 10 to the power of the digits, multiplies it by the number left most digit
// and then subtracts the result from the original number.
// EXAMPLE:  4567  has 4 digits so its 10 to the 3rd power
//				   1000 * 4 = 4000,    4567 - 4000 = 567





// this piece of code is old, dont pay attention.
/*
void buildNum(int* num, int firstNum) {  // also we can count the number of digits in the number and multiply it by 10 to the power of digits then multiply by first digit and add the array number.
	int reverse = 0;
	while (*num > 10) {
		reverse += (*num % 10);
		reverse *= 10;
		*num /= 10;
	}
	*num = 0;
	printf("%d", reverse);
	reverse * 10;
	reverse += firstNum;
	
	while (reverse > 10) {
		*num += reverse % 10;
		reverse / 10;
	}
}
*/