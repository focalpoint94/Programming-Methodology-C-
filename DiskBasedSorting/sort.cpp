#include "sort.h"

void sort(int arr[], int len)
{
	quick_sort(arr, 0, len - 1);
}
// sorting algorithm���� quick_sort ���
// p <=r�� ���� ����
// q = partition -> p~q-1���� sort, q+1~r���� sort.
void quick_sort(int arr[], int p, int r)
{
	if (p <= r)
	{
		int q = partition(arr, p, r);
		quick_sort(arr, p, q - 1);
		quick_sort(arr, q + 1, r);
	}
	else
		return;
}
// pivot = arr[r];
// pivot�� �������� ���� value��� ū value���� �и�, pivot�� index return.
int partition(int arr[], int p, int r)
{
	int pivot = arr[r];
	int i = p - 1;
	int j;
	int temp;
	for (j = p; j < r; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			//exchange arr[i], arr[j]
		}
	}
	temp = arr[i + 1];
	arr[i + 1] = arr[j];
	arr[j] = temp;
	//exchange arr[j], arr[i+1]
	return i + 1;
	//return i+1
}