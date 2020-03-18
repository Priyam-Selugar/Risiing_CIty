#include "minheap.h"
#include "building.h"
/*This procedure is invoked  when a delete is called. It heapifies from top to bottom,
starting from index 0 till leaf maintaining the mon heap property*/
void minheap::heapify_down(int index)
{
	int index_left_child = 2*index + 1;
	int index_right_child = 2*index + 2;
	if(index_left_child >= leaf) {
		return;
	}
	int index_min = index;
	building current = *min_heap[index];
	building left_child = *min_heap[index_left_child];
	building right_child = *min_heap[index_right_child];
	if(current.building_executed_time > left_child.building_executed_time)
	{
		index_min = index_left_child;
		current = left_child;
	}
	else if(current.building_executed_time == left_child.building_executed_time) {
		if (current.building_num > left_child.building_num) {
			index_min = index_left_child;
			current = left_child;
		}
	}
	if ((index_right_child < leaf) && (current.building_executed_time > right_child.building_executed_time)) {
		index_min = index_right_child;
	} else if (current.building_executed_time == right_child.building_executed_time) {
		if (current.building_num > right_child.building_num) {
			index_min = index_right_child;
		}
	}
	if(index_min != index)
	{
		building* temp = min_heap[index];
		min_heap[index] = min_heap[index_min];
		min_heap[index_min] = temp;
		heapify_down(index_min);
	}
}
/*This method is invoked  when an insert occurs,heapifies from bottom to top
till the root maintaining the min heap property.*/
void minheap::heapify_up(int index)
{
	if (index == 0) {
		return;
	}
	int index_parent = (index-1)/2;
	building parent = *min_heap[index_parent];
	building current = *min_heap[index];
    if(parent.building_executed_time > current.building_executed_time)
    {
        building* temp = min_heap[index_parent];
        min_heap[index_parent] = min_heap[index];
        min_heap[index] = temp;
        heapify_up(index_parent);
    }
    else if (parent.building_executed_time == current.building_executed_time) {
		if (parent.building_num > current.building_num) {
		building* temp = min_heap[index_parent];
		min_heap[index_parent] = min_heap[index];
		min_heap[index] = temp;
		heapify_up(index_parent);
		}
    }
}
	//inserts a buildingnode at the end of active array and simultaneously modifies the minheap array.
void minheap::insert_building(building* value)
{
	min_heap[leaf] = value;
	heapify_up(leaf);
	leaf++;
}
	//returns min indexed building node
building* minheap::get_minimum()
{
	return min_heap[0];
}
/* removes the topmost element of min heap and replaces it with the last leaf value ,
threby reduces array_size by 1 and accordingly modifies the minheap array.
*/
void minheap::delete_minimum()
{
	if(leaf == 0)
	{
		return;
	}
	min_heap[0] = min_heap[leaf-1];
	leaf--;
	heapify_down(0);
}
