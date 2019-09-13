#include "merge.h"
#include "read_buffer.h"
#include "output_buffer.h"

void merge(int page_size, string in_file_path1, string in_file_path2,
	string out_file_path, string debug_out_file_path)
{
	//* page_size = 4
	//* in_file_path1�� in_file_path2�� sorted�� data�� ����Ǿ�����
	// 0. page_size ������ buffer�� 3������(read 2��, output 1��, ������ memory size = page_size)
	// 1. read buffer 2�� : binary input �޾ƿ´�
	// 2. output buffer 1�� : 2���� read buffer�κ��� ���������� int �ϳ��� �޾ƿ´�
	// 3. output buffer�� ���� �� ��� ���Ϸ� ������
	// 4. input buffer�� ����� entry�� ��� ���õ� ���, data�� ���Ӱ� load�ϰų�, ���̻� load�� data�� ���� ��� false return
	
	ReadBuffer rb1(page_size, in_file_path1);
	ReadBuffer rb2(page_size, in_file_path2);
	OutputBuffer ob(page_size, out_file_path, debug_out_file_path);
	// readbuffer 2���� outputbuffer 1�� ����

	int inp1;
	rb1.read(inp1);
	int inp2;
	rb2.read(inp2);
	// inp1�� inp2�� ���� rb1�� rb2�� ù��° entry ����

	bool keep1, keep2; // rb1�� rb2�� reading�� success/failure ���� ���� 
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
	// inp1 < inp2�� ���: outputbuffer�� inp1 ���� -> inp1�� rb1�� ���� entry ����. ���� reading�� failure�� ��� ��ü ���� �ݺ� ����
	// inp1 >= inp2�� ���: outputbuffer�� inp2 ���� -> inp2�� rb2�� ���� entry ����. ���� reading�� failure�� ��� ��ü ���� �ݺ� ����
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
	// reading failure�� rb1���� �߻��Ͽ�����, rb2���� �߻��Ͽ����� Ȯ��
	// ���� rb1���� reading failure�� �߻��ߴٸ�, outputbuffer�� inp2�� �����ϰ�, inp2�� rb2�� ���� entry�� �����Ѵ�-> rb2�� reading�� failure�� ������ ��ü ���� �ݺ�
	// ���� rb2���� reading failure�� �߻��ߴٸ�, outputbuffer�� inp1�� �����ϰ�, inp1�� rb1�� ���� entry�� �����Ѵ�-> rb1�� reading�� failure�� ������ ��ü ���� �ݺ�
	*/
}

