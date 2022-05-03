#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>  // maybe needs deleting
// defining the array length.
#define N 3
// declaring the structure.
struct category {
	char* code;
	char* name;
	int sales;
};
// declaring the used functions.
void get_input(struct category* categ);
void best_worst(struct category** ptArray);
void print_best_worst(struct category** ptArray);
// main function.
int main() {
	int i = 0;
	// declaring the structure array.
	struct category catArray[N];
	// calling get input to get input from the user.
	get_input(&catArray);
	// declaring an array of pointers of type category*.
	struct category **ptArray[N];
	// assigning the adressed of the structures from catArray to ptArray with matching indices.
	// 0 to 0, 1 to 1, 2 to 2, etc..
	for (i; i < N; i++) {
		ptArray[i] = &catArray[i];
	}
	// calling best worst function to find the best  and worst selling category
	// and put the pointers in the first and second places in the POINTER array. 
	best_worst(ptArray);
	// calling the print best worst function to print the according messages.
	print_best_worst(ptArray);
}
// get input function.
void get_input(struct category* categ) {
	int i = 0, j = 0;
	// a loop to get each index in the original array.
	for (i; i < N; i++) {
		printf("Enter category %d data: \n", i + 1);
		char str_code[10];
		char str_name[20];

		// asking for the category code.
		printf("Enter the category code: ");
		scanf("%s", &str_code);

		// allocating memory for the code string.
		categ[i].code = (char*)malloc(sizeof(strlen(str_code)));
		
		// asking for the category name.
		printf("Enter the category name: ");
		scanf("%s", &str_name);

		// allocating memory for the category name string.
		categ[i].name = (char*)malloc(sizeof(strlen(str_name) + 1));
		// checking if the memory for the 2 strings was allocated correctly.
		if (categ[i].name == NULL || categ[i].code == NULL){
			// if not, printing a message, freeing up all the allocated memory and exiting with code 1.
			printf("Not enough memory.");
			for (j; j < i; j++) {
				free(categ[i].name);
				free(categ[i].code);
				free(categ);
				exit(1);
			}
		}
		// inserting the strings from the user into code and name.
		strcpy(categ[i].code, str_code);
		strcpy(categ[i].name, str_name);
		// asking for the number of sales.
		printf("Enter the number of sales today: ");
		scanf("%d", &categ[i].sales);
		printf("\n");
	}
}
// best worst function finds the best and worst selling categories and places the best and worst 
// categories in first and second place in the POINTER array.
void best_worst(struct category** ptArray) {
	// declaring the used variables.
	int i = 0, best_index, worst_index;
	int best_sale = 0,temp, worst_sale = ptArray[0]-> sales;
	struct category *best_cat, *temp_cat, *worst_cat;
	// a loop in which we check if temp is the biggest current number of sales or the smallest.
	for (i; i < N; i++) {
		temp = ptArray[i]-> sales;
		// checking for biggest.
		if (temp > best_sale) {
			best_sale = temp;
			best_index = i;
		}
		// checking for smallest.
		if (temp <= worst_sale) {
			worst_sale = temp;
			worst_index = i;
		}
	}
	// placing the best and worst pointers in first and second place of the POINTER array.
	best_cat = ptArray[best_index];  
	worst_cat = ptArray[worst_index];

	temp_cat = ptArray[0];
	ptArray[0] = best_cat;
	ptArray[best_index] = temp_cat;

	temp_cat = ptArray[1];
	ptArray[1] = worst_cat;
	ptArray[worst_index] = temp_cat;

}
// print best worst is a function that prints the according message.
void print_best_worst(struct category** ptArray) {
	printf("The best selling category is code: %s, name: %s, with %d sales.", ptArray[0]->code, ptArray[0]->name, ptArray[0]->sales);
	printf("\nThe worst selling category is code: %s, name: %s, with %d sales.", ptArray[1]->code, ptArray[1]->name, ptArray[1]->sales);
}


/*
	// placing the best and worst pointers in first and second place of the POINTER array.
	best_cat = ptArray[best_index];
	worst_cat = ptArray[worst_index];
	temp_cat_1 = ptArray[0];
	temp_cat_2 = ptArray[1];
	ptArray[0] = best_cat;                         // <------ here i can probably simplify...
	ptArray[1] = worst_cat;
	ptArray[best_index] = temp_cat_1;
	ptArray[worst_index] = temp_cat_2;
*/