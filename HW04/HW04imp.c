// IMPLEMENTATION FILE:
# include "HW04hdr.h"
// a function that creates the kitchen.
void CreateProduct(cont_p cont, FILE* menu) {
	// declaring variables.
	dish* temp;
	char name[50];
	cont->size = 0;
	// endless loop until we reach end of file.
	while (1) {
		// checking if allocations and input went well.
		if ((temp = malloc(sizeof(dish))) == NULL)
			PrintError("Error allocating memory.");
		if (fscanf(menu, "%s %d %f", &name, &temp->quantity, &temp->price) == EOF)
			break;
		if ((temp->name = malloc((strlen(name) + 1) * sizeof(char))) == NULL)
			PrintError("Error allocating memory.");
		// copying the name of the dish to the dynamically allocated variable.
		strcpy(temp->name, name);
		// filling the array with the input from manot.
		temp->next = NULL;
		if (cont->head == NULL) {
			cont->head = temp;
			cont->size += 1;
		}
		else {
			cont->tail->next = temp;
			cont->size += 1;
		}
		cont->tail = temp;
	}
	// freeing the temp variable.
	free(temp);
	printf("Kitchen created successfully.\n");
}
// a fnction that adds quantity to a certain dish.
void AddItem(cont_p cont, char* food, int qty) {
	int i;
	// checking if we got a valid value.
	if (qty < 0) {
		printf("Negative value found.\n");
		return 0;
	}
	// creating a temp dish structure so we can navigate through the array.
	dish* temp = cont->head;
	// searching for the dish we need to find.
	for (i = 0; i < cont->size; i++) {
		if (strcmp(temp->name, food) == 0) {
			// if we found the dish, we add the quantity.
			temp->quantity += qty;
			printf("%d %s was added to the kitchen.\n", qty, food);
			return 0;
		}
		temp = temp->next;
	}
	// if we didnt find the dish we print the according message.
	free(temp);
	printf("no such dish as \"%s\", was found.\n", food);
}
// a function that orderes a dish to a table.
void OrderItem(cont_p* table_ar, cont_p dishes, int table, char* food, int qty) {
	// declaring the used variables.
	int i;
	dish* temp = dishes->head;
	dish* new;
	// a loop for going through the dishes that were already ordered to the table.
	for (i = 0; i < dishes->size; i++) {
		if (strcmp(food, temp->name) == 0) {
			// checking if the allocations went well.
			if ((new = malloc(sizeof(dish))) == NULL)
				PrintError("Error allocating memory.");
			if ((new->name = malloc((strlen(food) + 1) * sizeof(char))) == NULL)
				PrintError("Error allocating memory.");
			// if the dish ordered is present in the kitchen we add the structure to the table array.
			strcpy(new->name, food);
			new->price = temp->price;
			new->quantity = qty;
			new->next = table_ar[table]->head;

			table_ar[table]->head = new;
			table_ar[table]->size += 1;
			printf("%d %s were added to table number %d\n", qty, food, table);
			return 0;
		}
		temp = temp->next;
	}
	// if the dish wasnt found in the kitchen we print the according message.
	printf("we dont have \"%s\" sorry.\n", food);
	free(temp);
}
// a function for removing the last item ordered.
void RemoveItem(cont_p* table_ar, int table) {
	// if the table is empty then we dont have anything to remove.
	if (table_ar[table]->head == NULL) {
		printf("Table is empty.\n");
		return 0;
	}
	// declaring the variables.
	int i;
	dish* temp;
	// removing the head index from the array.
	if ((temp = malloc(sizeof(dish))) == NULL)
		PrintError("Error allocating memory.");
	temp = table_ar[table]->head;
	table_ar[table]->head = table_ar[table]->head->next;
	printf("%d %s was returned from table number %d.\n",temp->quantity , temp->name, table);
	free (temp);
	table_ar[table]->size -= 1;
}
// a function for removing a table.
void RemoveTable(cont_p* table_ar, int table) {
	// if the table is empty then we have nothing to free.
	if (table_ar[table]->head == NULL) {
		printf("Table number %d hasn't ordered yet.\n", table);
		return 0;
	}
	// declaring the used variables.
	dish* temp = table_ar[table]->head;
	dish* deleter;
	int i;
	float sum = 0, service = 0.15;
	// we go through each index in the dishes array and free it.
	// also we calculate the cost of everything.
	for (i = 0; table_ar[table]->size; i++) {
		if (temp == NULL) {
			break;
		}
		printf("%d %s. ", temp->quantity, temp->name);
		sum += (temp->price * temp->quantity);
		deleter = temp;
		temp = temp->next;
		table_ar[table]->size -= 1;
		free(deleter);
	}
	// printing the bill.
	printf("%0.2f nis + %0.2f for tips, please!\n", sum, sum * service);
	free(temp);
	
}
// a function for printing error messages and exiting the program.
void PrintError(char* str) {
	printf("\n%s", str);
	exit(1);
}
