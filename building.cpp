 #include "building.h"

building::building(long int buildingNum, long int executed_Time, long int total_Time, redblacknode* rb_pointer) {
	set_building(buildingNum, executed_Time, total_Time, rb_pointer);
}

void building::set_building(long int buildingNum, long int executed_Time, long int total_Time, redblacknode* rb_pointer) {
	building_num = buildingNum;
	building_executed_time = executed_Time;
	building_total_time = total_Time;
	red_black_pointer = rb_pointer;
}
