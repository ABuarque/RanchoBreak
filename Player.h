#ifndef PLAYER_H
#define PLAYER_H

#include "stringHandling.h"

struct player {
	char name[101];
	int score;
};

typedef struct player Player;
typedef struct player PLAYER_SIZE;

Player newPlayer(String name);

void setScore(Player* this, int score);

String getPlayerName(const Player* this);

void destroyPlayer(Player* this);

int getPlayerScore(const Player* this);

#endif
