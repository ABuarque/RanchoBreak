CC = gcc
CFLAGS = -I. -W -Wall
LIBS = `allegro-config --shared` -lm
DEPS = $(wildcard *.h)
SRC = $(wildcard *.c)
OBJ= $(SRC:.c=.o)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

app: $(OBJ)
	gcc -o app $(SRC) -I. $(LIBS)