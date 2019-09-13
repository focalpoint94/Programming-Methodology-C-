

#include <iostream>

#include "run_ext_sort.h"
#include "misc.h"

#include <fstream>
#include <sstream>

using std::stringstream;

int main() {

	//data_size, page_size, num_pages 입력
	const int data_size = 200;
	const int page_size = 2;
	const int num_pages = 4;
	//Input data 생성 및 external sorting 진행
	gen_data("input.bin", data_size);
	run_ext_sort(data_size, page_size, num_pages);
	std::cout << "Finished" << std::endl;
	
	   	 

	//이 밑은 검증과정
	std::ifstream fin("input.bin", std::ios::binary);
	std::ofstream fout("input_sorted.bin", std::ios::binary);
	//File "input_sorted.bin": "output.bin"파일이랑 비교하기 위한 용도.
	int e;
	int * arr = new int[data_size];
	for (int i = 0; i < data_size; i++)
	{
		fin.read((char*)&e, sizeof(e));
		arr[i] = e;
	}
	fin.close();
	//Bubble sorting arr[i]
	for (int i = 0; i < data_size - 1; i++)
	{
		for (int j = 0; j < data_size - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	//input_sorted.bin에 정렬된 data 저장
	for (int i = 0; i < data_size; i++)
	{
		fout.write((char*)&arr[i], sizeof(arr[i]));
	}
	fout.close();
	delete[] arr;
	   

	// "output.bin"과 "input_sorted.bin"의 비교를 통한 검증
	std::ifstream f1("output.bin", std::ios::binary);
	std::ifstream f2("input_sorted.bin", std::ios::binary);
	int e1, e2;
	int flag = 1;
	std::cout << "Final Test" << std::endl;
	for (int i = 0; i < data_size; i++)
	{
		f1.read((char*)&e1, sizeof(e1));
		f2.read((char*)&e2, sizeof(e2));
		std::cout << e1 << "," << e2 << std::endl;
		if (e1 != e2)
		{
			flag = 0;
			break;
		}
	}
	if (flag == 1)
	{
		std::cout << std::endl << std::endl;
		std::cout << "Matched" << std::endl << std::endl << std::endl;
	}
	f1.close();
	f2.close();

	return 0;
}

