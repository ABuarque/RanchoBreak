#include <stdio.h>
#include <stdlib.h>
#include "Player.h"
#include "stringHandling.h"

#define DEBUG if(1)

Player newPlayer(String name) {
	Player player = (Player) malloc(sizeof(PLAYER_SIZE));
	copyString(player->name, name);
	player->score = 0;
	return player;
}

void destroyPlayer(Player player) {
	free(player);
}

int getPlayerScore(Player player) {
	return player->score;
}

void setPlayerScore(Player player, int score) {
	player->score = score;
}

String getPlayerName(Player this) {
	return this->name;
}