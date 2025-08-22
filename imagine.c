//Motea Catalin-Alexandru 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imagine.h"

void freeimg(IMG img)
{
	for (int i = 0; i < img.n; i++) {
		for (int j = 0; j < img.m; j++) {
			free(img.matrice[i][j]);
		}
		free(img.matrice[i]);
	}
	free(img.matrice);
}

void alocare(IMG *img)
{
	img->matrice = (int ***)malloc(img->n * sizeof(int **));
	for (int i = 0; i < img->n; i++) {
		img->matrice[i] = (int **)malloc(img->m * sizeof(int *));
		for (int j = 0; j < img->m; j++) {
			img->matrice[i][j] = (int *)malloc(img->pixeli * sizeof(int));
		}
	}
}

//functia in care rotesc imaginea selectata cu 90 de grade
void rotire90(IMG *img, int n, int m, int ok)
{
	int ***new_matrix;
	//pentru cazul in care selectia este intreaga
	if (ok == 1) {
		new_matrix = (int ***)malloc(m * sizeof(int **));
		for (int i = 0; i < m; i++) {
			new_matrix[i] = (int **)malloc(n * sizeof(int *));
			for (int j = 0; j < n; j++) {
				new_matrix[i][j] = (int *)malloc(img->pixeli * sizeof(int));
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < img->pixeli; k++) {
					int i2 = j;
					int j2 = n - i - 1;
					new_matrix[i2][j2][k] = img->matrice[i][j][k];
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				free(img->matrice[i][j]);
			}
			free(img->matrice[i]);
		}
		free(img->matrice);
		img->matrice = new_matrix;
		img->x2 = m;
		img->y2 = n;
		img->n = m;
		img->m = n;
	} else {
		//cazul in care selectia nu este intreaga dar este patratica
		new_matrix = (int ***)malloc(n * sizeof(int **));
		for (int i = 0; i < n; i++) {
			new_matrix[i] = (int **)malloc(m * sizeof(int *));
			for (int j = 0; j < m; j++) {
				new_matrix[i][j] = (int *)malloc(img->pixeli * sizeof(int));
				memcpy(new_matrix[i][j], img->matrice[i][j],
					   img->pixeli * sizeof(int));
			}
		}
		for (int i = img->x1; i < img->x2; i++) {
			for (int j = img->y1; j < img->y2; j++) {
				for (int k = 0; k < img->pixeli; k++) {
					int i2 = (j - img->y1) + img->x1;
					int j2 = (img->x2 - i - 1) + img->y1;
					new_matrix[i2][j2][k] = img->matrice[i][j][k];
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				free(img->matrice[i][j]);
			}
			free(img->matrice[i]);
		}
		free(img->matrice);
		img->matrice = new_matrix;
	}
}
