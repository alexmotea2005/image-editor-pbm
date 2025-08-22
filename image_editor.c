//Motea Catalin-Alexandru 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

#define MAX 1000

int main(void)
{
	char comanda[MAX], linie[MAX];
	//initializare imagine
	IMG imagine;
	imagine.matrice = NULL;
	int pos = 0;
	do {
		pos = 0;
		fgets(linie, MAX, stdin);
		//parseaza comanda
		cuvinte(linie, comanda, &pos);
		if (!imagine.matrice && strcmp(comanda, "LOAD") != 0) {
			printf("No image loaded\n");
		} else if (strcmp(comanda, "LOAD") == 0) {
			load(linie, &pos, &imagine);
		} else if (strcmp(comanda, "SELECT") == 0) {
			selectat(linie, &imagine, &pos);
		} else if (strcmp(comanda, "SAVE") == 0) {
			save(linie, &pos, &imagine);
		} else if (strcmp(comanda, "APPLY") == 0) {
			aplicatie(linie, &imagine, &pos);
		} else if (strcmp(comanda, "CROP") == 0) {
			crop(&imagine);
		} else if (strcmp(comanda, "EQUALIZE") == 0) {
			equalize(&imagine);
		} else if (strcmp(comanda, "HISTOGRAM") == 0) {
			histogram(&imagine, linie, &pos);
		} else if (strcmp(comanda, "ROTATE") == 0) {
			rotate(&imagine, linie, &pos);
		} else if (strcmp(comanda, "EXIT") == 0) {
			fexit(&imagine);
		} else {
			printf("Invalid command\n");
		}
	} while (strcmp(comanda, "EXIT") != 0);
	return 0;
}
