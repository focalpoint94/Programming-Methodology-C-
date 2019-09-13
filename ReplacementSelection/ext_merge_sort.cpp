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

//MinHeap생성을 위한 class
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

	void init_insert(int input) //MinHeap에 처음 원소를 넣는 함수
	{
		arr[heap_size++] = input;
	}

	inline void swap(int i, int j)	//swap elements of arr
	{
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}

	void min_heapify(int i) //특정 index에 대해 heapify 진행
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

	void build_minheap() //MinHeap생성
	{
		for (int i = heap_size / 2; i >= 0; i--)
		{
			min_heapify(i);
		}
	}

	//MinHeap의 배열 값 return
	int getnum(int index) const
	{
		return arr[index];
	}

	//MinHeap의 배열 값 변경
	void setnum(int idx, int num)
	{
		arr[idx] = num;
	}

	//MinHeap의 heap_size 1 감소
	void dec_heap_size()
	{
		heap_size--;
	}

	//MinHeap의 heap_size를 arr_size로 변경
	void full_heap_size()
	{
		heap_size = arr_size;
	}

	//MinHeap 내부의 원소를 전체 정렬
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

	//MinHeap의 arr_size를 return
	int getarrsize()
	{
		return arr_size;
	}
	
	//debug용 함수, 사용하지 않음.
	void showall()
	{
		for (int i = 0; i < arr_size; i++)
			cout << arr[i] << endl;
	}
};

ExtMergeSort::ExtMergeSort(int data_size, int page_size, int num_pages) : data_size(data_size), page_size(page_size), num_pages(num_pages), num_of_initial_files(0) {}

