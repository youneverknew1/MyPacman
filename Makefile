CC = gcc
CFLAGS = -Iinclude -Llib -Wall -std=c99
LDFLAGS = -lmingw32 -lSDL2main -lSDL2

all:
	$(CC) $(CFLAGS) src/*.c -o pacman $(LDFLAGS)

clean:
	rm -f pacman.exe