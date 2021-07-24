
SRC=src
OBJ=obj
B=bin

SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

CFLAGS +=-W  -Wall -Wextra -g3 -Iinclude
CC=gcc 
BIN=$(B)/my_blockchain
RM=rm -rf

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $(BIN) $(OBJS) $(CFLAGS) 

$(OBJ)/%.o: $(SRC)/%.c 
	${CC} ${CFLAGS} -c $< -o $@

clean:
	$(RM) $(BIN) $(B)/*.dSYM $(OBJ)/*.o
