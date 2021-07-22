OBJ=obj/my_blockchain.o    	   				\
		obj/list.o   

CFLAGS +=-W  -Wall -Wextra -g3 -fsanitize=address -Iinclude
CC=gcc 
BIN=bin/my_blockchain
RM=rm -rf

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $(BIN) $(OBJ) $(CFLAGS) 

obj/%.o: src/%.c 
	${CC} ${CFLAGS} -c $< -o $@

clean:
	$(RM) bin/$(BIN) bin/*.dSYM obj/*.o
