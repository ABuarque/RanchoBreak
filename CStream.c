#include "CStream.h"
#include "stringHandling.h"
#include <stdio.h>
#include <stdlib.h>

CStream openFile(const String pathFile, const String mode) {
	CStream stream = (CStream) fopen(pathFile, mode);
	if(stream == NULL) {
		printf("Problem on opening file.\n");
		exit(1);
	}
	return stream;
}

void closeFile(CStream obj) {
	fclose(obj);
}


int fileWriteChar(char c, CStream this) {
	return fputc(c, this);
}

int fileReadChar(CStream this) {
	return fgetc(this);	
}

int fileWriteString(const String string, CStream this) {
	return fputs(string, this);
}

String fileReadString(String place, int size, CStream this) {
	return fgets(place, size, this);
}

int fileWriteBin(void* buffer, int size, int elements, CStream obj) {
	fwrite(buffer, size, elements, obj);
}

int fileReadBin(void* buffer, int size, int elements, CStream obj) {
	fread(buffer, size, elements, obj);
}
