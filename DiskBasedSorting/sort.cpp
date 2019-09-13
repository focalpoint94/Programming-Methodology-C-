#include "sort.h"

void sort(int arr[], int len)
{
	quick_sort(arr, 0, len - 1);
}
// sorting algorithm으로 quick_sort 사용
// p <=r일 때만 동작
// q = partition -> p~q-1까지 sort, q+1~r까지 sort.
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
// pivot을 기준으로 작은 value들과 큰 value들은 분리, pivot의 index return.
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