#ifndef REDBLACKNODE_H
#define REDBLACKNODE_H

//class defining the structure of redblacktree node.
class redblacknode {
		public:
		void set_node(long int buildingNum, long int executed_Time, long int total_Time, int color, redblacknode* parent, redblacknode* left, redblacknode* right);
		long int building_num;
		long int building_executed_time;
		long int building_total_time;
		redblacknode* rb_left;//left child pointer
		redblacknode* rb_right;//right child pointer
		redblacknode* rb_parent;//parent pointer
		int rb_color; // Assign Colors a value :- red : 1, black : 0
		redblacknode(long int buildingNum, long int executed_Time, long int total_Time, int color, redblacknode* parent, redblacknode* left, redblacknode* right);
};
#endif
