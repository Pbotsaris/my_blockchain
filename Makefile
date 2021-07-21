OBJ=obj/my_blockchain.o    	   				\
OBJ=obj/list.o    	 				  				\

CFLAGS +=-W  -Wall -Wextra -g3 -Iinclude
CC=gcc 
BIN=bin/my_blockchain
RM=rm -rf

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $(BIN) $(OBJ) $(CFLAGS) 

obj/%.o: src/%.c 
	${CC} ${CFLAGS} -c $< -o $@

clean:
	$(RM) bin/$(BIN) bin/*.dSYM obj/*