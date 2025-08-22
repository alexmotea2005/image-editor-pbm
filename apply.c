//Motea Catalin-Alexandru 311CA
#include <stdlib.h>
#include <string.h>
#include "apply.h"
#include <math.h>

//initializarea fiecarui kenrel dupa formula
void kernel(char nume[MAX], int ker[3][3])
{
	if (strcmp(nume, "EDGE") == 0) {
		ker[0][0] = -1 * 1.0;
		ker[0][1] = -1 * 1.0;
		ker[0][2] = -1 * 1.0;
		ker[1][0] = -1 * 1.0;
		ker[1][1] = 8 * 1.0;
		ker[1][2] = -1 * 1.0;
		ker[2][0] = -1 * 1.0;
		ker[2][1] = -1 * 1.0;
		ker[2][2] = -1 * 1.0;
	}
	if (strcmp(nume, "SHARPEN") == 0) {
		ker[0][0] = 0 * 1.0;
		ker[0][1] = -1 * 1.0;
		ker[0][2] = 0 * 1.0;
		ker[1][0] = -1 * 1.0;
		ker[1][1] = 5 * 1.0;
		ker[1][2] = -1 * 1.0;
		ker[2][0] = 0 * 1.0;
		ker[2][1] = -1 * 1.0;
		ker[2][2] = 0 * 1.0;
	}
	if (strcmp(nume, "BLUR") == 0) {
		ker[0][0] = 1 * 1.0;
		ker[0][1] = 1 * 1.0;
		ker[0][2] = 1 * 1.0;
		ker[1][0] = 1 * 1.0;
		ker[1][1] = 1 * 1.0;
		ker[1][2] = 1 * 1.0;
		ker[2][0] = 1 * 1.0;
		ker[2][1] = 1 * 1.0;
		ker[2][2] = 1 * 1.0;
	}
	if (strcmp(nume, "GAUSSIAN_BLUR") == 0) {
		ker[0][0] = 1 * 1.0;
		ker[0][1] = 2 * 1.0;
		ker[0][2] = 1 * 1.0;
		ker[1][0] = 2 * 1.0;
		ker[1][1] = 4 * 1.0;
		ker[1][2] = 2 * 1.0;
		ker[2][0] = 1 * 1.0;
		ker[2][1] = 2 * 1.0;
		ker[2][2] = 1 * 1.0;
	}
}

//functie de aplicare a unui kernel pe un pixel
int apply_kernel(int i, int j, int k, const int ker[3][3], IMG *img)
{
	int sum = 0;
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (i + x >= 0 && i + x < img->m &&
				j + y >= 0 && j + y < img->n) {
				sum += img->matrice[j + y][i + x][k] *
					ker[x + 1][y + 1];
			}
		}
	}
	return sum;
}

//functia in care se executa comanda in kare aplicam un kernel
void executie(IMG *img, char nume[MAX])
{
	int ker[3][3];
	kernel(nume, ker);
	if (img->type == 2 || img->type == 5) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}
	//verificam daca numele este valid
	if (strcmp(nume, "BLUR") != 0 && strcmp(nume, "GAUSSIAN_BLUR") != 0 &&
		strcmp(nume, "SHARPEN") != 0 && strcmp(nume, "EDGE") != 0) {
		printf("APPLY parameter invalid\n");
		return;
	}
	int ***new = (int ***)malloc(img->n * sizeof(int **));
	for (int i = 0; i < img->n; i++) {
		new[i] = (int **)malloc(img->m * sizeof(int *));
		for (int j = 0; j < img->m; j++) {
			new[i][j] = (int *)malloc(img->pixeli * sizeof(int));
		}
	}
	for (int i = 0 ; i < img->n ; i++) {
		for (int j = 0 ; j < img->m ; j++) {
			for (int k = 0 ; k < img->pixeli ; k++) {
				new[i][j][k] = img->matrice[i][j][k];
			}
		}
	}
	//aplicam kernelul pe fiecare pixel
	for (int i = img->y1; i < img->y2; i++) {
		for (int j = img->x1; j < img->x2; j++) {
			for (int k = 0; k < img->pixeli; k++) {
				int sum = apply_kernel(i, j, k, ker, img);
				if (strcmp(nume, "BLUR") == 0) {
					sum = round(sum / (1.0 * 9));
				} else if (strcmp(nume, "GAUSSIAN_BLUR") == 0) {
					sum = round(sum /  (1.0 * 16));
				} else if (strcmp(nume, "SHARPEN") == 0) {
					sum = sum * 1.0;
				} else if (strcmp(nume, "EDGE") == 0) {
					sum = sum * 1.0;
				}
				if (sum < 0) {
					sum = 0;
				}
				if (sum > 255) {
					sum = 255;
				}
				new[j][i][k] = sum;
			}
		}
	}
	//copiem imaginea noua in cea veche
	for (int i = 1 ; i < img->n - 1 ; i++) {
		for (int j = 1 ; j < img->m - 1 ; j++) {
			for (int k = 0 ; k < img->pixeli ; k++) {
				img->matrice[i][j][k] = new[i][j][k];
			}
		}
	}
	for (int i = 0; i < img->n; i++) {
		for (int j = 0; j < img->m; j++) {
			free(new[i][j]);
		}
		free(new[i]);
	}
	free(new);
	printf("APPLY %s done\n", nume);
}
