#ifndef BINARY_TREE
#define BINARY_TREE

#include "binary_tree_node.h"

#define tree_contains(val) (find(val) != NULL)

typedef struct binary_tree {
	binary_tree_node* root;
	int size;
	int depth;
} binary_tree;

binary_tree* initialize_tree();

void deinitialize_tree(binary_tree* bt);

//void update_count(binary_tree_node* btn, int new_count);

binary_tree_node* find(int val, binary_tree* bt);

void insert_tree_node(int val, binary_tree* bt);

int delete_tree_node(binary_tree_node* btn, binary_tree* bt);

int** tree_2_array(binary_tree* bt);

void print_tree_array(int** array, int array_size);

void free_tree_array(int** array, int array_size);

void print_tree(int node_size, binary_tree* bt);


#endif
