#include "LittleCow.h"
#include <stdio.h>
#include <stdlib.h>

Cow newCow() {
	Cow cow = (Cow) malloc(sizeof(COW_SIZE));
	cow->fuel = 10;
	cow->lifes = 2;
	return cow;
}

int getCowLifes(Cow cow) {
	return cow->lifes;
}

//if it has gotten points of life, +1, else -1
void setCowLifes(Cow cow, int lifes) {
	cow->lifes += lifes;
	if(cow->lifes < 0)
		cow->lifes = 0;
}

int getCowFuel(Cow cow) {
	return cow->fuel;
}

//if it has gotten points of fuel, +1, else -1
void setCowFuel(Cow cow, int fuel) {
	cow->fuel += fuel;
	if(cow->fuel < 0)
		cow->fuel = 0;
}

void destroyCow(Cow cow) {
	free(cow);
}
