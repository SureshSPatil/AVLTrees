#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

void left_rotate(binary_tree_node* btn, binary_tree* bt) {
	binary_tree_node* child = btn->right_child;
	btn->right_child = child->left_child;
	child->left_child = btn;
	btn->depth_right = child->depth_left;
	child->depth_left = max(btn->depth_left, btn->depth_right) + 1;
	if (btn == bt->root) {
		child->parent = NULL;		
		btn->parent = child;
		bt->root = child;
	} else {
		if (child->val > btn->parent->val) btn->parent->right_child = child;
		else btn->parent->left_child = child;
		child->parent = btn->parent;
		btn->parent = child;
	}
}

void right_rotate(binary_tree_node* btn, binary_tree* bt) {
	binary_tree_node* child = btn->left_child;
	btn->left_child = child->right_child;
	child->right_child = btn;
	btn->depth_left = child->depth_right;
	child->depth_right = max(btn->depth_left, btn->depth_right) + 1;
	if (btn == bt->root) {
		child->parent = NULL;		
		btn->parent = child;
		bt->root = child;
	} else {
		if (child->val > btn->parent->val) btn->parent->right_child = child;
		else btn->parent->left_child = child;
		child->parent = btn->parent;
		btn->parent = child;
	}
}

int does_violate(binary_tree_node* potential_problem) {
	binary_tree_node* cur = potential_problem;
	while (cur != NULL) {
		if (abs(cur->depth_left - cur->depth_right) > 1) return 1;
		cur = cur->parent;
	}
	return 0;
}

binary_tree_node* find_problem_child(binary_tree_node* btn) {
	binary_tree_node* cur = btn;
	
	while (1) {
		if (cur->depth_left == cur->depth_right && cur->depth_left == 0) return cur;
		if (cur->depth_left > cur->depth_right) cur = cur->left_child;
		else cur = cur->right_child;
	}
}

binary_tree_node* find_problem(binary_tree_node* btn) {
	binary_tree_node* left_result;

	if (btn == NULL) return NULL;	

	printf("btn->val: %d\ndepth_left: %d\ndepth_right: %d\n\n", btn->val, btn->depth_left, btn->depth_right);

	if (abs(btn->depth_left - btn->depth_right) > 1) return find_problem_child(btn);
	left_result = find_problem(btn->left_child);
	if (left_result != NULL) return left_result;
	return find_problem(btn->right_child);
}

void rebalance(binary_tree* bt, binary_tree_node* potential_problem) {
	binary_tree_node* problem = potential_problem;
	binary_tree_node* parent;
	binary_tree_node* grandparent;	

	while (does_violate(problem)) {
		parent = problem->parent;
		grandparent = parent->parent;
		if (problem->val <= parent->val) {
			if (parent->val <= grandparent->val) {
				right_rotate(grandparent, bt);
			}
			else {
				right_rotate(parent, bt);
				left_rotate(grandparent, bt);
			}
		} else {
			if (parent->val > grandparent->val) left_rotate(grandparent, bt);
			else {
				left_rotate(parent, bt);
				right_rotate(grandparent, bt);
			}
		}

		propogate_depth(grandparent->parent, bt);	
		problem = grandparent;	
	}
}

int main() {
	binary_tree* bt = initialize_tree();

	insert_tree_node(4, bt);
	insert_tree_node(2, bt);
	insert_tree_node(10, bt);
	insert_tree_node(8, bt);
	insert_tree_node(12, bt);
	insert_tree_node(9, bt);
	insert_tree_node(1, bt);
	insert_tree_node(0, bt);
	insert_tree_node(-1, bt);
	insert_tree_node(5, bt);
	insert_tree_node(13, bt);
	insert_tree_node(27, bt);
	//insert_tree_node(-8, bt);


	printf("Original BT:\n");
	printf("BT Depth:%d\n", bt->depth);

	//update_depth(bt);

	//printf("%d\n", bt->root->val);
	//printf("%d\n", bt->root->left_child->val);
	//printf("%d\n", bt->root->right_child->val);

	int** tree_array = tree_2_array(bt);
	//print_tree_array(tree_array, (1 << (bt->depth + 1)) - 1);
	free_tree_array(tree_array, (1 << (bt->depth + 1)) - 1);

	binary_tree* balanced_bt = initialize_tree();

	print_tree(3, bt);

	//binary_tree_node* problem = find_problem(bt->root);
	//if (problem != NULL) printf("%d\n", problem->val);

	deinitialize_tree(bt);
	
	rebalance(balanced_bt, insert_tree_node(4, balanced_bt));
	rebalance(balanced_bt, insert_tree_node(2, balanced_bt));
	rebalance(balanced_bt, insert_tree_node(10, balanced_bt));
	rebalance(balanced_bt, insert_tree_node(8, balanced_bt));
	rebalance(balanced_bt, insert_tree_node(12, balanced_bt));
	rebalance(balanced_bt, insert_tree_node(9, balanced_bt));
	rebalance(balanced_bt, insert_tree_node(1, balanced_bt));
	rebalance(balanced_bt, insert_tree_node(0, balanced_bt));
	rebalance(balanced_bt, insert_tree_node(-1, balanced_bt));
	rebalance(balanced_bt, insert_tree_node(5, balanced_bt));
	rebalance(balanced_bt, insert_tree_node(13, balanced_bt));
	rebalance(balanced_bt, insert_tree_node(27, balanced_bt));
	//rebalance(balanced_bt, insert_tree_node(-8, balanced_bt));

	printf("\nBalanced BT:\n");
	printf("BT Depth:%d\n", balanced_bt->depth);

	//update_depth(bt);

	//printf("%d\n", bt->root->val);
	//printf("%d\n", bt->root->left_child->val);
	//printf("%d\n", bt->root->right_child->val);

	int** tree_array_balanced = tree_2_array(balanced_bt);
	//print_tree_array(tree_array_balanced, (1 << (balanced_bt->depth + 1)) - 1);
	free_tree_array(tree_array_balanced, (1 << (balanced_bt->depth + 1)) - 1);

	print_tree(3, balanced_bt);

	//binary_tree_node* problem = find_problem(bt->root);
	//if (problem != NULL) printf("%d\n", problem->val);

	deinitialize_tree(balanced_bt);


	return 0;
}
