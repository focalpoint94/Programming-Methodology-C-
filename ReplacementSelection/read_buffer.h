#pragma once
#include <string>
#include <fstream>

using std::string;

class ReadBuffer {
public:
	//ReadBuffer 배열 생성을 위한 생성자
	ReadBuffer() :curr_pos(0) {	}
	//ReadBuffer 배열의 ReadBuffer를 설정하기 위한 함수
	void setreadbuffer(int capacity, string filename)
	{
		this->capacity = capacity;
		buffer = new int[capacity];
		IFS = std::ifstream(filename, std::ios::binary);
		int e;
		for (int i = 0; i < capacity; i++)
		{
			IFS.read((char*)&e, sizeof(e));
			buffer[i] = e;
		}
	}
	ReadBuffer(int capacity, string filename): capacity(capacity), curr_pos(0)
	{
		buffer = new int[capacity];
		IFS = std::ifstream(filename, std::ios::binary);
		int e;
		for (int i = 0; i < capacity; i++)
		{
			IFS.read((char*)&e, sizeof(e));
			buffer[i] = e;
		}
	}
	~ReadBuffer()
	{
		IFS.close();
		delete[] buffer;
	}
	//read2와 밑의 read 함수는 다름
	//read2는 curr_pos를 바꾸지 않음
	//curr_pos == capacity의 경우 false return
	//x에 buffer의 현재 값 저장한 경우, return true
	bool read2(int &x)
	{
		if (curr_pos == capacity)
		{
			return false;
		}
		x = buffer[curr_pos];
		return true;
	}
	//새로운 data set을 load하는 함수
	//capacity==1인 경우는 따로 취급
	void new_load()
	{
		int e;
		int i = 0;
		if (IFS.read((char*)&e, sizeof(e)))
		{
			buffer[i++] = e;
			if (capacity == 1)
			{
				curr_pos = 0;
				return;
			}
			while (IFS.read((char*)&e, sizeof(e)))
			{
				buffer[i++] = e;
				if (i == capacity)
					break;
			}
			curr_pos = 0;
		}
	}

	//x를 int 형 변수로 줌(call할때)
	//x에 buffer의 현재 값을 줌
	bool read(int &x)
	{
		if (curr_pos == capacity)
		{
			int e;
			int i = 0;
			if (IFS.read((char*)&e, sizeof(e)))
			{
				buffer[i++] = e;
				if (capacity == 1)
				{
					curr_pos = 0;
					x = buffer[curr_pos];
					curr_pos++;
					return true;
				}
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
	}

private:
	int *buffer;
	int capacity;
	int curr_pos;
	std::ifstream IFS;
};
