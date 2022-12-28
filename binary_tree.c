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

int max(int a, int b){
	return (a > b)? a : b;
}

int update_depth_helper(binary_tree_node* btn) {
	if (btn == NULL) return 0;
	else {
		printf("btn->val: %d\ndepth_left: %d\ndepth_right: %d\n\n", btn->val, btn->depth_left, btn->depth_right);
		btn->depth_left = update_depth_helper(btn->left_child);
		btn->depth_right = update_depth_helper(btn->right_child);
		return max(btn->depth_left, btn->depth_right) + 1;
	}
}

void update_depth(binary_tree* bt) {
	update_depth_helper(bt->root);	
	bt->depth = max(bt->root->depth_left, bt->root->depth_right);
}

void propogate_depth(binary_tree_node* btn, binary_tree* bt) {
	binary_tree_node* cur = btn;
	while (cur != NULL) {
		cur->depth_left = (cur->left_child)? 1 + max(cur->left_child->depth_left, cur->left_child->depth_right) : 0;
		cur->depth_right = (cur->right_child)? 1 + max(cur->right_child->depth_left, cur->right_child->depth_right) : 0;
		cur = cur->parent;
	}
	bt->depth = max(bt->root->depth_left, bt->root->depth_right);	
}

binary_tree_node* insert_tree_node(int val, binary_tree* bt) {
	binary_tree_node* btn = (binary_tree_node*) malloc(sizeof(binary_tree_node));
	btn->val = val;
	binary_tree_node* cur = bt->root;
	binary_tree_node* cur_parent = NULL;

	int cur_depth = 0;
	while (cur != NULL) {
		cur_parent = cur;
		if (val > cur->val) {
			cur = cur->right_child;
		} else {
			cur = cur->left_child;
		}
		cur_depth += 1;
	}	
	btn->parent = cur_parent;
	btn->left_child = NULL;
	btn->right_child = NULL;
	btn->depth_left = 0;
	btn->depth_right = 0;
	if (bt->size == 0) {	
		bt->root = btn;
	} else {
		if(btn->val > cur_parent->val) cur_parent->right_child = btn;
		else cur_parent->left_child = btn;
	} 
	bt->size += 1;
	if (btn->parent != NULL) {
		if (btn->val > btn->parent->val) {
			if (btn->parent->depth_right == 0) btn->parent->depth_right = 1;
		} else {
			if (btn->parent->depth_left == 0) btn->parent->depth_left = 1;
		}
		propogate_depth(btn->parent->parent, bt);
	}
	
	return btn;
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
		if (*(btn_array + i) != NULL) {
			*(int_array + i) = (int*) malloc(sizeof(int));
			**(int_array + i) = (*(btn_array + i))->val;	
		} else {
			*(int_array + i) = NULL;
		}
	}

	free(btn_array);
	return int_array;
}

void print_tree_array(int** array, int array_size) {
	int i;	
	for (i = 0; i < array_size; i++) {
		if (*(array + i) == NULL) {
			printf("%s ", "NULL");
		} else {
			printf("%d ", **(array + i));
		}
	}
	printf("\n");
}

void free_tree_array(int** array, int array_size) {
	int i;
	for (i = 0; i < array_size; i++) {
		if (*(array + i) != NULL) {
			free(*(array + i));
		}
	}
	free(array);
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

int int_2_string(char* buff, int val) {
	return sprintf(buff, "%d", val);
}

void print_arrows(int** tree_array, int start_index, int end_index, int arrow_len, char* line_buff) {
	int i, j, k;
	for (i = 0; i < arrow_len; i++) {
		k = 0;
		for (j = start_index; j < end_index; j++) {
			if (*(tree_array + j) != NULL) {
				if (j % 2 == 1) {
					fill_spaces((line_buff + k), arrow_len + 1);
					k += arrow_len + 1;

					fill_spaces((line_buff + k), arrow_len - 1 - i);
					strcpy((line_buff + k + arrow_len - 1 - i), "/");
					fill_spaces((line_buff + k + arrow_len - i), i);
					k += arrow_len;					

					fill_spaces((line_buff + k), 1);
					k += 1;
				} else {
					fill_spaces((line_buff + k), i);
					strcpy((line_buff + k + i), "\\");
					fill_spaces((line_buff + k + i + 1), arrow_len - 1 - i);
					k += arrow_len;

					fill_spaces((line_buff + k), arrow_len + 1);
					k += arrow_len + 1;

					if(j != end_index - 1) {
						fill_spaces((line_buff + k), 1);
						k += 1;
					}
				}
			} else {
				if (j % 2 == 1) {
					fill_spaces((line_buff + k), arrow_len + 1);
					k += arrow_len + 1;

					fill_spaces((line_buff + k), arrow_len);
					k += arrow_len;

					fill_spaces((line_buff + k), 1);
					k += 1;
				} else {
					fill_spaces((line_buff + k), arrow_len);
					k += arrow_len;

					fill_spaces((line_buff + k), arrow_len + 1);
					k += arrow_len + 1;

					if(j != end_index - 1) {
						fill_spaces((line_buff + k), 1);
						k += 1;
					}
				}
			}
		}
		printf("%s\n", line_buff);
	}
}

void print_tree(int node_size, binary_tree* bt) {
	int width = (pow2(bt->depth) * node_size) + (pow2(bt->depth) - 1);
	int arrow_len = width / 2;
	int int_len = 0;
	char* line_buff = (char*) malloc(width * sizeof(char));
	char int_buff[101];
	int** tree_array = tree_2_array(bt);
	int i, j, k, level_start, level_end;

	center_string(line_buff, width, "ROOT", 4);
	printf("%s\n", line_buff);

	for(j = 0; j < 2; j++) {
		center_string(line_buff, width, "|", 1);
		printf("%s\n", line_buff);
	}

	if (bt->root == NULL) {
		center_string(line_buff, width, "NULL", 4);
		printf("%s\n", line_buff);
		free_tree_array(tree_array, pow2(bt->depth + 1) - 1);
		free(line_buff);
		return;
	} else {
		int_len = int_2_string(int_buff, bt->root->val);
		center_string(line_buff, width, int_buff, int_len);
		printf("%s\n", line_buff);
	} 

	for (i = 1; i < bt->depth + 1; i++) {
		arrow_len = arrow_len / 2;
		level_start = pow2(i) - 1;
		level_end = pow2(i + 1) - 1;
		print_arrows(tree_array, level_start, level_end, arrow_len, line_buff);
		k = 0;
		for(j = level_start; j < level_end; j++) {
			if (*(tree_array + j) != NULL) {
				int_len = int_2_string(int_buff, **(tree_array + j));
				center_string((line_buff + k), (2 * arrow_len) + 1, int_buff, int_len);
			} else {
				fill_spaces((line_buff + k), (2 * arrow_len) + 1);
			}
			k += (2 * arrow_len) + 1;
			if (k + 1 > width) break;
			fill_spaces((line_buff + k), 1);
			k += 1; 
		}
		printf("%s\n", line_buff);
	}

	free_tree_array(tree_array, pow2(bt->depth + 1) - 1);
	free(line_buff);
}
