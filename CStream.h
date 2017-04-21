#ifndef CSTREAM_H
#define CSTREAM_H

#include <stdlib.h>
#include <stdio.h>
#include "stringHandling.h"

typedef FILE* CStream;

/* It creates and also checks wether
 * some error has ocurred.
 */
CStream openFile(const String pathFile, const String mode);

/* It closes the stream;
 * 
 */
void closeFile(CStream obj);

/* It writes a single char on the file.
 * If something goes wron it will return EOF,
 * else, the given char;
 */
int fileWriteChar(char c, CStream this);

/* It gets one char from the file and return it.
 * If something goes wron it will return EOF,
 * else, the given char;
 */
int fileReadChar(CStream this);

/* It will write a whole string on the file.
 * If something goes wron it will return EOF,
 * else, a number dirent from 0;
 */
int fileWriteString(const String string, CStream this);

/* It read a string from file and save it 
 * in the given char vector.
 * In case of erros, it returns NULL, else,
 * a pointer to the first char.
 */
String fileReadString(String place, int size, CStream this);

/* I gets a generic type to save in the given stream.
 * If all goes right, it returns the number of elements.
 */
int fileWriteBin(void* buffer, int size, int elements, CStream obj);

/* It returns a byte block and save is in buffer.
 * If all goes right it returns elements.
 */
int fileReadBin(void* buffer, int size, int elements, CStream obj);

#endif
