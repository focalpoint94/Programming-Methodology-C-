#pragma once
#include <string>
#include <fstream>

#include "misc.h"

using std::string;

class OutputBuffer {
public:
	OutputBuffer(int capacity, string file_path, string debug_file_path) : capacity(capacity), current_size(0)
	{
		buffer = new int[capacity]; //capacity = page_size(4);
		OFS = std::ofstream(file_path, std::ios::binary);
		OFS_debug = std::ofstream(debug_file_path);
	}

	~OutputBuffer()
	{
		OFS.close();
		OFS_debug.close();
		delete[] buffer;
	}

	//buffer에 매개변수 값 저장
	//buffer가 가득 찬 경우, data를 파일로 옮김
	int add(int x)
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
			return 1;
		}
		return 0;
	}

	//현재 저장된 모든 data를 파일로 옮기고
	//저장되어있던 data의 수를 return
	int fin()
	{
		for (int i = 0; i < current_size; i++)
		{
			int e;
			e = buffer[i];
			OFS.write((char*)&e, sizeof(e));
			OFS_debug << e << std::endl;
		}
		return current_size;
	}

private:
	int *buffer;
	int capacity;
	int current_size;
	std::ofstream OFS, OFS_debug;
};
