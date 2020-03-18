#include "redblacktree.h"

//constructor of red_black_tree
redblacktree::redblacktree() {
	external = new redblacknode(-1,-1,-1,0,nullptr,nullptr,nullptr);
	root = external;
}

//called to ensure rbt properties once a delete and rb_rejoin is done.
// When deeleted node sibling is black
//This function is called after deletion of any node to compensate for the delete imbalance and thus maintain red black tree properties
void redblacktree::delete_rebalance(redblacknode* node) {
	while (node != root && node->rb_color == 0) {
		redblacknode* tmp;
		if (node == node->rb_parent->rb_left) {
			tmp = node->rb_parent->rb_right;
			if (tmp->rb_color == 1) {	// Deletion case 1
				tmp->rb_color = 0;
				node->rb_parent->rb_color = 1;
				left_rotate(node->rb_parent);
				tmp = node->rb_parent->rb_right;
			}
			if (tmp->rb_left->rb_color == 0 && tmp->rb_right->rb_color == 0) {	// Deletion case 2
				tmp->rb_color = 1;
				node = node->rb_parent;
			} else {
				if (tmp->rb_right->rb_color == 0) {	// Deletion case 3
					tmp->rb_left->rb_color = 0;
					tmp->rb_color = 1;
					right_rotate(tmp);
					tmp = node->rb_parent->rb_right;
				}
				tmp->rb_color = node->rb_parent->rb_color;	// Deletion case 4
				node->rb_parent->rb_color = 0;
				tmp->rb_right->rb_color = 0;
				left_rotate(node->rb_parent);
				node = root;
			}
			//When deeleted node sibling is red
		} else {
			tmp = node->rb_parent->rb_left;
			// Deletion case 1
			if (tmp->rb_color == 1) {
				tmp->rb_color = 0;
				node->rb_parent->rb_color = 1;
				right_rotate(node->rb_parent);
				tmp = node->rb_parent->rb_left;
			}
			// Deletion case 2
			if (tmp->rb_left->rb_color == 0 && tmp->rb_right->rb_color == 0) {
				tmp->rb_color = 1;
				node = node->rb_parent;
			}
			// Deletion case 3
			else {
				if (tmp->rb_left->rb_color == 0) {
					tmp->rb_right->rb_color = 0;
					tmp->rb_color = 1;
					left_rotate(tmp);
					tmp = node->rb_parent->rb_left;
				}
				// Deletion case 4
				tmp->rb_color = node->rb_parent->rb_color;
				node->rb_parent->rb_color = 0;
				tmp->rb_left->rb_color = 0;
				right_rotate(node->rb_parent);
				node = root;
			}
		}
	}
	node->rb_color = 0;
}

//After node deletion this function rejoins/relinks the children of deleted node to deleted node’s parent
void redblacktree::rb_rejoin(redblacknode* node1, redblacknode* node2){
	if (node1->rb_parent == external) {
		root = node2;
	} else if (node1 == node1->rb_parent->rb_left){
		node1->rb_parent->rb_left = node2;
	} else {
		node1->rb_parent->rb_right = node2;
	}
	node2->rb_parent = node1->rb_parent;
}

//delete a node from rbtree.
// Building_Num node is deleted and delete_rebalance() is called to ensure red black tree properties are followed.
void redblacktree::delete_node(redblacknode* node) {
	redblacknode *node1,*node2;
	node2 = node;
	int original_color = node2->rb_color;
	if (node->rb_left == external) {
		node1 = node->rb_right;
		rb_rejoin(node, node->rb_right);
	} else if (node->rb_right == external) {
		node1 = node->rb_left;
		rb_rejoin(node, node->rb_left);
	} else {
		node2 = min_left(node->rb_right);
		original_color = node2->rb_color;
		node1 = node2->rb_right;
		if (node2->rb_parent == node) {
			node1->rb_parent = node2;
		} else {
			rb_rejoin(node2, node2->rb_right);
			node2->rb_right = node->rb_right;
			node2->rb_right->rb_parent = node2;
		}
		rb_rejoin(node, node2);
		node2->rb_left = node->rb_left;
		node2->rb_left->rb_parent = node2;
		node2->rb_color = node->rb_color;
	}
	if (original_color == 0){
		delete_rebalance(node1);
	}
}