void ExtMergeSort::main() {

	//initial_pass 과정 진행
	//현재 run의 총 개수 = initial_pass에서 생성된 run 수
	initial_pass();
	num_of_total = num_of_initial_files;

	vector<int> num_run_stage; //각 stage(initial->nRun=0->nRun=1->etc)별 생성되는 run의 수 저장을 위한 vector
	num_run_stage.push_back(num_of_initial_files); //initial_pass에서 생성된 run 수 저장
	int nRun = 0;
	while (1)
	{
		int init_num = 0; //이번 stage에서 현재까지 생성된 run의 개수
		int fileID = 0; //이번 stage에서 생성되는 run의 번호
		int previous = 0; //이전 stage에서 생성된 run의 개수
		previous = num_run_stage[nRun];
		int make = 0; //이번 stage에서 생성되야 하는 run의 개수
		int remainder = previous % (num_pages - 1); //make의 계산과 관련
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
			//index: getrun_size함수의 index를 계산하기 위한 변수
			int index = 0;
			if (nRun >= 1)
			{
				for (int i = 0; i < nRun; i++)
				{
					index += num_run_stage[i];
				}
			}
			
			int size = 0; //이번 run의 size 저장
			//min = ReadBuffer의 개수
			int min = num_pages - 1 < previous - init_num ? num_pages - 1 : previous - init_num; 
			ReadBuffer * ptr = new ReadBuffer[min]; //ptr = ReadBuffer의 배열
			//ReadBuffer를 min개 생성
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

			int * how_many_reads = new int[min];//각 buffer를 몇번 read했는지 저장
			for (int i = 0; i < min; i++)
				how_many_reads[i] = 0;
					

			while (1)
			{
				int temp1 = INT_MAX; //temp1에 무한대 저장
				int smallest = 0; //smallest = 가장 작은 값을 갖는 index
				int count = 0; 
				for (int i = 0; i < min; i++)
				{
					//특정 Buffer를 읽은 횟수와 runsize가 같다면, 그 Buffer는 읽기 중단
					if (how_many_reads[i] == getrun_size(index + fileID * (num_pages-1)+i))
					{
						count++;
						continue;
					}
					//temp2에 Buffer의 값을 읽어옴
					//단, 여기서 read2함수는 read와 다름
					//read함수는 curr_pos를 증가시키지만, read2는 curr_pos를 바꾸지 않음
					//reading2가 false인 경우: Buffer에 새로운 data set을 load하고, temp2에 Buffer의 값을 읽어옴
					int temp2;
					bool reading2 = ptr[i].read2(temp2);
					if (reading2 == false)
					{
						ptr[i].new_load();
						ptr[i].read2(temp2);
					}
					//temp2 < temp1인 경우
					//temp1에 temp2 저장
					//smallest에 index 저장
					if (temp2 < temp1)
					{
						temp1 = temp2;
						smallest = count;
					}
					count++;
				}
				//결과: smallest = 제일 작은 element를 갖고 있는 Buffer의 Index, temp1 = 제일 작은 element    
				//temp1에 그 값 저장 및 정식으로 읽기(curr_pos 증가)
				ptr[smallest].read(temp1);
				//Output Buffer가 가득 찬 경우, runsize를 page_size만큼 증가
				int full = ob.add(temp1);
				if (full == 1)
				{
					size += page_size;
				}
				how_many_reads[smallest]++; //해당 Buffer 읽은 것을 기록
				
				int fin = 1; //작업이 끝났는지 확인
				for (int i = 0; i < min; i++)
				{
					//각 Buffer의 읽은 횟수가 run_size와 일치하는지 확인
					//하나라도 불일치하면, 위의 과정 반복
					if (how_many_reads[i] != getrun_size(index + fileID * (num_pages-1)+i))
					{
						fin = 0;
						break;
					}
				}
				//작업이 끝난 경우
				//Output Buffer 비우고, Buffer에 저장된 data 수만큼 runsize 증가
				//현재 stage의 run 개수 증가
				//run 번호 또한 증가
				if (fin == 1)
				{
					int num = ob.fin();
					size += num;
					num_of_runs++;
					fileID++;
					break;
				}
			}
			//이번에 생성된 run의 run_size 기록
			run_size[num_of_runs - 1] = size;
			//동적할당된 메모리 반환
			delete[] how_many_reads;
			delete[] ptr;
			//이번 stage에서 생성된 run수가 이번 stage에서 생성되야 하는 run수와 일치하는지 확인
			//일치한다면 이번 stage 종료
			//nRun증가
			//전체 run 개수 update
			//이번 stage의 run 개수 update
			if (fileID == make)
			{
				nRun++;
				num_of_total += fileID;
				num_run_stage.push_back(fileID);
				break;
			}
			//nRun 한턴 끝

		}
		//이번 stage에서 생성되야 하는 run의 수가 1이라면, 최종 파일이므로 위의 과정 종료
		if (make == 1)
		{
			break;
		}
	}

	//최종 생성된 파일을 output.bin으로 다시 생성
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
	
	ReadBuffer rb(page_size, "input.bin"); //Input Buffer 생성
	
	int fileID = 0; //run의 개수 저장
	int heap_size = page_size * (num_pages - 2); //heap_size 저장
	int runsize = 0; //runsize 저장
	int read = 0; //읽은 data 수

	MinHeap MH(page_size*(num_pages-2)); //B-2개의 page로 이루어진 MinHeap 생성
	for (int i = 0; i < page_size*(num_pages - 2); i++)
	{
		int temp;
		rb.read(temp);
		MH.init_insert(temp);
		read++;
	} //Heap 생성 완료
	MH.build_minheap(); //MinHeap 생성 완료
	
	while (1)
	{
		stringstream ss_filename, ss_filename_debug;
		ss_filename << "temp_0_" << fileID;
		ss_filename_debug << "debug_temp_0_" << fileID;
		OutputBuffer ob(page_size, ss_filename.str(), ss_filename_debug.str()); //Output Buffer 생성
		
		int temp1;
		while (1)
		{
			//data를 모두 읽은 경우
			//output buffer를 비우고
			//output buffer에 있었던 data의 개수만큼 runsize 증가
			//runsize를 저장
			if (read == data_size) {
				int num = ob.fin();
				runsize += num;
				run_size[fileID] = runsize;
				fileID++;
				runsize = 0;
				break;
			}
			//temp1 = input buffer의 현재 값
			//temp2 = MinHeap의 root
			rb.read(temp1);
			int temp2 = MH.getnum(0);
			//temp1>temp2인 경우
			//temp2를 output buffer로
			//output buffer가 다 찬 경우, runsize는 page_size만큼 증가
			//MinHeap의 root를 temp1으로 대체, root에 대해 heapify 진행
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
			//temp ==temp2인 경우
			//temp1을 output buffer로
			//output buffer가 다 찬 경우, runsize는 page_size만큼 증가
			else if (temp1 == temp2)
			{
				int full= ob.add(temp1);
				if (full == 1)
				{
					runsize += page_size;
				}
			}
			//temp1<temp2인 경우
			//temp2를 output buffer로
			//output buffer가 다 찬 경우, runsize는 page_size만큼 증가
			//MinHeap의 배열 마지막 원소를 root에 저장
			//MinHeap의 배열 마지막에 temp1 저장
			//heap_size 1감소
			//MinHeap의 root 대상으로 heapify 진행
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
			read++; //data읽은 횟수 증가
			//heap_size==1인 경우
			//더이상 해당 파일에 저장할수 없음
			//output buffer를 비우고, 저장되어있던 data 수만큼 runsize 증가
			//MinHeap의 heap_size=arr_size로 설정
			//다시 MinHeap으로 만듦
			//runsize 저장
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
		//Input Buffer의 read가 끝난 경우
		if (read == data_size)
		{
			break;
		}
	}
	stringstream ss_filename, ss_filename_debug;
	ss_filename << "temp_0_" << fileID;
	ss_filename_debug << "debug_temp_0_" << fileID;
	OutputBuffer ob(page_size, ss_filename.str(), ss_filename_debug.str()); //Output Buffer 생성
	
	MH.sorting(); //MinHeap의 모든 원소를 정렬
	//MinHeap의 모든 원소를 output buffer로
	//마지막 runsize 계산 및 저장
	//initial_pass로 생성된 파일 수 저장
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
