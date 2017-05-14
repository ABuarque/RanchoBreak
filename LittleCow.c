#include "LittleCow.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

Cow newCow() {
	Cow cow = (Cow) malloc(sizeof(COW_SIZE));
	cow->fuel = 10;
	cow->lifes = 3;
	cow->coordX = 300;
	cow->coordY = 500;

    cow->animationSprites[0][0] = load_bitmap("imgs/cow1.bmp", NULL);
    cow->animationSprites[0][1] = load_bitmap("imgs/cow2.bmp", NULL);
    cow->animationSprites[0][2] = load_bitmap("imgs/cow3.bmp", NULL);
    cow->animationSprites[0][3] = load_bitmap("imgs/cow4.bmp", NULL);
    cow->animationSprites[1][0] = load_bitmap("imgs/jump1.bmp", NULL);
    cow->animationSprites[1][1] = load_bitmap("imgs/jump2.bmp", NULL);
    cow->animationSprites[1][2] = load_bitmap("imgs/jump3.bmp", NULL);
    cow->animationSprites[1][3] = load_bitmap("imgs/jump4.bmp", NULL);
    cow->animationSprites[2][0] = load_bitmap("imgs/cowDie1.bmp", NULL);
    cow->animationSprites[2][1] = load_bitmap("imgs/cowDie2.bmp", NULL);
    cow->animationSprites[2][2] = load_bitmap("imgs/cowDie3.bmp", NULL);
    cow->animationSprites[2][3] = load_bitmap("imgs/cowDie4.bmp", NULL);
    cow->animationSprites[3][0] = load_bitmap("imgs/stun1.bmp", NULL);
    cow->animationSprites[3][1] = load_bitmap("imgs/stun2.bmp", NULL);
    cow->animationSprites[3][2] = load_bitmap("imgs/stun3.bmp", NULL);
    cow->animationSprites[3][3] = load_bitmap("imgs/stun1.bmp", NULL);
    cow->animationSprites[4][0] = load_bitmap("imgs/life0.bmp", NULL);
    cow->animationSprites[4][1] = load_bitmap("imgs/life1.bmp", NULL);
    cow->animationSprites[4][2] = load_bitmap("imgs/life2.bmp", NULL);
    cow->animationSprites[4][3] = load_bitmap("imgs/life3.bmp", NULL);

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

float getCowCoordX(Cow cow){
    return cow->coordX;
}

void setCowCoordX(Cow cow, float x){
    cow->coordX = x;
}

float getCowCoordY(Cow cow){
    return cow->coordY;
}

void setCowCoordY(Cow cow, float y){
    cow->coordY += y;
}

void destroyCow(Cow cow) {
	free(cow);
}
