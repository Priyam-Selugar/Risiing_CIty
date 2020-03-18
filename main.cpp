// Driver Function of Program
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

#include "building.h"
#include "minheap.h"
#include "redblacknode.h"
#include "redblacktree.h"

using namespace std;

//processes  command from input file.
void process_input_command(string input_command, string args, minheap* min_heap_pointer, redblacktree* rbt_pointer, ofstream& outfile) {
	if (input_command == "Insert") { //handles insert commands from the input file
		long int buildingNum,total_Time;
		regex re("(.*),(.*)");
		if (regex_match(args, re)) {
			for (smatch sm; regex_search(args, sm, re); args = sm.suffix()) {
				buildingNum = stol(sm.str(1));
				total_Time = stol(sm.str(2));
			}
			redblacknode* rb_pointer = new redblacknode(buildingNum, 0, total_Time, 1, nullptr, rbt_pointer->external, rbt_pointer->external);
			rbt_pointer->insert(rb_pointer);

			building* B = new building(buildingNum,0,total_Time,rb_pointer);
			min_heap_pointer->insert_building(B);
		}
		//handles print commands from the input file
	} else if (input_command == "PrintBuilding") {
		long int b1 = -1;
		long int b2 = -1;
		regex re("(.*),(.*)");
		//Print Building with 2 arguements with its attributes
		if (regex_match(args, re)) {
			for (smatch sm; regex_search(args, sm, re); args = sm.suffix()) {
				b1 = stol(sm.str(1));
				b2 = stol(sm.str(2));
			}
			vector<redblacknode*>* list = new vector<redblacknode*>;
			rbt_pointer->search_tree_miidle(b1, b2, list);
			int list_size = list->size();
			int j;
			for (j = 0; j < list_size-1; j++) {
				outfile << "(" << list->at(j)->building_num << "," << list->at(j)->building_executed_time << "," << list->at(j)->building_total_time << ")" << ",";
			}

			if (list_size == 0) {
				outfile << "(" << 0 << "," << 0 << "," << 0 << ")" ;
			}
			else {
				outfile << "(" << list->at(j)->building_num << "," << list->at(j)->building_executed_time << "," << list->at(j)->building_total_time << ")";
			}
			outfile << endl;
			// Display Building with one arguement
		} else {
			b1 = stol(args);
			redblacknode* searchnode = rbt_pointer->search(b1);
			if (searchnode->building_num == -1) {
				outfile << "(" << 0 << "," << 0 << "," << 0 << ")" << endl;
			}
			else {
				outfile << "(" << searchnode->building_num << "," << searchnode->building_executed_time << "," << searchnode->building_total_time << ")" << endl;
			}
		}
	}
}


int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "No file provided";
		return 1;
	}
	//Initialize min_heap  and  red_black_tree here
	minheap* min_heap_pointer = new minheap;
	redblacktree* rbt_pointer = new redblacktree();

	vector<string> lines;
	string line = "";
	ifstream infile(argv[1]);
	if(!infile) {
		cout << "Cannot open input file\n";
		return 1;
	}
	//reading file in a input array of strings
	while (getline(infile, line)) {
		lines.push_back(line);
	}
	infile.close();

	ofstream outfile;
	outfile.open("output_file.txt");

	int size_of_input = lines.size();

	long int line_number=0;//line number in input file
	building* curr=nullptr;
	int end_loop = 0;	//loop end
	long int global_time = 0;	//global time counter
	int work_done = 0;	//record of work done  so far for each iteration in loop
	bool is_wayne_busy = false;	//is_wayne_busy to check whether insutry is busy or not ; initally False

	regex re("(.*): (.*)\\((.*)\\)"); // regex to split the input line in cmd_time, command and args.
	long int cmd_time = -1;
	string input_command;
	string args;

	while(!end_loop) {
		string line = "-1: Break()";
		if (line_number != size_of_input) {
			line = lines[line_number];
		}
		if (regex_match(line, re)) {

			for (smatch sm; regex_search(line, sm, re); line = sm.suffix()) {
				cmd_time = stol(sm.str(1));
				input_command = sm.str(2);
				args = sm.str(3);
			}
			while (cmd_time != global_time) {
				//if executed_Time == total_Time iee. Building construction Done
				if((curr!=nullptr) && (curr->building_executed_time == curr->building_total_time)) {
					is_wayne_busy = false;
					outfile<< "(" << curr->building_num << "," << global_time << ")" << endl;
					rbt_pointer->delete_node(curr->red_black_pointer);
					curr = nullptr;
					if ((min_heap_pointer->leaf == 0) && (cmd_time == -1)) {
						end_loop = 1;
						break;
					}
//When 5 units work is done for a bulding update executed_Time.
				} else if (curr!=nullptr && work_done == 5) {
					is_wayne_busy = false;
					min_heap_pointer->insert_building(curr);
				}
				// daily work of wayne industries
				else if (curr != nullptr) {
					work_done++;
					curr->building_executed_time++;
					curr->red_black_pointer->building_executed_time++;
				}
				// When industry is not busy, select new building.
				if(!is_wayne_busy && min_heap_pointer->leaf!=0) {
					work_done = 0;
					is_wayne_busy = true;
					curr = min_heap_pointer->get_minimum();
					min_heap_pointer->delete_minimum();
					curr->building_executed_time++;
					curr->red_black_pointer->building_executed_time++;
					work_done ++;
				}
				global_time++;
			}
		    process_input_command(input_command, args, min_heap_pointer, rbt_pointer, outfile);
			line_number++;
		}
		else {
			cout << "Unsupported input format";
			return 1;
		}
	}
	outfile.close();
	return 0;
}
