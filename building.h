#ifndef BUILDING_H
#define BUILDING_H
#include "redblacknode.h"

// class defining structure of building
class building {
		public:
		void set_building(long int buildingNum, long int executed_Time, long int total_Time, redblacknode* rb_pointer);

		long int building_num;
		long int building_executed_time;
		long int building_total_time;
		redblacknode* red_black_pointer;
		building(long int buildingNum, long int executed_Time, long int total_Time, redblacknode* rb_pointer);
};
#endif
