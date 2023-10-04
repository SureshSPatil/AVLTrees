CC := gcc
CFLAGS:= -Wall -Wextra -g

INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj

C_FILES := $(wildcard $(SRC_DIR)/*.c)
H_FILES := $(wildcard $(INC_DIR)/*.h)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_FILES))

EXEC := avl
cfiles := binary_tree.c

all: $(OBJ_DIR) $(EXEC)

$(OBJ_DIR):
	mkdir -p $@

$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC)

