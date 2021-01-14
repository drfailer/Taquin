CC = gcc
CFLAGS = -Wall -Wextra
EXEC = main
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all = $(EXEC)

prog : $(OBJ)	
	$(CC) -o $@ $^ `sdl-config --cflags --libs` -lSDL_ttf


main.o : foncTaquin.h
%.o: %.c
	$(CC) $(FLAGS) -c $<

clean:
	@rm -rf $(OBJ) $(EXEC)
