#ifndef LITTLECOW_H
#define LITTLECOW_H

#include <allegro.h>

struct cow {
	int fuel;
	float coordX;
	float coordY;
	int lifes;
    BITMAP* animationSprites[5][4];
};

typedef struct cow* Cow;
typedef struct cow COW_SIZE;

Cow newCow();

int getCowLifes(Cow cow);

void setCowLifes(Cow cow, int lifes);

int getCowFuel(Cow cow);

void setCowFuel(Cow cow, int fuel);

float getCowCoordX(Cow cow);

void setCowCoordX(Cow cow, float x);

float getCowCoordY(Cow cow);

void setCowCoordY(Cow cow, float y);

void destroyCow(Cow cow);

#endif
