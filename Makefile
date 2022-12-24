CC := gcc
exec := avl
libraries := binary_tree_node.h binary_tree.h
cfiles := binary_tree.c

all: $(exec)

$(exec): $(exec).c $(libraries)
	$(CC) -o $(exec) $(exec).c $(libraries) $(cfiles) -Wall

clean: $(exec)
	rm $(exec)

