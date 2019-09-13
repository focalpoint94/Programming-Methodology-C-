#pragma once
#include <iostream>
class ExtMergeSort {
public:
	ExtMergeSort(int data_size, int page_size, int num_pages);
	void main(); //initial_pass + merge과정
	int getrun_size(int i) //저장된 run_size를 return하는 함수
	{
		return run_size[i];
	}
	void showrun_size() //debug용 함수, 사용하지 않음
	{
		for(int i=0; i<num_of_total; i++)
			std::cout << run_size[i] << std::endl;
	}
private:
	const int data_size; 
	const int page_size;
	const int num_pages; 
	int num_of_initial_files; //initial_pass에서 생성되는 파일 수 저장
	void initial_pass(); //initial_pass 과정
	int run_size[1000]; //run_size 저장하는 배열, 크게 할수록 작은 page_size에서 동작 가능
	int num_of_runs; //현재(nRun)의 run 개수 저장
	int num_of_total; //전체 run 개수 저장
};
