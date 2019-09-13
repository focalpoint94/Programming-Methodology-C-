#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <ctime>
#include <cstdlib> // srand, rand
#include <climits> // INT_MAX

using namespace std;


int quick_sort(double arr[], int p, int r, clock_t);
int partition(double arr[], int p, int r);
int merge_sort(double arr[], int left, int right, clock_t);
int insertion_sort(double arr[], int size);
int stooge_sort(double arr[], int left, int right, clock_t);


class QuickSort {
public:
	/*
	Input : -
	Output : -
	Function Description :
	- prints out class member variable 'seconds'
	*/
	void print_time() const {
		cout << "QuickSort : " << seconds << " sec" << endl;
	}

	/*
	Input : -
	Output : -
	Function Description :
	- allocate an array(size of 10) to arr
	- initialize arr with {1,2,3,4,5,6,7,8,9,10}
	- initialize seconds(0) & size(10)
	*/
	// implement the following functions
	QuickSort() {
		// constructor
		arr = new double[10];
		for (int i = 0; i < 10; i++)
		{
			arr[i] = i + 1;
		}
		seconds = 0;
		size = 10;
	}
	/*
	Input : -
	Output : -
	Function Description :
	- deallocate arr
	*/
	~QuickSort() {
		// destructor
		delete[] arr;
	}
	/*
	Input : -
	Output : -
	Function Description :
	- record start time in start_time
	- run quick_sort
	- record end time in end_time
	- if runtime <= 10, seconds = sorting runtime
	- if runtime > 10, seconds = 10.000 and prints out a message
	*/
	void run() {
		// sorting algorithm is applied
		// elapsed time is also recorded in seconds
		clock_t start_time = clock();
		int a = quick_sort(arr, 0, size - 1, start_time);
		clock_t end_time = clock();
		seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		if(a==0 || seconds >= 10)
		{
			seconds = 10.000;
			cout << "Terminated due to the time limit" << endl;
		}
	}

	/*
	Input : arr, size
	Output : -
	Function Description :
	- delete arr that has been allocated during class construction
	- initialize class member variable size, makes new array
	- deep copy to class member variable arr
	*/
	void set(double *arr, int size) {
		// new input array and its size are set
		delete[] this->arr;
		this->size = size;
		this->arr = new double[size];
		for (int i = 0; i < size; i++)
		{
			this->arr[i] = arr[i];
		}
	}
	/*
	Input : QuickSort pointer
	Output : True or False
	Function Description :
	- checks whether class member array is sorted
	*/
	friend bool check_quick(QuickSort *quick_sort);

private:
	double *arr;
	int size;
	double seconds;
};

class MergeSort {
public:
	/*
	Input : -
	Output : - 
	Function Description :
	- prints out class member variable 'seconds'
	*/
	void print_time() const {
		cout << "MergeSort : " << seconds << " sec" << endl;
	}
	/*
	Input : -
	Output : -
	Function Description :
	- allocate an array(size of 10) to arr
	- initialize arr with {1,2,3,4,5,6,7,8,9,10}
	- initialize seconds(0) & size(10)
	*/
	// implement the following functions
	MergeSort() {
		// constructor
		arr = new double[10];
		for (int i = 0; i < 10; i++)
		{
			arr[i] = i + 1;
		}
		seconds = 0;
		size = 10;
	}
	/*
	Input : -
	Output : -
	Function Description :
	- deallocate arr
	*/
	~MergeSort() {
		// destructor
		delete[] arr;
	}
	/*
	Input : -
	Output : -
	Function Description :
	- record start time in start_time
	- run merge_sort
	- record end time in end_time
	- if runtime <= 10, seconds = sorting runtime
	- if runtime > 10, seconds = 10.000 and prints out a message
	*/
	void run() {
		// sorting algorithm is applied
		// elapsed time is also recorded in seconds
		clock_t start_time = clock();
		int a = merge_sort(arr, 0, size - 1, start_time);
		clock_t end_time = clock();
		seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		if (a == 0 || seconds >= 10)
		{
			seconds = 10.000;
			cout << "Terminated due to the time limit" << endl;
		}
	}
	/*
	Input : arr, size
	Output : -
	Function Description :
	- delete arr that has been allocated during class construction
	- initialize class member variable size, makes new array
	- deep copy to class member variable arr
	*/
	void set(double *arr, int size) {
		// new input array and its size are set
		delete[] this->arr;
		this->size = size;
		this->arr = new double[size];
		for (int i = 0; i < size; i++)
		{
			this->arr[i] = arr[i];
		}
	}
	/*
	Input : MergeSort pointer
	Output : True or False
	Function Description :
	- checks whether class member array is sorted
	*/
	friend bool check_merge(MergeSort *merge_sort);

private:
	double *arr;
	int size;
	double seconds;

};

