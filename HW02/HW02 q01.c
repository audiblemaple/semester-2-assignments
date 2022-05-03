#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
// defining the constant used variables.
#define N 5
#define M 6
#define drivers 10
// declaring the used functions.
void print_msg(int bus[N][M],int zero_cnt[N], int drive_cnt[N][drivers], int drive_seq[drivers], int flgs[3]);
void seek_error(int bus[N][M], int* zero_cnt, int drive_cnt[][drivers], int* drive_seq, int* flgs);
// main function for declaring variables and calling functions.
int main() {
	// declaring the schedule matrix.
	int bus[N][M] = { {6, 3, 8, 0, 0, 5}
				     ,{6, 6, 5, 7, 8, 4}
			 	     ,{4, 5, 6, 6, 1, 7}
			 	     ,{0, 4, 6, 2, 5, 0}
				     ,{0, 8, 7, 3, 2, 8} };

	/*
			int bus[N][M] = { {6, 3, 8, 0, 0, 5}
						 ,{6, 6, 5, 7, 8, 4}
						 ,{4, 5, 6, 6, 1, 7}
						 ,{0, 4, 3, 2, 5, 0}
						 ,{0, 8, 7, 3, 2, 8} }; 
	
	*/

	// declaring the variables that will help us count the needed errors.
	int zero_cnt[N] = { 0 };
	int drive_cnt[N][drivers] = { 0 };
	int drive_seq[drivers] = { 0 };
	// declaring the flags array to see if any of the errors exist.
	int flgs[3] = { 0 };
	// calling the used functions.
	seek_error(bus, zero_cnt, drive_cnt, drive_seq, flgs);
	print_msg(bus, zero_cnt, drive_cnt, drive_seq, flgs);
}
// a function that finds the neede errors.
void seek_error(int bus[N][M], int* zero_cnt, int drive_cnt[][drivers], int* drive_seq, int* flgs) {
	// declaring the used variables
	int i, j, k, count_zr, count_dr;
	// a nested loop that checks if:
	// 1. there are zeros near each other.
	// 2. there are drivers that scheduled to the same station in the same time.
	// 3. there are drivers that drive 3 hours in a row.
	for (i = 0; i < N; i++) {
		count_zr = 0;
		for (j = 0; j < M; j++) {
			// calculating the number of zeros.
			if (bus[i][j] == 0) {
				count_zr += 1;
			}
			// if the counter is bigger than the current number in the counter array then we assign the value of the counter.
			else if (count_zr > zero_cnt[i]){
				zero_cnt[i] = count_zr;
				count_zr = 0;
			}
			// if there is at leas 2 zeros near each other then we "raise" the flag.
			if (count_zr > 1) {
				*(flgs) = 1;
			}
			// calculating the drivers that are assigned to different stations at the same time.
			// for this we whould have to go over each column (hour) and check which driver was assigned there.
			if (j < N && i < N) {
				*(*(drive_cnt + i) + bus[j][i]) += 1;
				// if there is at least 1 driver that was assigned to different stations at the same time,
				// we "raise" the flag again.
				if (*(*(drive_cnt + i) + bus[j][i]) > 1 && (i + bus[j][i] != 0)) {
					*(flgs + 1) = 1;
				}
			}
		}
		// here we assign the counter value to the counter array in case we exited the loop and didnt
		// have the chance to assign it(the zeros were in the M'th place).
		if (count_zr > zero_cnt[i]) {
			zero_cnt[i] = count_zr;
		}
	}
	// counting the drivers that drive 3 hours in a row.
	// a loop for each number from 1 to drivers.
	for (i = 1; i < drivers; i++) {
		// resetting counter.
		count_dr = 0;
		// nested loop for each columns and rows.
		for (j = 0; j < M; j++) {
			for (k = 0; k < N; k++) {
				// if the counter is bigger than 2 we can break to the end of both loops because we already found what we wanted.
				if (count_dr > 2) {
					break;
				}
				// if the driver number is equals to the number we are currently searching then we increment the counter.
				if (bus[k][j] == i) {
					count_dr += 1;
					break;
				}
				// if we got to the end of the line and there were no matches then we reset the counter.
				if (k == N-1 && bus[k][j] != i) {
					count_dr = 0;
				}
			}
		}
		// if the dounter is bigger than 2 we assign the value to the counter array.
		// also we "raise" the flag.
		if (count_dr > 2) {
			drive_seq[i] += 1;
			*(flgs + 2) += 1;
		}

	}
}
// a function for printing the according messages.
void print_msg(int bus[N][M], int zero_cnt[N], int drive_cnt[N][drivers], int drive_seq[drivers], int flgs[3]) {
	// declaring the used variables.
	int used_drivers[drivers] = {0};
	int i, j;
	// printing the schedule.
	printf("             ");
	for (i = 0; i < M; i++) {
		printf("%4d:00 ", 10 + i);
	}
	//i = 0;
	printf("\n");
	for (i = 0; i < N; i++) {
		printf("station %d:", i + 1);
		for (j = 0; j < M; j++) {
			printf("%8d", bus[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	// here for each case we first check the flag array.

	// printing the message if there are stations with no collection for more than 2 hours.
	if (flgs[0] != 0) {
		printf("The stations with no collection for more than two hours are:\n");
		for (i = 0; i < N; i++) {
			if (zero_cnt[i] > 1) {
				printf("Station number %d\n", i + 1);
			}
		}
		printf("\n");
	}
	// printing the message if there are drivers who have been assigned to the same station in the same hour.
	if (flgs[1] != 0) {
		printf("The drivers that have two or more stations in one hour are:\n");
		for (i = 0; i < N; i++) {
			for (j = 1; j < drivers; j++) {
				if (drive_cnt[i][j] > 1) {
					if (used_drivers[j] > 0) {
						continue;
					}
					printf("Driver number %d\n", j);
					used_drivers[j] = 1;
					
					
				}
				
			}
		}
		printf("\n");
	}
	//  printing the message if there are drivers that drive for more than 3 hours in a row.
	if (flgs[2] != 0) {
		printf("The drivers that drive three or more hours in a row are:\n");
		for (i = 0; i < drivers; i++) {
			if (drive_seq[i] != 0) {
				printf("Driver number %d\n", i);
			}
		}
	}
	// printing the needed message if there are no errors.
	if (flgs[0] == 0 && flgs[1] == 0 && flgs[2] == 0) {
		printf("No problems were found, the schedule is good to go.");
	}
}