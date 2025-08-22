#pragma once
#include "subfunctii.h"

void load(char linie[MAX], int *pos, IMG * img);
void selectat(char linie[MAX], IMG *img, int *pos);
void crop(IMG *img);
void save(char linie[MAX], int *pos, IMG *img);
void aplicatie(char linie[MAX], IMG *img, int *pos);
void equalize(IMG *img);
void histogram(IMG *img, char linie[MAX], int *pos);
void rotate(IMG *img, char linie[MAX], int *pos);
void fexit(IMG *img);