//invoked to ensure rbt properties after insert is done.
void redblacktree::insert_rebalance(redblacknode* node){
	redblacknode* tmp;
	while (node->rb_parent->rb_color == 1) {
		if (node->rb_parent == node->rb_parent->rb_parent->rb_left) {
			tmp = node->rb_parent->rb_parent->rb_right;
			// Insert Case 1
			if (tmp->rb_color == 1) {
				tmp->rb_color = 0;
				node->rb_parent->rb_color = 0;
				node->rb_parent->rb_parent->rb_color = 1;
				node = node->rb_parent->rb_parent;
			} else {
					// Insert case 2
				if (node == node->rb_parent->rb_right) {
					node = node->rb_parent;
					left_rotate(node);
				}
				// Insert case 3
				node->rb_parent->rb_color = 0;
				node->rb_parent->rb_parent->rb_color = 1;
				right_rotate(node->rb_parent->rb_parent);

			}
		} else {
			tmp = node->rb_parent->rb_parent->rb_left;
			// Insert case 1
			if (tmp->rb_color == 1) {
				tmp->rb_color = 0;
				node->rb_parent->rb_color = 0;
				node->rb_parent->rb_parent->rb_color = 1;
				node = node->rb_parent->rb_parent;
			} else {
				// Insert case 2
				if (node == node->rb_parent->rb_left) {
					node = node->rb_parent;
					right_rotate(node);
				}
				//  Insert case 3
				node->rb_parent->rb_color = 0;	
				node->rb_parent->rb_parent->rb_color = 1;
				left_rotate(node->rb_parent->rb_parent);
			}
		}
	}
	root->rb_color = 0;
}

/*  Performs left rotation with node as center to,
 rebalance the red black tree during insert and delete cases and maintains red black properties*/
void redblacktree::left_rotate(redblacknode* node) {
	redblacknode* tmp = node->rb_right;
	node->rb_right = tmp->rb_left;
	if (tmp->rb_left != external) {
		tmp->rb_left->rb_parent = node;
	}
	tmp->rb_parent = node->rb_parent;
	if (node->rb_parent == external) {
		root = tmp;
	} else if (node == node->rb_parent->rb_left) {
		node->rb_parent->rb_left = tmp;
	} else {
		node->rb_parent->rb_right = tmp;
	}
	tmp->rb_left = node;
	node->rb_parent = tmp;
}

/*  Performs right rotation with node as center to,
 rebalance the red black tree during insert and delete cases and maintains red black properties*/
void redblacktree::right_rotate(redblacknode* node) {
	redblacknode* tmp = node->rb_left;
	node->rb_left = tmp->rb_right;
	if (tmp->rb_right != external) {
		tmp->rb_right->rb_parent = node;
	}
	tmp->rb_parent = node->rb_parent;
	if (node->rb_parent == external) {
		root = tmp;
	} else if (node == node->rb_parent->rb_right) {
		node->rb_parent->rb_right = tmp;
	} else {
		node->rb_parent->rb_left = tmp;
	}
	tmp->rb_right = node;
	node->rb_parent = tmp;
}

/*  New building node are added to red black tree
and insert_reblance() is invoked to maintain the red black property following every insert of building_num to tree.*/
void redblacktree::insert(redblacknode* node) {
	redblacknode* node1 = external;
	redblacknode* node2 = root;
	while (node2 != external) {
		node1 = node2;
		if (node->building_num < node2->building_num) {
			node2 = node2->rb_left;
		} else {
			node2 = node2->rb_right;
		}
	}
	node->rb_parent = node1;
	if (node1 == external) {
		root = node;
	} else if (node->building_num < node1->building_num) {
		node1->rb_left = node;
	} else {
		node1->rb_right = node;
	}
	node->rb_left = external;
	node->rb_right = external;
	node->rb_color = 1;
	insert_rebalance(node);
}

/*This method is used to find and return left most leaf from the red black tree
to handle delete cases from non-leaf node*/
redblacknode* redblacktree::min_left(redblacknode* node) {
	while (node->rb_left != external) {
		node = node->rb_left;
	}
	return node;
}

redblacknode* redblacktree::search_tree_helper(redblacknode* node, long int key) {
	if (node == external || key == node->building_num) {
		return node;
	}
	if (key < node->building_num) {
		return search_tree_helper(node->rb_left, key);
	}
	return search_tree_helper(node->rb_right, key);
}

//Invokes serach_tree_helper() corresponding to building_num as parameter during function call
redblacknode* redblacktree::search(long int key) {
	return search_tree_helper(root, key);
}

void redblacktree::search_tree_middle_helper(redblacknode* node, long int building1, long int building2, vector<redblacknode*>* list) {
	if (!((node == external) || (node == nullptr))) {
		if (!(node->building_num < building1)) {
			search_tree_middle_helper(node->rb_left, building1, building2, list);
		}
		if ((node->building_num >= building1) and (node->building_num <= building2)) {
			list->push_back(node);
		}
		if (!(node->building_num > building2)) {
			search_tree_middle_helper(node->rb_right, building1, building2, list);
		}
	}
}

/*   Makes a function call to search_tree_middle_helper() and
returns a list of nodes from red black tree that lie in range from building1 to building 2 which are parameters to this function */
void redblacktree::search_tree_miidle(long int building1, long int building2, vector<redblacknode*>* list) {
	search_tree_middle_helper(root, building1, building2, list);
}
