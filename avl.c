#include "binary_tree.h"
#include <stdio.h>

int main() {
	binary_tree* bt = initialize_tree();
	insert_tree_node(5, bt);
	insert_tree_node(4, bt);
	insert_tree_node(7, bt);

	printf("%d\n", bt->depth);

	//printf("%d\n", bt->root->val);
	//printf("%d\n", bt->root->left_child->val);
	//printf("%d\n", bt->root->right_child->val);

	int** tree_array = tree_2_array(bt);
	print_tree_array(tree_array, bt->size);

	deinitialize_tree(bt);
	return 0;
}
