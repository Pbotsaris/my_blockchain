SRC=src
OBJ=obj
BIN=bin

CFLAGS +=-W  -Wall -Wextra -g3 -Iinclude
CFLAGS2 +=-W -g3 -Iinclude
CC=gcc-11
TARGET=$(BIN)/my_blockchain
RM=rm -rf

SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

TEST=tests
TESTS=$(wildcard $(TEST)/*.c)
TESTOBJS=${OBJ}/list.o ${OBJ}/option.o
TESTBINS=$(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TESTS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) 

$(OBJ)/%.o: $(SRC)/%.c 
	${CC} ${CFLAGS} -c $< -o $@

# dir don't exit
$(OBJ):
	mkdir $@

$(BIN):
	mkdir $@

$(TEST)/bin:
	mkdir $@

# TESTING
$(TEST)/bin/%: $(TEST)/%.c
	${CC} ${CFLAGS2} $< $(TESTOBJS) -o $@ -lcheck

test: $(TARGET) $(TEST)/bin $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

clean:
	$(RM) $(TARGET) $(BIN)/*.dSYM $(OBJ)/*.o $(LIBDIR)
