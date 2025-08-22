//Motea Catalin-Alexandru 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functii.h"
#include "imagine.h"
#include "ascii_si_binar.h"
#include "apply.h"
#define MAX 1000
//LOAD functie de incarcare a imaginii
void load(char linie[MAX], int *pos, IMG *img)
{
	//dezalocarea imaginii
	if (img->matrice) {
		freeimg(*img);
	}
	img->matrice = NULL;
	char filename[MAX], magic[3];
	cuvinte(linie, filename, pos);
	FILE *file = fopen(filename, "r");
	if (!file || strcmp(filename, "dummy") == 0) {
		printf("Failed to load %s\n", filename);
		return;
	}
	fpos_t hashtag;
	char input[MAX];
	//in do while sar peste comentarii
	do {
		fgetpos(file, &hashtag);
		fgets(input, MAX, file);
	} while (input[0] == '#');
	fsetpos(file, &hashtag);
	fscanf(file, "%s\n", magic);
	img->type = (int)(magic[1] - '0');
	do {
		fgetpos(file, &hashtag);
		fgets(input, MAX, file);
	} while (input[0] == '#');
	fsetpos(file, &hashtag);
	//mai intai se citesc col dupa linieile
	fscanf(file, "%d %d\n", &img->m, &img->n);
	do {
		fgetpos(file, &hashtag);
		fgets(input, MAX, file);
	} while (input[0] == '#');
	fsetpos(file, &hashtag);
	fscanf(file, "%d\n", &img->valmax);
	if (img->type == 2 || img->type == 5)
		img->pixeli = 1;
	else
		img->pixeli = 3;
	alocare(img);
	img->x1 = 0;
	img->y1 = 0;
	img->x2 = img->n;
	img->y2 = img->m;
	if (img->type == 2 || img->type == 3) {
		citireascii(file, img);
	} else {
		citirebinary(file, img);
	}
	fclose(file);
	printf("Loaded %s\n", filename);

}

//
//SELECT functie de selectare a unei portiuni din imagine
void selectat(char linie[MAX], IMG *img, int *pos)
{
	char numere[MAX];
	cuvinte(linie, numere, pos);
	if (strcmp(numere, "ALL") == 0) {
		printf("Selected ALL\n");
		img->x1 = 0;
		img->y1 = 0;
		img->x2 = img->n;
		img->y2 = img->m;
		return;
	}
	int v[4], i = 0;
	for (i = 0; i < 4; i++) {
		if (numere[0] == '\0') {
			printf("Invalid command\n");
			return;
		}
		v[i] = atoi(numere);
		if (v[i] == 0 && strcmp(numere, "0") != 0) {
			printf("Invalid command\n");
			return;
		}
		cuvinte(linie, numere, pos);

	}
	if (v[0] > v[2]) {
		int aux = v[0];
		v[0] = v[2];
		v[2] = aux;
	}
	if (v[1] > v[3]) {
		int aux = v[1];
		v[1] = v[3];
		v[3] = aux;
	}
	if (v[0] == v[2] || v[1] == v[3]) {
		printf("Invalid set of coordinates\n");
		return;
	}
	if (v[0] < 0 || v[3] > img->n || v[1] < 0 || v[2] > img->m) {
		printf("Invalid set of coordinates\n");
		return;
	}
	img->y1 = v[0];
	img->x1 = v[1];
	img->y2 = v[2];
	img->x2 = v[3];
	printf("Selected %d %d %d %d\n", img->y1, img->x1, img->y2, img->x2);
}

//CROP functia de a aducea imaginea la dimensiunile selectiei
void crop(IMG *img)
{

	int n = img->x2 - img->x1;
	int m = img->y2 - img->y1;
	int  ***new = (int ***)malloc(n * sizeof(int **));
	for (int i = 0; i < n; i++) {
		new[i] = (int **)malloc(m * sizeof(int *));
		for (int j = 0; j < m; j++) {
			new[i][j] = (int *)malloc(img->pixeli * sizeof(int));
		}
	}
    //copiez imaginea selectata in new
	for (int i = img->x1; i < img->x2; i++) {
		for (int j = img->y1; j < img->y2; j++) {
			for (int k = 0; k < img->pixeli; k++) {
				new[i - img->x1][j - img->y1][k] = img->matrice[i][j][k];
			}
		}
	}
	freeimg(*img);
	img->matrice = new;
	img->n = n;
	img->m = m;
	img->x1 = 0;
	img->y1 = 0;
	img->x2 = n;
	img->y2 = m;
	printf("Image cropped\n");
}

//SAVE functia de salvarea a imaginii intr un
// fisier si decodarea sa prin ascii sau binar
void save(char linie[MAX], int *pos, IMG *img)
{
	char filename[MAX], types[MAX];
	cuvinte(linie, filename, pos);
	cuvinte(linie, types, pos);
	//schimbarea tipului de fisier daca e cazul
	if (strcmp(types, "ascii") == 0 && img->type > 3)
		img->type -= 3;
	if (strcmp(types, "ascii") != 0 && img->type < 4)
		img->type += 3;
	FILE *file = fopen(filename, "w");
	if (!file) {
		printf("Failed to save %s\n", filename);
		return;
	}
	fprintf(file, "P%d\n", img->type);
	fprintf(file, "%d %d\n", img->m, img->n);
	fprintf(file, "%d\n", img->valmax);
	if (img->type == 2 || img->type == 3) {
		afis_ascii(file, img);
	} else if (img->type == 5 || img->type == 6) {
		afis_binary(file, img);
	}
	fprintf(file, "\n");
	printf("Saved %s\n", filename);
	fclose(file);
}

