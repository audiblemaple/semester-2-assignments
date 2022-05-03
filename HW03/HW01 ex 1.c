#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>
// Declaring the needed structures.
typedef struct {
	char* name;
	long ID;
	float grade;
	char handle[5];
	char final;
}student;

typedef struct {
	student* stud;
}university;
// Declaring the used fuctions.
struct student* get_input(FILE* f_ptr, int* len);
int hand_calc(student stud, int len);
float final_calc(student stud);
void print_2(university uni, int len, FILE* f_out);
// Main function with the menu.
int main() {
	FILE* f_in = fopen("files\\input.txt", "r");
	FILE* f_out = fopen("files\\output.txt", "w");
	university uni;
	int len = 0, i;
	if (f_in == NULL || f_out == NULL){
		printf("Error opening file.");
		exit(1);
	}
	int choice, flg = 0, trigger = 0;
	printf("Choose a number between 1-6:\n");
	printf("first you need to get input (option 1), also you need to do this only once: ");
	if (scanf("%d", &choice) != 1)
		printf("Error getting input.");
	while (choice != 6) {
		// if chioce is out of bounds.
		if (choice < 1 || choice > 6)
			printf("Wrong number chosen.\n");
		// if choice 1 was chosen more than once.
		if (choice == 1 && flg == 1) {
			printf("Can't choose first option more than once, please choose another option: ");}
		// the first option that will start the process will be 1 so every number
		// not equal to 1 we will just ignore and print an according message.
		if (choice != 1 && flg == 0) {
			printf("You first need to choose option 1.\n");
		}
		// if chioce 1 we is chosen for the first time it does its job.
		if (choice == 1 && flg == 0) {
			uni.stud = get_input(f_in, &len);
			flg = 1;
			trigger = 1;
			fprintf(f_out,"option 1: \nData from input file copied to university struct successfully.");
			fclose(f_in);
		}
		// choice 2 prints the data to a file.
		if (choice == 2 && trigger == 1) {
			fprintf(f_out, "\nOption 2: \n");
			print_2(uni, len, f_out);
		}
		// choice 3 does the same as 2 but with final grades.
		if (choice == 3 && trigger == 1) {
			float final = 0;
			fprintf(f_out, "\nOption 3: \nBefore: \n");
			print_2(uni, len, f_out);
			fprintf(f_out, "\nAfter: \n");
			for (i = 0; i < len; i++) {
				final = final_calc(uni.stud[i], len, f_out);
				fprintf(f_out, "student %d %s %ld %0.2f %c final: %0.2f\n", i + 1, uni.stud[i].name, uni.stud[i].ID, uni.stud[i].grade, uni.stud[i].final, final);
			}
		}
		// choice 4 prints the statistical data to a file. 
		if (choice == 4 && trigger == 1) {
			float average = 0, min = 100, grade_temp = 0, max = 0;
			double deviation = 0, dev_temp = 0, final = 0;
			for (i = 0; i < len; i++) {
				if (min > uni.stud[i].grade);
					min = uni.stud[i].grade;
				if (max < uni.stud[i].grade)
					max = uni.stud[i].grade;
				average += uni.stud[i].grade;
			}
			average /= len;
			for (i = 0; i < len; i++) {
				final = uni.stud[i].grade;
				dev_temp += pow(final - average, 2);
			}
			deviation =  sqrt(dev_temp / len);
			fprintf(f_out,"\nOption 4: \n");
			fprintf(f_out, "Average: %0.2f \nStandard deviation: %0.2lf \nNumber of students: %d \nRange: %0.2f - %0.2f \n", average, deviation, len, max, min);
		}
		// choice 5 prints the data of students whom grades are above average.
		if (choice == 5 && trigger == 1) {
			float average = 0;
			fprintf(f_out, "\nOption 5: \n");
			for (i = 0; i < len; i++) {
				average += uni.stud[i].grade;
			}
			average /= len;
			for (i = 0; i < len; i++) {
				if (uni.stud[i].grade >= average){
					fprintf(f_out, "%s %ld\n", uni.stud[i].name, uni.stud[i].ID);
				}
			}
		}
		// here if choice is 6 we end the loop, free the students array and print end of program.
		printf("choose options 2-6 (6 to exit): ");
		if (scanf("%d", &choice) != 1)
			printf("Error getting input.");
	}
	free(uni.stud);
	fprintf(f_out, "\nEnd Of Program.");
	return 0;
}
// A function that gets the input from the file into the student array inside the university structure.
// 1. we dinamically allocate space for the students name, and the array size.
// 2. we check if the allocations went well.
// 3. we count the length of the array and assign the value of counter to the length so we can work with it later.
// 4. returning the array.
struct student* get_input(FILE* f_ptr, int* len){
	int i = 0, counter = 1;
	char str[99];
	student* arr;
		arr = (student*)malloc(sizeof(student));
		if (arr == NULL) {
			printf("Error allocating memory");
			free(arr);
			exit(1);
		}
		while (1){
			fscanf(f_ptr, "%s", &str);
			arr[i].name = (char*)malloc(sizeof(strlen(str)));
			if (arr[i].name == NULL) {
				printf("Error allocating memory");
				free(arr);
				exit(1);
			}
			strcpy(arr[i].name, str);
			if (fscanf(f_ptr, "%ld %f %s", &arr[i].ID, &arr[i].grade, arr[i].handle) == EOF) {
				break;
			}
			counter += 1;
			arr = (student*)realloc(arr, sizeof(student) * (counter + 1));
			if (arr == NULL) {
				printf("Error reallocating memory.");
				free(arr);
				exit(1);
			}
			i += 1;
			*(len) = counter -1;
		}
		return arr;
}
// A function that calculates the 1's and 0's from the handed assignments and gives a grade of 0 or 1
// if the student handed more than 3 assignments.
int hand_calc(student stud, int len) {
	int i, hand[2] = {0};
	char ret = 0;
	for (i = 0; i < 5; i++) {
		if (stud.handle[i] == 49)
			hand[1] += 1;
	}
	if (hand[1] >= 3)
		ret = 49;
	else
		ret = 48;
	return ret;
}
// A function that calculates the final grade according to the hand grade(1 or 0).
float final_calc(student stud) {
	if (stud.final != '1' || stud.grade < 55)
		return stud.grade;
	return (stud.grade * 0.85) + 15;
}
// A function that prints the name, ID, grade, and hand grade of each student.
// this function was written with the purpose of not duplicating code in options 2 and 3.
void print_2(university uni, int len, FILE* f_out) {
	char temp;
	int i;
	for (i = 0; i < len; i++) {
		uni.stud[i].final = hand_calc(uni.stud[i], len);
		fprintf(f_out, "student %d %s %ld %0.2f %c\n", i + 1, uni.stud[i].name, uni.stud[i].ID, uni.stud[i].grade, uni.stud[i].final);
	}
}