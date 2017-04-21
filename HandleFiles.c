#include "HandleFiles.h"
#include "Player.h"
#include "PlayersList.h"
#include "stringHandling.h"
#include "CStream.h"
#include <stdio.h>
#include <stdlib.h>

const char FILE_PATH[] = "list.f";

void savePlayer(CStream stream, Player player) {
	fprintf(stream, "%s %d\n", getPlayerName(player), getPlayerScore(player));
}

void saveListPlayers(Node list) {
	CStream handleFile = openFile(FILE_PATH, "a");
	Node iterator;
	for(iterator = list; iterator != NULL; iterator = iterator->next)
		savePlayer(handleFile, iterator->player);
	closeFile(handleFile);
}

Node getListPlayers(void) {
	CStream handleFile = openFile(FILE_PATH, "r");
	Node list = newPlayersList();
	char name[101];
	int score;
	while(fscanf(handleFile, "%s %d", name, &score) != EOF) {
		list = addSorted(list, _newPlayer(name, score));
	}
	closeFile(handleFile);
	return list;
}
