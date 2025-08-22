//Motea Catalin-Alexandru 311CA
#include <stdio.h>
#include <stdlib.h>

#include "ascii_si_binar.h"
#include "imagine.h"

//citirea in ascii
void citireascii(FILE *file, IMG *img)
{
	for (int i = 0; i < img->n; i++) {
		for (int j = 0; j < img->m; j++) {
			for (int k = 0; k < img->pixeli; k++) {
				fscanf(file, "%d", &img->matrice[i][j][k]);
			}
		}
	}
}

//citirea in binar
void citirebinary(FILE *file, IMG *img)
{
	unsigned char elem;
	for (int i = 0; i < img->n; i++) {
		for (int j = 0; j < img->m; j++) {
			for (int k = 0; k < img->pixeli; k++) {
				fread(&elem, sizeof(unsigned char), 1, file);
				img->matrice[i][j][k] = (int)elem;
			}
		}
	}
}

//afisarea in ascii
void afis_ascii(FILE *file, IMG *img)
{
	for (int i = 0; i < img->n; i++) {
		for (int j = 0; j < img->m; j++) {
			for (int k = 0; k < img->pixeli; k++) {
				fprintf(file, "%d ", img->matrice[i][j][k]);
			}
		}
		fprintf(file, "\n");
	}
}

//afisarea in binar
void afis_binary(FILE *file, IMG *img)
{
	unsigned char elem;
	for (int i = 0; i < img->n; i++) {
		for (int j = 0; j < img->m; j++) {
			for (int k = 0; k < img->pixeli; k++) {
				elem = (unsigned char)img->matrice[i][j][k];
				fwrite(&elem, sizeof(unsigned char), 1, file);
			}
		}
	}
}
