DEBUG=1
CC=gcc
ifeq ($(DEBUG),yes)
	CFLAGS=-W -Wall -pedantic -g
	LDFLAGS=
else
	CFLAGS=-W -Wall -pedantic
	LDFLAGS=
endif

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
BIN = chess

all: $(BIN)
ifeq ($(DEBUG),1)
	@echo "Debug mode"
else
	@echo "Release mode"
endif

chess: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
	
%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)
	
clean:
	@rm -rf *.o

mrproper:
	@rm -rf $(BIN)

.PHONY: clean mrproper
