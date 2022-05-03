# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>

# define N 4
# define stlen 40
// declaring the used functions.
void letter_appear(char* str, int str_len, int* monim);
int str_length(char* str);
void printing(char* str, int* monim);
// main function.
int main() {
	// declaring a string with length of 40
	char str[stlen];
	printf("Enter a string with max length of %d with a \'!\' in the end: ",stlen );
	// getting the string from the user.
	scanf("%s", str);
	// declaring the string length.
	int str_len = str_length(str);
	// declaring an array representing the number of appearances of each lowercase english letter.
	int* monim[26] = { 0 };
	letter_appear(str, str_len, monim);
	// printing the diagram for the letters.
	printing(str, monim);
	return 0;
}
// counting the number of appearances for each letter.
void letter_appear(char* str, int str_len, int* monim) {
	for (int i = 0; i < str_len; i++) {
		if(str[i] >= 97 && str[i] <= 122){
			monim[str[i] - 'a'] += 1;
		}
	}
}
// calculating the length of the string.
int str_length(char* str) {
	int counter = 0;
	int i = 0;
	char let;
	while (str[i] != '!') {
		let = str[i];
		counter += 1;
		i += 1;
	}
	return counter;
}
// printing the diagram of letter appearances.
void printing(char* str, int* monim) {
	char letter = 'a';
	for (int j = 0; j < N; j++) {
		printf("%c: ", letter + j);
		for (int k = 0; k < *(monim + j); k++) {
			printf("*");
		}
		printf("\n");
	}
}
