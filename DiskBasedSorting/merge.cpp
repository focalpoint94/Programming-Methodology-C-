#include "merge.h"
#include "read_buffer.h"
#include "output_buffer.h"

void merge(int page_size, string in_file_path1, string in_file_path2,
	string out_file_path, string debug_out_file_path)
{
	//* page_size = 4
	//* in_file_path1과 in_file_path2에 sorted된 data가 저장되어있음
	// 0. page_size 단위의 buffer가 3개존재(read 2개, output 1개, 각각의 memory size = page_size)
	// 1. read buffer 2개 : binary input 받아온다
	// 2. output buffer 1개 : 2개의 read buffer로부터 선택적으로 int 하나씩 받아온다
	// 3. output buffer가 가득 찬 경우 파일로 보낸다
	// 4. input buffer에 저장된 entry가 모두 선택된 경우, data를 새롭게 load하거나, 더이상 load할 data가 없는 경우 false return
	
	ReadBuffer rb1(page_size, in_file_path1);
	ReadBuffer rb2(page_size, in_file_path2);
	OutputBuffer ob(page_size, out_file_path, debug_out_file_path);
	// readbuffer 2개와 outputbuffer 1개 생성

	int inp1;
	rb1.read(inp1);
	int inp2;
	rb2.read(inp2);
	// inp1과 inp2에 각각 rb1과 rb2의 첫번째 entry 저장

	bool keep1, keep2; // rb1과 rb2의 reading의 success/failure 여부 저장 
	while (1)
	{
		if (inp1 < inp2)
		{
			ob.add(inp1);
			keep1 = rb1.read(inp1);
			if (keep1 == false)
			{
				break;
			}
		}
		else
		{
			ob.add(inp2);
			keep2 = rb2.read(inp2);
			if (keep2 == false)
			{
				break;
			}
		}
	}
	/*
	// inp1 < inp2인 경우: outputbuffer에 inp1 저장 -> inp1에 rb1의 다음 entry 저장. 만약 reading이 failure일 경우 전체 과정 반복 중지
	// inp1 >= inp2인 경우: outputbuffer에 inp2 저장 -> inp2에 rb2의 다음 entry 저장. 만약 reading이 failure일 경우 전체 과정 반복 중지
	*/
	if (keep1 == false)
	{
		do
		{
			ob.add(inp2);
		} while (rb2.read(inp2));
	}
	else
	{
		do
		{
			ob.add(inp1);
		} while (rb1.read(inp1));
	}
	/*
	// reading failure가 rb1에서 발생하였는지, rb2에서 발생하였는지 확인
	// 만약 rb1에서 reading failure가 발생했다면, outputbuffer에 inp2를 저장하고, inp2에 rb2의 다음 entry를 저장한다-> rb2의 reading이 failure일 때까지 전체 과정 반복
	// 만약 rb2에서 reading failure가 발생했다면, outputbuffer에 inp1을 저장하고, inp1에 rb1의 다음 entry를 저장한다-> rb1의 reading이 failure일 때까지 전체 과정 반복
	*/
}

