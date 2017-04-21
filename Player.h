#ifndef PLAYER_H
#define PLAYER_H

#include "stringHandling.h"

struct player {
	char name[101];
	int score;
};

typedef struct player* Player;
typedef struct player PLAYER_SIZE;

Player newPlayer(String name);

void destroyPlayer(Player player);

int getPlayerScore(Player player);

void setPlayerScore(Player player, int score);

String getPlayerName(Player this);

#endif
