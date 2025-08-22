//Motea Catalin-Alexandru 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

//functia de parsare a liniei citite de la tastatura
void cuvinte(char linie[MAX], char cuvant[MAX], int *pos)
{
	cuvant[0] = '\0';
	int n = strlen(linie);
	int lungime = 0;
	while (linie[*pos] != ' ' && (*pos) < n && linie[*pos] != '\n') {
		cuvant[lungime] = linie[*pos];
		(*pos)++;
		lungime++;
	}
	while ((linie[*pos] == ' ' || linie[*pos] == '\n') && (*pos) < n) {
		(*pos)++;
	}
	cuvant[lungime] = '\0';
}
