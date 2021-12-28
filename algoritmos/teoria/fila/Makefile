CC = gcc
INCLUDES = includes
SOURCES = source/*.c
BINARY = ./main
PROG = main.c
FLAGS = -g -lm -Wall -Werror
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full -s

all:
	@$(CC) -o $(BINARY) $(PROG) $(SOURCES) -I $(INCLUDES) $(FLAGS)

run: all clear
	@$(BINARY)

clear:
	@clear

val: all clear
	@valgrind $(VFLAGS) $(BINARY)

zip:
	zip -r pilha.zip $(PROG) $(INCLUDES) $(SOURCES) Makefile

clean:
	rm $(BINARY)