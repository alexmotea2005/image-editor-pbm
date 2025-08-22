#pragma once
#define MAX 1000

typedef struct {
	int type;
	int n, m;
	int valmax;
	int pixeli;
	int x1, x2, y1, y2;
	int ***matrice;
} IMG;

void alocare(IMG *img);
void freeimg(IMG img);
void rotire90(IMG *img, int n, int m, int ok);
