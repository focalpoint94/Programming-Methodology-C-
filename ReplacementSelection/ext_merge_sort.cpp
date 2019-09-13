#include "ext_merge_sort.h"

#include <sstream>
#include <iostream>
#include <fstream>

#include "misc.h"
#include "read_buffer.h"
#include "output_buffer.h"
#include <cstdlib>
#include <vector>

using std::stringstream;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::vector;

//MinHeap������ ���� class
class MinHeap
{
private:
	int* arr;
	size_t arr_size;
	size_t heap_size;
public:
	MinHeap(int arr_size) :arr_size(arr_size), heap_size(0)
	{
		arr = new int[arr_size];
	}
	~MinHeap()
	{
		delete[] arr;
	}

	void init_insert(int input) //MinHeap�� ó�� ���Ҹ� �ִ� �Լ�
	{
		arr[heap_size++] = input;
	}

	inline void swap(int i, int j)	//swap elements of arr
	{
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}

	void min_heapify(int i) //Ư�� index�� ���� heapify ����
	{
		int l = 2 * i + 1;
		int r = 2 * i + 2;
		int smallest_idx = i;
		if (l < heap_size && arr[l] < arr[i])
		{
			smallest_idx = l;
		}
		if (r < heap_size && arr[r] < arr[smallest_idx])
		{
			smallest_idx = r;
		}
		if (smallest_idx != i)
		{
			swap(i, smallest_idx);
			//exchange arr[i] & arr[smallest_idx]
			min_heapify(smallest_idx);
		}
	}

	void build_minheap() //MinHeap����
	{
		for (int i = heap_size / 2; i >= 0; i--)
		{
			min_heapify(i);
		}
	}

	//MinHeap�� �迭 �� return
	int getnum(int index) const
	{
		return arr[index];
	}

	//MinHeap�� �迭 �� ����
	void setnum(int idx, int num)
	{
		arr[idx] = num;
	}

	//MinHeap�� heap_size 1 ����
	void dec_heap_size()
	{
		heap_size--;
	}

	//MinHeap�� heap_size�� arr_size�� ����
	void full_heap_size()
	{
		heap_size = arr_size;
	}

