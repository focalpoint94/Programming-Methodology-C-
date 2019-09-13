/*
 * 3 buffer pages
 */

#include <iostream>

#include "run_ext_sort.h"
#include "misc.h"

#include <fstream>
#include <sstream>

using std::stringstream;

int main() {
	const int page_size = 4;
	const int initial_buffer_size = 3 * page_size;
	const int data_size = initial_buffer_size * 2 * 2;

	gen_data("input.bin", data_size);
	run_ext_sort(page_size); // implement this
	std::cout << "Finished" << std::endl;
	
	return 0;
}

