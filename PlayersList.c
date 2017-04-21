#include "PlayersList.h"
#include "stringHandling.h"
#include <stdio.h>
#include <stdlib.h>

#define DEBUG if(0)

Node newPlayersList(void) {
	return NULL;
}

Node addSorted(Node list, Player player) {
	Node node = (Node) malloc(sizeof(NODE_SIZE));
	node->player = player;
	Node iterator = list, prevNode = NULL;
	while(iterator != NULL && iterator->player->score < player->score) {
		prevNode = iterator;
		iterator = iterator->next;
	}
	if(prevNode == NULL) {
		node->next = list;
		list = node;
	} else {
		node->next = prevNode->next;
		prevNode->next = node;
	}
	return list;
}

void printPlayersList(Node list) {
	printf("[");
	Node iterator;
	for(iterator = list; iterator != NULL; iterator = iterator->next) {
		printf("%s : %d", iterator->player->name, iterator->player->score);
		if(iterator->next != NULL)
			printf(", ");
	}
	printf("]\n");
}

Node removePlayer(Node list, String name) {

}

Player getPlayer(Node list, String name) {
	if(isEqual(list->player->name, name))
		return list->player;
	if(list == NULL)
		return NULL;
	return getPlayer(list->next, name);
}

int isPlayersListEmpty(Node list) {
	return list == NULL;
}

int listPlayersSize(Node list) {
	if(list == NULL)
		return 0;
	return 1 + listPlayersSize(list->next);
}

void destroyPlayersList(Node list) {
	if(list == NULL)
		return;
	destroyPlayersList(list->next);
	free(list);
}
