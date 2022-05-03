// MAIN FILE:
# include "HW04hdr.h"
# define tables 50
// main function.
int main() {
	// declaring the used variables.
	FILE *menu, *ins;
	int i, input, qty = 0, trigger = 0;
	int table_num;
	char food[256];//<--here we need to check if its allowed.
	// declaring the tables (control structure array).
	// initializing the tables.
	cont_p manage_table[tables];
	for (i = 0; i < tables; i++) {
		if ((manage_table[i] = malloc(sizeof(cont))) == NULL)
			PrintError("Error allocating memory.\n");
		manage_table[i]->head = NULL;
		manage_table[i]->tail = NULL;
		manage_table[i]->size = 0;
	}
	// declaring the kitchen array.
	cont_p manage_dish;
	if ((manage_dish = malloc(sizeof(cont))) == NULL)
		PrintError("Error allocating memory.\n");
	manage_dish->head = NULL;
	// opening the files.
	if ((menu = fopen("files\\Manot.txt", "r")) == NULL)
		PrintError("Error opening file 'manot'\n.");
	if ((ins = fopen("files\\instructions.txt", "r")) == NULL)
		PrintError("Error opening file 'instructions'\n.");
	if (fscanf(ins, "%d", &input) != 1)
		PrintError("Input error.\n");
	// an endless loop for reading through the whole file.
	while (1) {
		// if we already created the kitchen we print the according message.
		if (input == 1 && trigger == 1)
			printf("we already created the kitchen.\n");
		// if we didnt create the kitchen yet then we create it.
		if (input == 1 && trigger == 0) {
			CreateProduct(manage_dish, menu);
			trigger = 1;
		}
		// if the input is not 1 and we didnt create the kitchen yet then we print the according message.
		if (input != 1 && trigger == 0)
			printf("first we need to create the kitchen.\n");
		// function 2 call (adding items to the kitchen).
		if (input == 2 && trigger == 1)
			AddItem(manage_dish, food, qty);
		// function 3 call (ordering a dish to a table).
		if (input == 3 && trigger == 1)
			OrderItem(manage_table, manage_dish, table_num, food, qty);
		// function 4 call (removint the last dish from a table).
		if (input == 4 && trigger == 1)
			RemoveItem(manage_table, table_num);
		// closing the table.
		if (input == 5 && trigger == 1)
			RemoveTable(manage_table, table_num);
		// getting next function call and if the file has ended then we break the loop.
		if (fscanf(ins, "%d", &input) == EOF)
			break;
		// if input is 2 we search for 2 variables.
		if (input == 2) {
			if (fscanf(ins, "%s %d", food, &qty) != 2)
				PrintError("Input error`2.\n");
		}
		// if input is 3 we search for 3 variables.
		if (input == 3) {
			if (fscanf(ins, "%d %s %d",&table_num, food, &qty) != 3)
				PrintError("Input error3.\n");
		}
		// if input is 4 we search for 1 variables.
		if (input == 4) {
			if (fscanf(ins, "%d", &table_num) != 1)
				PrintError("Input error4.\n");
		}
		// if input is 5 we search for 1 variables.
		if (input == 5) {
			if (fscanf(ins, "%d", &table_num) != 1)
				PrintError("Input error5.\n");
		}
	}
	// printing end of program info.
	printf("End of program.");
	fclose(menu);
	fclose(ins);
	return 0;
} 