class InsertionSort {
public:
	/*
	Input : -
	Output : -
	Function Description :
	- prints out class member variable 'seconds'
	*/
	void print_time() const {
		cout << "InsertionSort : " << seconds << " sec" << endl;
	}
	/*
	Input : -
	Output : -
	Function Description :
	- allocate an array(size of 10) to arr
	- initialize arr with {1,2,3,4,5,6,7,8,9,10}
	- initialize seconds(0) & size(10)
	*/
	// implement the following functions
	InsertionSort() {
		// constructor
		arr = new double[10];
		for (int i = 0; i < 10; i++)
		{
			arr[i] = i + 1;
		}
		seconds = 0;
		size = 10;
	}
	/*
	Input : -
	Output : -
	Function Description :
	- deallocate arr
	*/
	~InsertionSort() {
		// destructor
		delete[] arr;
	}
	/*
	Input : -
	Output : -
	Function Description :
	- record start time in start_time
	- run insertion_sort
	- record end time in end_time
	- if runtime <= 10, seconds = sorting runtime
	- if runtime > 10, seconds = 10.000 and prints out a message
	*/
	void run() {
		// sorting algorithm is applied
		// elapsed time is also recorded in seconds
		clock_t start_time = clock();
		int a = insertion_sort(arr, size);
		clock_t end_time = clock();
		seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		if (a == 0 || seconds >= 10)
		{
			seconds = 10.000;
			cout << "Terminated due to the time limit" << endl;
		}
	}
	/*
	Input : arr, size
	Output : -
	Function Description :
	- delete arr that has been allocated during class construction
	- initialize class member variable size, makes new array
	- deep copy to class member variable arr
	*/
	void set(double *arr, int size) {
		// new input array and its size are set
		delete[] this->arr;
		this->size = size;
		this->arr = new double[size];
		for (int i = 0; i < size; i++)
		{
			this->arr[i] = arr[i];
		}
	}
	/*
	Input : InsertionSort pointer
	Output : True or False
	Function Description :
	- checks whether class member array is sorted
	*/
	friend bool check_insertion(InsertionSort *insertion_sort);

private:
	double *arr;
	int size;
	double seconds;
};

