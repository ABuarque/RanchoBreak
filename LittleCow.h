#ifndef LITTLECOW_H
#define LITTLECOW_H

struct cow {
	int fuel;
	int lifes;
};

typedef struct cow* Cow;
typedef struct cow COW_SIZE;

Cow newCow();

int getCowLifes(Cow cow);

void setCowLifes(Cow cow, int lifes);

int getCowFuel(Cow cow);

void setCowFuel(Cow cow, int fuel);

void destroyCow(Cow cow);

#endif
