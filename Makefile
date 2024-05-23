# Makefile
CC = gcc
CFLAGS = -Wall -std=c99 -g
OBJS = main.o grid.o target.o robot.o build_grid.o game_logistic.o wall.o
EXEC = jeu

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

main.o: main.c grid.h wall.h target.h build_grid.h game_logistic.h robot.h
	$(CC) $(CFLAGS) -c main.c

grid.o: grid.c grid.h build_grid.h
	$(CC) $(CFLAGS) -c grid.c

target.o: target.c target.h wall.h
	$(CC) $(CFLAGS) -c target.c

robot.o: robot.c robot.h 
	$(CC) $(CFLAGS) -c robot.c

build_grid.o: build_grid.c build_grid.h 
	$(CC) $(CFLAGS) -c build_grid.c

wall.o: wall.c wall.h 
	$(CC) $(CFLAGS) -c wall.c

game_logistic.o: game_logistic.c game_logistic.h 
	$(CC) $(CFLAGS) -c game_logistic.c

clean:
	rm -f *.o $(EXEC)