	//MinHeap ������ ���Ҹ� ��ü ����
	void sorting()
	{
		for (int i = 0; i < arr_size - 1; i++)
		{
			for (int j = 0; j < arr_size - 1 - i; j++)
			{
				if (arr[j] > arr[j + 1])
				{
					int temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}
	}

	//MinHeap�� arr_size�� return
	int getarrsize()
	{
		return arr_size;
	}
	
	//debug�� �Լ�, ������� ����.
	void showall()
	{
		for (int i = 0; i < arr_size; i++)
			cout << arr[i] << endl;
	}
};

ExtMergeSort::ExtMergeSort(int data_size, int page_size, int num_pages) : data_size(data_size), page_size(page_size), num_pages(num_pages), num_of_initial_files(0) {}

void ExtMergeSort::main() {

	//initial_pass ���� ����
	//���� run�� �� ���� = initial_pass���� ������ run ��
	initial_pass();
	num_of_total = num_of_initial_files;

	vector<int> num_run_stage; //�� stage(initial->nRun=0->nRun=1->etc)�� �����Ǵ� run�� �� ������ ���� vector
	num_run_stage.push_back(num_of_initial_files); //initial_pass���� ������ run �� ����
	int nRun = 0;
	while (1)
	{
		int init_num = 0; //�̹� stage���� ������� ������ run�� ����
		int fileID = 0; //�̹� stage���� �����Ǵ� run�� ��ȣ
		int previous = 0; //���� stage���� ������ run�� ����
		previous = num_run_stage[nRun];
		int make = 0; //�̹� stage���� �����Ǿ� �ϴ� run�� ����
		int remainder = previous % (num_pages - 1); //make�� ���� ����
		if (remainder == 0)
		{
			make = previous / (num_pages - 1);
		}
		else
		{
			make = previous / (num_pages - 1) + 1;
		}

		while (1)
		{
			//index: getrun_size�Լ��� index�� ����ϱ� ���� ����
			int index = 0;
			if (nRun >= 1)
			{
				for (int i = 0; i < nRun; i++)
				{
					index += num_run_stage[i];
				}
			}
			
			int size = 0; //�̹� run�� size ����
			//min = ReadBuffer�� ����
			int min = num_pages - 1 < previous - init_num ? num_pages - 1 : previous - init_num; 
			ReadBuffer * ptr = new ReadBuffer[min]; //ptr = ReadBuffer�� �迭
			//ReadBuffer�� min�� ����
			int count = 0;
			while (count < min)
			{
				stringstream ss_in;
				ss_in << "temp_" << nRun << "_" << init_num;
				ptr[count].setreadbuffer(page_size, ss_in.str());
				init_num++;
				count++;
			}

			stringstream ss_out, ss_out_debug;
			ss_out << "temp_" << nRun + 1 << "_" << fileID;
			ss_out_debug << "debug_temp_" << nRun + 1 << "_" << fileID;
			OutputBuffer ob(page_size, ss_out.str(), ss_out_debug.str());

			int * how_many_reads = new int[min];//�� buffer�� ��� read�ߴ��� ����
			for (int i = 0; i < min; i++)
				how_many_reads[i] = 0;
					

			while (1)
			{
				int temp1 = INT_MAX; //temp1�� ���Ѵ� ����
				int smallest = 0; //smallest = ���� ���� ���� ���� index
				int count = 0; 
				for (int i = 0; i < min; i++)
				{
					//Ư�� Buffer�� ���� Ƚ���� runsize�� ���ٸ�, �� Buffer�� �б� �ߴ�
					if (how_many_reads[i] == getrun_size(index + fileID * (num_pages-1)+i))
					{
						count++;
						continue;
					}
					//temp2�� Buffer�� ���� �о��
					//��, ���⼭ read2�Լ��� read�� �ٸ�
					//read�Լ��� curr_pos�� ������Ű����, read2�� curr_pos�� �ٲ��� ����
					//reading2�� false�� ���: Buffer�� ���ο� data set�� load�ϰ�, temp2�� Buffer�� ���� �о��
					int temp2;
					bool reading2 = ptr[i].read2(temp2);
					if (reading2 == false)
					{
						ptr[i].new_load();
						ptr[i].read2(temp2);
					}
					//temp2 < temp1�� ���
					//temp1�� temp2 ����
					//smallest�� index ����
					if (temp2 < temp1)
					{
						temp1 = temp2;
						smallest = count;
					}
					count++;
				}
				//���: smallest = ���� ���� element�� ���� �ִ� Buffer�� Index, temp1 = ���� ���� element    
				//temp1�� �� �� ���� �� �������� �б�(curr_pos ����)
				ptr[smallest].read(temp1);
				//Output Buffer�� ���� �� ���, runsize�� page_size��ŭ ����
				int full = ob.add(temp1);
				if (full == 1)
				{
					size += page_size;
				}
				how_many_reads[smallest]++; //�ش� Buffer ���� ���� ���
				
				int fin = 1; //�۾��� �������� Ȯ��
				for (int i = 0; i < min; i++)
				{
					//�� Buffer�� ���� Ƚ���� run_size�� ��ġ�ϴ��� Ȯ��
					//�ϳ��� ����ġ�ϸ�, ���� ���� �ݺ�
					if (how_many_reads[i] != getrun_size(index + fileID * (num_pages-1)+i))
					{
						fin = 0;
						break;
					}
				}
				//�۾��� ���� ���
				//Output Buffer ����, Buffer�� ����� data ����ŭ runsize ����
				//���� stage�� run ���� ����
				//run ��ȣ ���� ����
				if (fin == 1)
				{
					int num = ob.fin();
					size += num;
					num_of_runs++;
					fileID++;
					break;
				}
			}
			//�̹��� ������ run�� run_size ���
			run_size[num_of_runs - 1] = size;
			//�����Ҵ�� �޸� ��ȯ
			delete[] how_many_reads;
			delete[] ptr;
			//�̹� stage���� ������ run���� �̹� stage���� �����Ǿ� �ϴ� run���� ��ġ�ϴ��� Ȯ��
			//��ġ�Ѵٸ� �̹� stage ����
			//nRun����
			//��ü run ���� update
			//�̹� stage�� run ���� update
			if (fileID == make)
			{
				nRun++;
				num_of_total += fileID;
				num_run_stage.push_back(fileID);
				break;
			}
			//nRun ���� ��

		}
		//�̹� stage���� �����Ǿ� �ϴ� run�� ���� 1�̶��, ���� �����̹Ƿ� ���� ���� ����
		if (make == 1)
		{
			break;
		}
	}

	//���� ������ ������ output.bin���� �ٽ� ����
	stringstream fin_in;
	fin_in << "temp_" << nRun << "_" << 0;
	ifstream fin(fin_in.str(), std::ios::binary);
	std::ofstream fout("output.bin", std::ios::binary);
	int e;
	for (int i = 0; i < data_size; i++)
	{
		fin.read((char*)&e, sizeof(e));
		fout.write((char*)&e, sizeof(e));
	}
	fin.close();
	fout.close();
}



void ExtMergeSort::initial_pass() {
	
	ReadBuffer rb(page_size, "input.bin"); //Input Buffer ����
	
	int fileID = 0; //run�� ���� ����
	int heap_size = page_size * (num_pages - 2); //heap_size ����
	int runsize = 0; //runsize ����
	int read = 0; //���� data ��

	MinHeap MH(page_size*(num_pages-2)); //B-2���� page�� �̷���� MinHeap ����
	for (int i = 0; i < page_size*(num_pages - 2); i++)
	{
		int temp;
		rb.read(temp);
		MH.init_insert(temp);
		read++;
	} //Heap ���� �Ϸ�
	MH.build_minheap(); //MinHeap ���� �Ϸ�
	
	while (1)
	{
		stringstream ss_filename, ss_filename_debug;
		ss_filename << "temp_0_" << fileID;
		ss_filename_debug << "debug_temp_0_" << fileID;
		OutputBuffer ob(page_size, ss_filename.str(), ss_filename_debug.str()); //Output Buffer ����
		
		int temp1;
		while (1)
		{
			//data�� ��� ���� ���
			//output buffer�� ����
			//output buffer�� �־��� data�� ������ŭ runsize ����
			//runsize�� ����
			if (read == data_size) {
				int num = ob.fin();
				runsize += num;
				run_size[fileID] = runsize;
				fileID++;
				runsize = 0;
				break;
			}
			//temp1 = input buffer�� ���� ��
			//temp2 = MinHeap�� root
			rb.read(temp1);
			int temp2 = MH.getnum(0);
			//temp1>temp2�� ���
			//temp2�� output buffer��
			//output buffer�� �� �� ���, runsize�� page_size��ŭ ����
			//MinHeap�� root�� temp1���� ��ü, root�� ���� heapify ����
			if (temp1 > temp2)
			{
				int full = ob.add(temp2);
				if (full == 1)
				{
					runsize += page_size;
				}
				MH.setnum(0, temp1);
				MH.min_heapify(0);
			}
			//temp ==temp2�� ���
			//temp1�� output buffer��
			//output buffer�� �� �� ���, runsize�� page_size��ŭ ����
			else if (temp1 == temp2)
			{
				int full= ob.add(temp1);
				if (full == 1)
				{
					runsize += page_size;
				}
			}
			//temp1<temp2�� ���
			//temp2�� output buffer��
			//output buffer�� �� �� ���, runsize�� page_size��ŭ ����
			//MinHeap�� �迭 ������ ���Ҹ� root�� ����
			//MinHeap�� �迭 �������� temp1 ����
			//heap_size 1����
			//MinHeap�� root ������� heapify ����
			else
			{
				int full = ob.add(temp2);
				if (full == 1)
				{
					runsize += page_size;
				}
				MH.setnum(0, MH.getnum(heap_size - 1));
				MH.setnum(heap_size - 1, temp1);
				heap_size--;
				MH.dec_heap_size();
				MH.min_heapify(0);
			}
			read++; //data���� Ƚ�� ����
			//heap_size==1�� ���
			//���̻� �ش� ���Ͽ� �����Ҽ� ����
			//output buffer�� ����, ����Ǿ��ִ� data ����ŭ runsize ����
			//MinHeap�� heap_size=arr_size�� ����
			//�ٽ� MinHeap���� ����
			//runsize ����
			if (heap_size == 1)
			{
				int num = ob.fin();
				runsize += num;
				MH.full_heap_size();
				heap_size = page_size * (num_pages - 2);
				MH.build_minheap();
				run_size[fileID] = runsize;
				fileID++;
				runsize = 0;
				break;
			}
		}
		//Input Buffer�� read�� ���� ���
		if (read == data_size)
		{
			break;
		}
	}
	stringstream ss_filename, ss_filename_debug;
	ss_filename << "temp_0_" << fileID;
	ss_filename_debug << "debug_temp_0_" << fileID;
	OutputBuffer ob(page_size, ss_filename.str(), ss_filename_debug.str()); //Output Buffer ����
	
	MH.sorting(); //MinHeap�� ��� ���Ҹ� ����
	//MinHeap�� ��� ���Ҹ� output buffer��
	//������ runsize ��� �� ����
	//initial_pass�� ������ ���� �� ����
	for (int i = 0; i < MH.getarrsize(); i++)
	{
		int full = ob.add(MH.getnum(i));
		if (full == 1)
		{
			runsize += page_size;
		}
	}
	int num = ob.fin();
	runsize += num;
	run_size[fileID] = runsize;
	num_of_initial_files = fileID + 1;
	num_of_runs = num_of_initial_files;

}
