#pragma once
#include <string>
#include <fstream>

#include "misc.h"

using std::string;

class OutputBuffer {
public:
	// OutputBuffer Constructor
	// initialize capacity & current_size, newly allocate buffer & open files
	OutputBuffer(int capacity, string file_path, string debug_file_path) : capacity(capacity), current_size(0)
	{
		buffer = new int[capacity]; //capacity = page_size(4);
		OFS = std::ofstream(file_path, std::ios::binary);
		OFS_debug = std::ofstream(debug_file_path);
	}
	//	Allocate the array 'buffer'. Open OFS, OFS_debug.
	// OutputBuffer Destructor
	// close files & release buffer
	~OutputBuffer()
	{
		OFS.close();
		OFS_debug.close();
		delete[] buffer;
	}// Close the OFS, OFS_debug. Release the array 'buffer'
	// Add a int to the buffer array
	// if buffer is full, write all the contents of the buffer to the files & clear the buffer by setting current_size = 0
	void add(int x)
	{
		buffer[current_size++] = x;

		if (current_size == capacity)
		{
			for (int i = 0; i < capacity; i++)
			{
				int e;
				e = buffer[i];
				OFS.write((char*)&e, sizeof(e));
				OFS_debug << e << std::endl;
			}
			current_size = 0;
		}
	}
	/*
		Add one integer to the 'buffer'.
		If the buffer is full,
			Write the contents of the buffer to the files.
			Clear the buffer (current_size = 0).
	*/

private:
	int *buffer;
	int capacity;
	int current_size;
	std::ofstream OFS, OFS_debug;
};
