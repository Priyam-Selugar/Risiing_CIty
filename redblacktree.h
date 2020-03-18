#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include <vector>
#include "redblacknode.h"
using namespace std;

//redblacktree class: Contains Prototypes for all methods of a redblack tree.
class redblacktree {
	public:
		void delete_rebalance(redblacknode* node);
		void rb_rejoin(redblacknode* node_a, redblacknode* node_b);
		void insert_rebalance(redblacknode* node);
		redblacknode* search_tree_helper(redblacknode* node, long int key);
		void left_rotate(redblacknode* node);
		void right_rotate(redblacknode* node);
			redblacknode* min_left(redblacknode* node);
		void search_tree_middle_helper(redblacknode* node, long int building1, long int building2, vector<redblacknode*>* list);

		redblacknode* root;
		redblacknode* external;
		redblacktree();
		redblacknode* search(long int buidingNum);
		void insert(redblacknode* node);
		void delete_node(redblacknode* node);
		void search_tree_miidle(long int building1, long int building2, vector<redblacknode*>* list);
};
#endif
