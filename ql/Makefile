CC			= gcc
LD			= gcc

SRC			= src
OBJ			= obj
BIN			= ../bin

CINCLUDES	= -Iinclude/
CWARNINGS	= -Wall -Wextra
CCFLAGS		= -O2 $(CINCLUDES) $(CWARNINGS)

ifeq ($(OS), Windows_NT)
    LDFLAGS	= -lmingw32 
endif

SOURCES		:= $(wildcard $(SRC)/*.c)
OBJECTS		:= $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

all: $(OBJECTS)
	@mkdir -p $(BIN)
	@echo "Linking executable..."
	@$(LD) $^ -o $(BIN)/ql $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	@echo "Compiling $<..."
	@$(CC) $(CCFLAGS) -c $< -o $@

clean:
	@echo "Deleting binaries..."
	@rm -f $(BIN)/ql*
	@echo "Deleting objects..."
	@rm -f $(OBJECTS)

