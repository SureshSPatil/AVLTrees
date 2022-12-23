#include "binary_tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

binary_tree* initialize_tree(void) {
	binary_tree* bt = (binary_tree*) malloc(sizeof(binary_tree));
	bt->root = NULL;
	bt->size = 0;
	bt->depth = 0;
	return bt;
}

void deinitialize_tree_helper(binary_tree_node* btn) {
	if(btn == NULL) return;
	deinitialize_tree_helper(btn->left_child);
	deinitialize_tree_helper(btn->right_child);
	free(btn);
}

void deinitialize_tree(binary_tree* bt) {
	deinitialize_tree_helper(bt->root);
	free(bt);
}

binary_tree_node* find(int val, binary_tree* bt) {
	binary_tree_node* cur = bt->root;
	while (cur != NULL) {
		if (cur->val == val) {
			return cur;
		} else if (cur->val > val) {
			cur = cur->right_child;
		} else {
			cur = cur->left_child;
		}
	}
	return NULL;
}

void insert_tree_node(int val, binary_tree* bt) {
	binary_tree_node* btn = (binary_tree_node*) malloc(sizeof(binary_tree_node));
	btn->val = val;
	binary_tree_node* cur = bt->root;
	binary_tree_node* cur_parent = NULL;

	int cur_depth = 0;
	while (cur != NULL) {
		cur_parent = cur;
		if (val > cur->val) {
			cur = cur->right_child;
			cur_parent->num_right += 1;
		} else {
			cur = cur->left_child;
			cur_parent->num_left += 1;
		}
		cur_depth += 1;
	}	
	btn->parent = cur_parent;
	btn->left_child = NULL;
	btn->right_child = NULL;
	btn->num_left = 0;
	btn->num_right = 0;
	if (bt->size == 0) {	
		bt->root = btn;
	} else {
		if(btn->val > cur_parent->val) cur_parent->right_child = btn;
		else cur_parent->left_child = btn;
	} 
	bt->size += 1;
	bt->depth = (bt->depth < cur_depth)? cur_depth : bt->depth;
}


int delete_tree_node(binary_tree_node* btn, binary_tree* bt) {
	return 0;
}

int pow2(int n) {
	return (1 << n);
}

int** tree_2_array(binary_tree* bt) {
	int i;
	int max_num_nodes = pow2(bt->depth + 1) - 1;
	int** int_array = (int**) malloc(max_num_nodes * sizeof(int*));
	binary_tree_node** btn_array = (binary_tree_node**) malloc(max_num_nodes * sizeof(binary_tree_node*));

	
	*btn_array = bt->root;
	for (i = 0; i < max_num_nodes; i++) {
		if (*(btn_array + i) != NULL && (2 * i) + 1 < max_num_nodes) {
			*(btn_array + 2*i + 1) = (*(btn_array + i))->left_child;
			*(btn_array + 2*i + 2) = (*(btn_array + i))->right_child;
		}
	}
	
	for (i = 0; i < max_num_nodes; i++) {
		if(*(btn_array + i) != NULL) {
			*(int_array + i) = (int*) malloc(sizeof(int));
			**(int_array + i) = (*(btn_array + i))->val;	
		}
	}

	free(btn_array);
	return int_array;
}

void print_tree_array(int** array, int array_size) {
	int i;	
	for(i = 0; i < array_size; i++) {
		if (*(array + i) == NULL) {
			printf("%s ", "NULL");
		} else {
			printf("%d ", **(array + i));
		}
	}
	printf("\n");
}

void fill_spaces(char* buffer, int num_spaces) {
	int i;	
	for (i = 0; i < num_spaces; i++) {
		strcpy((buffer + i), " ");
	}
}

void center_string(char* buffer, int center_range, char* center_str, int center_str_len) {
	int left_spaces = (center_range - center_str_len) / 2;
	int right_spaces = center_range - center_str_len - left_spaces;
	fill_spaces(buffer, left_spaces);
	strcpy((buffer + left_spaces), center_str);
	fill_spaces((buffer + left_spaces + center_str_len), right_spaces);
}

char* int_2_string(int val, int* str_len) {
	return NULL;
}

void print_tree(int node_size, int num_spaces_between, binary_tree* bt) {
	/*
	width = 2^depth * node_size + (2^depth - 1) * num_spaces_between
	char* buff = (char*) malloc(width * sizeof(char));
	int* strlen = (int*) malloc(sizeof(int));
	line_length = width / 2;
	tree_array = tree2array(bt);
	center_string(buff, width, "root", 4);
	print(buff);
	fill_spaces(buff, width)

	if (bt->root == null) return;
	for i : 0 -> depth
		if (depth == 0) {
			for k : 0 -> 2:
				center_string(buff, width, "|", 1);
				print(buff)
				fill_spaces(buff, width)
			center_string(buff, width, int2string(bt->root->val, &str_len), str_len);
			print(buff)
			fill_spaces(buff, width)
		} else {
			line_length = line_length / 2;
			level = get_level(tree_array, depth)
			print_lines(level, line_length);
			for elem in level:
				int j = 0;
				while True:
					if elem != null:
						center_string((buff + j), (2 * line_length) + 1, int2string(elem), node_size);
					else:
						fill_spaces((buff + j), (2 * line_length) + 1);
					j += (2 * line_length) + 1
					if(j + num_spaces_between > width) break;
					fill_spaces((buff + j), num_spaces_between);
					j += num_spaces_between;
		}
	*/
}
