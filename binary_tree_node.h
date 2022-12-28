#ifndef BINARY_TREE_NODE
#define BINARY_TREE_NODE

typedef struct binary_tree_node {
	struct binary_tree_node* parent;
	struct binary_tree_node* left_child;
	struct binary_tree_node* right_child;
	int depth_left;
	int depth_right;
	int val;
} binary_tree_node;

#endif