class StoogeSort {
public:
	/*
	Input : -
	Output : -
	Function Description :
	- prints out class member variable 'seconds'
	*/
	void print_time() const {
		cout << "StoogeSort : " << seconds << " sec" << endl;
	}
	/*
	Input : -
	Output : -
	Function Description :
	- allocate an array(size of 10) to arr
	- initialize arr with {1,2,3,4,5,6,7,8,9,10}
	- initialize seconds(0) & size(10)
	*/
	// implement the following functions
	StoogeSort() {
		// constructor
		arr = new double[10];
		for (int i = 0; i < 10; i++)
		{
			arr[i] = i + 1;
		}
		seconds = 0;
		size = 10;
	}
	/*
	Input : -
	Output : -
	Function Description :
	- deallocate arr
	*/
	~StoogeSort() {
		// destructor
		delete[] arr;
	}
	/*
	Input : -
	Output : -
	Function Description :
	- record start time in start_time
	- run stooge_sort
	- record end time in end_time
	- if runtime <= 10, seconds = sorting runtime
	- if runtime > 10, seconds = 10.000 and prints out a message
	*/
	void run() {
		// sorting algorithm is applied
		// elapsed time is also recorded are seconds
		clock_t start_time = clock();
		int a = stooge_sort(arr, 0, size - 1, start_time);
		clock_t end_time = clock();
		seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		if (a == 0 || seconds >= 10)
		{
			seconds = 10.000;
			cout << "Terminated due to the time limit" << endl;
		}
	}
	/*
	Input : arr, size
	Output : -
	Function Description :
	- delete arr that has been allocated during class construction
	- initialize class member variable size, makes new array
	- deep copy to class member variable arr
	*/
	void set(double *arr, int size) {
		// new input array and its size are set
		delete[] this->arr;
		this->size = size;
		this->arr = new double[size];
		for (int i = 0; i < size; i++)
		{
			this->arr[i] = arr[i];
		}
	}
	/*
	Input : StoogeSort pointer
	Output : True or False
	Function Description :
	- checks whether class member array is sorted
	*/
	friend bool check_stooge(StoogeSort *stooge_sort);

private:
	double *arr;
	int size;
	double seconds;
};
/*
Input : arr, p(arr start index), r(arr end index), start(start time of run function)
Output : int(1 if runtime <= 10, 0 if runtime >10)
Function Description :
- q = partition(arr, p, r)
- sorts arr from index p to q-1 & from index q+1 to r only when p<=r
- dur records start time of the function
- end records end time of the function
- if runtime <=10, return 1
- if runtime > 10, return 0
- if it took more than 10 secs during sorting minor arrays, return 0 and stop sorting
- during records runtime of partition, if it took more than 10 sec return 0
*/
int quick_sort(double arr[], int p, int r, clock_t start)
{
	clock_t dur = clock();
	if ((dur - start) / CLOCKS_PER_SEC > 10)
	{
		return 0;
	}
	if (p <= r)
	{
		int q = partition(arr, p, r);
		clock_t during = clock();
		if ((during - start) / CLOCKS_PER_SEC > 10)
		{
			return 0;
		}
		int a = quick_sort(arr, p, q - 1, start);
		if (a == 0)
		{
			return 0;
		}
		int b = quick_sort(arr, q + 1, r, start);
		if (b == 0)
		{
			return 0;
		}
		clock_t end = clock();
		if ((end - start) / CLOCKS_PER_SEC <= 10)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
		return 1;
}
/*
Input : arr, p(arr start index), r(arr end index)
Output : partition
Function Description :
- initialize pivot = arr[r]
- returns partition : index of pivot after the array is divided by pivot
*/
int partition(double arr[], int p, int r)
{
	double pivot = arr[r];
	int i = p - 1;
	int j;
	double temp;
	for (j = p; j < r; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			double temp = arr[i];
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
/*
Input : arr, left(arr start index), right(arr end index), start(start time of run function)
Output : int(1 if runtime <= 10, 0 if runtime >10)
Function Description :
- sorts arr from index left to mid and from index mid+1 to right
- make new arrays and copies values into them
- sorts array by comparing values from two arrays
- dur records start time of the function
- end records end time of the function
- if runtime <=10, return 1
- if runtime > 10, return 0
- if it took more than 10 secs during sorting minor arrays, return 0 and stop sorting
*/
int merge_sort(double arr[], int left, int right, clock_t start)
{
	clock_t dur = clock();
	if ((dur - start) / CLOCKS_PER_SEC > 10)
	{
		return 0;
	}
	if (left < right)
	{
		int mid = (left + right) / 2;

		int a = merge_sort(arr, left, mid, start);
		if (a == 0)
		{
			return 0;
		}
		int b = merge_sort(arr, mid + 1, right, start);
		if (b == 0)
		{
			return 0;
		}

		// merge °úÁ¤
		int n1 = mid - left + 1;
		int n2 = right - mid;
		double * arr1 = new double[n1 + 1];
		double * arr2 = new double[n2 + 1];
		for (int i = 0; i < n1; i++)
		{
			arr1[i] = arr[left + i];
		}
		arr1[n1] = INT_MAX;
		for (int i = 0; i < n2; i++)
		{
			arr2[i] = arr[mid + i + 1];
		}
		arr2[n2] = INT_MAX;
		int i = 0, j = 0;
		for (int k = left; k <= right; k++)
		{
			if (arr1[i] <= arr2[j])
			{
				arr[k] = arr1[i];
				i++;
			}
			else
			{
				arr[k] = arr2[j];
				j++;
			}
		}
		delete[]arr1;
		delete[]arr2;

		clock_t end = clock();
		if ((end - start) / CLOCKS_PER_SEC <= 10)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 1;
	}
}
/*
Input : arr, size
Output : int(1 if runtime <= 10, 0 if runtime >10)
Function Description :
- sorts arr[i] under condition that arr is sorted from index 0 to i-1
- runtime records function runtime
- if runtime >10 sec, return 0
*/
int insertion_sort(double arr[], int size) {
	clock_t start = clock();
	for (int i = 1; i < size; i++)
	{
		double key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
		clock_t end = clock();
		if ((end - start) / CLOCKS_PER_SEC > 10)
		{
			return 0;
		}
	}
	return 1;
}
/*
Input : arr, left(arr start index), right(arr end index), start(start time of run function)
Output : int(1 if runtime <= 10, 0 if runtime >10)
Function Description :
- if left>= right do nothing
- if number of elements is 2, do sorting
- sorts the two thirds of the array from left and sorts the two thirds of the array from right
- finally sorts the two thirds of the array from left once more
- dur records start time of the function
- end records end time of the function
- if runtime <=10, return 1
- if runtime > 10, return 0
- if it took more than 10 secs during sorting minor arrays, return 0 and stop sorting
*/
int stooge_sort(double arr[], int left, int right, clock_t start)
{
	clock_t dur = clock();
	if ((dur - start) / CLOCKS_PER_SEC > 10)
	{
		return 0;
	}
	if (left >= right)
		return 1;
	else if (left + 1 == right)
	{
		if (arr[left] <= arr[right])
			return 1;
		else
		{
			double temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
			return 1;
		}
	}
	//basic part
	int x = (right - left + 1) / 3;

	int a = stooge_sort(arr, left, right - x, start);
	if (a == 0)
	{
		return 0;
	}
	int b = stooge_sort(arr, left + x, right, start);
	if (b == 0)
	{
		return 0;
	}
	int c = stooge_sort(arr, left, right - x, start);
	if (c == 0)
	{
		return 0;
	}
	//recursive part
	clock_t end = clock();
	if ((end - start) / CLOCKS_PER_SEC <= 10)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

#endif