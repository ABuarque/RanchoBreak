#include "Player.h"
#include "PlayersList.h"
#include "stringHandling.h"
#define WHITE makecol(255,255,255)
#define BLACK makecol(0,0,0)
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

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
	Node iterator = list, prevNode = NULL;
	while(iterator != NULL && isEqual(iterator->player->name, name)) {
		prevNode = iterator;
		iterator = iterator->next;
	}
	if(iterator == NULL)
		return list;
	if(prevNode == NULL) 
		list = iterator->next;
	else
		prevNode->next = iterator->next;
	free(iterator);
	return list;
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

int compare(const void* a, const void* b) {
  Player p1 = *(Player*) a;
  Player p2 = *(Player*) b;
  return p1->score < p2->score;
}

void show(BITMAP *buffer,Node list) {
  BITMAP *ranking = load_bitmap("imgs/ranking.bmp",NULL);
  FONT *fontType = load_font("fonts/constantia18.pcx",NULL,NULL);
  FONT *constantia = load_font("fonts/constantia20.pcx",NULL,NULL);
  //pegando tamanho da lista
  int listSize = listPlayersSize(list);
  Player* players = malloc(sizeof(Player) * listSize);
  int i;
  int playerIndex = 0;
  //alocando espaco
  for(i = 0; i < listSize; i++)
    players[i] = (Player) malloc(sizeof(PLAYER_SIZE));

  //botando os elementos da list no array
  Node it;
  for(it = list; it != NULL; it = it->next) {
    players[playerIndex++] = it->player;
  }
  //ordenando com qick sort
  qsort(players, listSize, sizeof(Player), compare);
  if(listSize >= 5) {
    for(i = 0; i < 5; i++){
      draw_sprite(buffer,ranking,150,250+(i*60));
      textprintf_ex(buffer,constantia,220,260+(i*60),BLACK,-1,"%d#",i+1);
      textprintf_ex(buffer,fontType,310,270+(i*60),BLACK,-1,"%s",getPlayerName(players[i]));
      textprintf_ex(buffer,fontType,580,270+(i*60),BLACK,-1,"%d",getPlayerScore(players[i]));
  	}
  } else {
    for(i = 0; i < listSize; i++){
      draw_sprite(buffer,ranking,150,250+(i*60));
      textprintf_ex(buffer,constantia,220,260+(i*60),BLACK,-1,"%d#",i+1);
      textprintf_ex(buffer,fontType,310,270+(i*60),BLACK,-1,"%s",getPlayerName(players[i]));
      textprintf_ex(buffer,fontType,580,270+(i*60),BLACK,-1,"%d",getPlayerScore(players[i]));
  	}
  }
}