#include "binary_tree.h"
#include <stdio.h>

int main() {
	binary_tree* bt = initialize_tree();
	insert_tree_node(5, bt);
	insert_tree_node(3, bt);
	insert_tree_node(6, bt);
	insert_tree_node(2, bt);
	insert_tree_node(4, bt);
	insert_tree_node(8, bt);

	printf("%d\n", bt->depth);

	//printf("%d\n", bt->root->val);
	//printf("%d\n", bt->root->left_child->val);
	//printf("%d\n", bt->root->right_child->val);

	int** tree_array = tree_2_array(bt);
	print_tree_array(tree_array, (1 << (bt->depth + 1)) - 1);
	free_tree_array(tree_array, (1 << (bt->depth + 1)) - 1);

	print_tree(5, bt);

	deinitialize_tree(bt);
	return 0;
}
