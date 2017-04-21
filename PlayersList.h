#ifndef PLAYERSLIST_H
#define PLAYERSLIST_H

#include "Player.h"
#include "stringHandling.h"

struct node {
	Player player;
	struct node* next;
};

typedef struct node* Node;
typedef struct node NODE_SIZE;

Node newPlayersList(void);

Node addSorted(Node list, Player player);

void printPlayersList(Node list);

int isPlayersListEmpty(Node list);

int listPlayersSize(Node list);

Node removePlayer(Node list, String name);

Player getPlayer(Node list, String name);

void destroyPlayersList(Node list);

#endif
