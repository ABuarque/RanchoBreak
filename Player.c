#include <stdio.h>
#include <stdlib.h>
#include "Player.h"
#include "stringHandling.h"

Player newPlayer(String name) {
	Player player;
	copyString(player.name, name);
	player.score = 0;
	return player;
}

void setScore(Player* this, int score) {
	this->score = score;
}

String getPlayerName(const Player* this) {
	return this->name;
} 

int getPlayerScore(const Player* this) {
	return this->score;
}

void destroyPlayer(Player* this) {
	free(this);
}
