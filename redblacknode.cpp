#include "redblacknode.h"

redblacknode::redblacknode(long int buildingNum, long int executed_Time, long int total_Time, int color, redblacknode* parent, redblacknode* left, redblacknode* right) {
	set_node(buildingNum, executed_Time, total_Time, color, parent, left, right);
}
/* This method sets member variables of red_black_node which are building_num,
executed_Time,total_Time,rb_left,rb_right,rb_color(0 or 1) 
*/
void redblacknode::set_node(long int buildingNum, long int executed_Time, long int total_Time, int color, redblacknode* parent, redblacknode* left, redblacknode* right) {
	building_num = buildingNum;
	building_executed_time = executed_Time;
	building_total_time = total_Time;
	rb_color = color;
	rb_parent = parent;
	rb_left = left;
	rb_right = right;
}
