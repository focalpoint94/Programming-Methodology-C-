#pragma once
#include <iostream>
class ExtMergeSort {
public:
	ExtMergeSort(int data_size, int page_size, int num_pages);
	void main(); //initial_pass + merge����
	int getrun_size(int i) //����� run_size�� return�ϴ� �Լ�
	{
		return run_size[i];
	}
	void showrun_size() //debug�� �Լ�, ������� ����
	{
		for(int i=0; i<num_of_total; i++)
			std::cout << run_size[i] << std::endl;
	}
private:
	const int data_size; 
	const int page_size;
	const int num_pages; 
	int num_of_initial_files; //initial_pass���� �����Ǵ� ���� �� ����
	void initial_pass(); //initial_pass ����
	int run_size[1000]; //run_size �����ϴ� �迭, ũ�� �Ҽ��� ���� page_size���� ���� ����
	int num_of_runs; //����(nRun)�� run ���� ����
	int num_of_total; //��ü run ���� ����
};
