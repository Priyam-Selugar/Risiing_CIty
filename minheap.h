#ifndef MINHEAP_H
#define MINHEAP_H

#include "building.h"

const int MAX = 2000;

//Minheap class: Works on buildingnode.
class minheap {

		public:
			/*This procedure is invoked  when a delete is called. It heapifies from top to bottom,
			starting from index 0 till leaf maintaining the mon heap property*/
		void heapify_down(int index);
		/*This method is invoked  when an insert occurs,heapifies from bottom to top
		till the root maintaining the min heap property.*/
		void heapify_up(int index);
		building* min_heap[MAX];
		int leaf = 0;
		//inserts a buildingnode at the end of active array and simultaneously modifies the minheap array.
		void insert_building(building* value);
		//returns min indexed building node
		building* get_minimum();
		/* removes the topmost element of min heap and replaces it with the last leaf value ,
		threby reduces array_size by 1 and accordingly modifies the minheap array.
		*/
		void delete_minimum();
};
#endif
