#pragma once
#include <string>
#include <fstream>

using std::string;

class ReadBuffer {
public:
	// ReadBuffer Constructor
	// initialize capacity, curr_pos(0) and newly allocate buffer & open a input file + read integers from the file (#of integers = capacity)
	ReadBuffer(int capacity, string filename): capacity(capacity), curr_pos(0)
	{
		buffer = new int[capacity]; //capacity = pge_size(4);
		IFS = std::ifstream(filename, std::ios::binary); //IFS으로 input file open
		int e;
		for (int i = 0; i < capacity; i++)
		{
			IFS.read((char*)&e, sizeof(e));
			buffer[i] = e;
		}
	}
	//	Allocate the array 'buffer'. Open IFS.
	// ReadBuffer Destructor
	// release buffer & close file
	~ReadBuffer()
	{
		delete[] buffer;
		IFS.close();
	}
	//	Release the array 'buffer'. Close IFS.
	// if function 'read'is called, x = buffer[curr_pos++] and return true
	// if buffer is emtpty(curr_pos == capacity), read integers from the input file
	// if reading failed, then return false
	bool read(int &x)
	{
		//x를 int 형 변수로 준다.(call할때)
		//x값을 buffer값을 준다.
		if (curr_pos == capacity)
		{
			int e;
			int i = 0;
			if (IFS.read((char*)&e, sizeof(e)))
			{
				buffer[i++] = e;
				while (IFS.read((char*)&e, sizeof(e)))
				{
					buffer[i++] = e;
					if (i == capacity)
						break;
				}
				curr_pos = 0;
			}
			else
			{
				return false;
			}
		}
		x = buffer[curr_pos];
		curr_pos++;
		return true;
	}// Means to read a one integer from the buffer
	/*
		If the buffer is empty,
			Read the integers of the size of capacity.
			If the reading is failed, return false.
			If the reading is successful, curr_pos = 0
		Set 'x' with the current position in the buffer.
	*/
private:
	int *buffer;
	int capacity;
	int curr_pos;
	std::ifstream IFS;
};
