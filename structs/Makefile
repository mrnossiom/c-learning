# MAKEFILE
CC=gcc
CFLAGS=-Wall -Wextra -Wvla -pedantic
DEBUG_FLAGS=-g -fsanitize=address

# im bad at makefile, uncomment the one you want to build
# SRC=linked_list.c
# BIN=linked_list
# SRC=vec.c
# BIN=vec

all:
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

debug:
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(SRC) -o $(BIN)

clean:
	$(RM) $(BIN)

.PHONY: all clean
# END
