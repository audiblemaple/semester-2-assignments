// HEADER FILE:
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// declaring the food/table structure.
typedef struct food {
	char* name;
	float price;
	int quantity;
	struct food* next;
}dish;
// declaring the control structure.
typedef struct cont {
	dish* head;
	dish* tail;
	int size;
}cont, *cont_p;
// declaring the used functions.
void CreateProduct(cont_p cont, FILE* menu);
void AddItem(cont_p cont, char* food, int qty);
void OrderItem(cont_p * table_ar, cont_p dishes, int table, char* food, int qty);
void RemoveItem(cont_p* table_ar, int table);
void RemoveTable(cont_p* table_ar, int table);
void PrintError(char* str);