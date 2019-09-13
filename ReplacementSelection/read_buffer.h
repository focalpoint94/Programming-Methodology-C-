#pragma once
#include <string>
#include <fstream>

using std::string;

class ReadBuffer {
public:
	//ReadBuffer �迭 ������ ���� ������
	ReadBuffer() :curr_pos(0) {	}
	//ReadBuffer �迭�� ReadBuffer�� �����ϱ� ���� �Լ�
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
	//read2�� ���� read �Լ��� �ٸ�
	//read2�� curr_pos�� �ٲ��� ����
	//curr_pos == capacity�� ��� false return
	//x�� buffer�� ���� �� ������ ���, return true
	bool read2(int &x)
	{
		if (curr_pos == capacity)
		{
			return false;
		}
		x = buffer[curr_pos];
		return true;
	}
	//���ο� data set�� load�ϴ� �Լ�
	//capacity==1�� ���� ���� ���
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

	//x�� int �� ������ ��(call�Ҷ�)
	//x�� buffer�� ���� ���� ��
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