//APPLY functia de aplicare a unui filtru
void aplicatie(char linie[MAX], IMG *img, int *pos)
{
	char nume[MAX];
	if (*pos == (int)strlen(linie)) {
		printf("Invalid command\n");
		return;
	}
	cuvinte(linie, nume, pos);
	executie(img, nume);
}

//EQUALIZE functia de egalizare a imaginii
void equalize(IMG *img)
{
	if (img->type == 3 || img->type == 6) {
		printf("Black and white image needed\n");
		return;
	}
	int *frecventa = (int *)malloc((img->valmax + 1) * sizeof(int));
	for (int i = 0; i <= 255; i++) {
		frecventa[i] = 0;
	}
	//se calculeaza frecventa fiecarui pixel
	for (int i = 0; i < img->n; i++) {
		for (int j = 0; j < img->m; j++) {
			int indice = img->matrice[i][j][0];
			frecventa[indice]++;
		}
	}
	//calculez sumele de la i = 0 pana la n
	for (int i = 1; i <= img->valmax; i++) {
		frecventa[i] += frecventa[i - 1];
	}
	for (int i = 0 ; i < img->n ; i++) {
		for (int j = 0; j < img->m; j++) {
			int val = round((double)((double)255 *
					(double)frecventa[img->matrice[i][j][0]] /
					(double)(img->n * img->m)));
			if (val > 255) {
				val = 255;
			}
			if (val < 0) {
				val = 0;
			}
			img->matrice[i][j][0] = val;
		}
	}
	free(frecventa);
	printf("Equalize done\n");
}

//HISTOGRAM functia de calculare a histogramei
void histogram(IMG *img, char linie[MAX], int *pos)
{
	int x, y;
	char numar[MAX];
	cuvinte(linie, numar, pos);
	x = atoi(numar);
	if (x == 0) {
		printf("Invalid command\n");
		return;
	}
	cuvinte(linie, numar, pos);
	y = atoi(numar);
	if (y == 0 || (int)strlen(linie) != *pos) {
		printf("Invalid command\n");
		return;
	}
	if (img->type == 3 || img->type == 6) {
		printf("Black and white image needed\n");
		return;
	}
	int frecventa[256];
	//calculez dimensiunea fiecarui interval
	int val = (img->valmax + 1) / y;
	for (int i = 0; i < y; i++) {
		frecventa[i] = 0;
	}
	//calculez frecventa fiecarui pixel
	for (int i = 0; i < img->n; i++) {
		for (int j = 0; j < img->m; j++) {
			int c = img->matrice[i][j][0] / val;
			frecventa[c]++;
		}
	}
	int vmax = 0;
	for (int i = 0; i < y; i++) {
		if (frecventa[i] > vmax) {
			vmax = frecventa[i];
		}
	}
	//afisarea conform formulei
	for (int i = 0; i < y ; i++) {
		int val = (int)((frecventa[i] * x) / vmax);
			printf("%d\t|\t", val);
		for (int j = 0; j < val; j++) {
			printf("*");
		}
		printf("\n");
	}
}

//ROUND functia pentru a roti portiunea din imagine
void rotate(IMG *img, char linie[MAX], int *pos)
{
	char numar[MAX];
	if ((int)strlen(linie) == *pos) {
		printf("Invalid command\n");
		return;
	}
	cuvinte(linie, numar, pos);
	int nr = atoi(numar);
	if (nr % 90 != 0) {
		printf("Unsupported rotation angle\n");
		return;
	}
	int ok = 0;
	if (img->x1 == 0 && img->x2 == img->n &&
		img->y1 == 0 && img->y2 == img->m) {
		ok = 1;
	}
	if (ok == 0 && img->x2 - img->x1 != img->y2 - img->y1) {
		printf("The selection is not square\n");
		return;
	}
	printf("Rotated %d\n", nr);
	int val;
	//rotirea are o periodicitate de 360 de grade
	if (nr < 0) {
		val = (360 + nr) / 90 % 4;
	} else {
		val = (nr / 90) % 4;
	}
	//nu e nevoie sa fac 3 cazuri separate
	//e deajuns sa rotesc cu 90 de grade
	for (int i = 0 ; i < val ; i++) {
		int n = img->n;
		int m = img->m;
		rotire90(img, n, m, ok);
	}
}

//functia de iesire din program in care dezaloc si imaginea
void fexit(IMG *img)
{
	for (int i = 0; i < img->n; i++) {
		for (int j = 0; j < img->m; j++) {
			free(img->matrice[i][j]);
		}
		free(img->matrice[i]);
	}
	free(img->matrice);
	exit(0);
}
