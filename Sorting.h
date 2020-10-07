#pragma once
#include <string>
using namespace std;
template <typename k, typename v, typename C>
class Sorting
{
public:
	Sorting(int Size);
	~Sorting();

	void add(pair<k, v> myPair);
	void remove(int position);//most likely never using this but might as well have it
	void insert(int position, pair<k,v> myPair);

	int Size();
	void insertionSort();
	void mergeSort();
	void quickSort();
	void quickSort3();
	void testPrint();
	void heapSort();
	void shellSort();
	void outputFile(string filename, string sortingMethod, double milliSeconds);
private:
	C isGreater;
	pair<k, v>  *myArr;
	int size;
	void swap(int position1, int position2);
	int keyCompares; //stores the most recent number of comparisons in it and is rewritten every time a new function is called
	int dataMoves;
	void merge(int l, int m, int r);
	void mergeSort1(int l, int r);
	void quickSort1(int l, int h);
	void quickSort31(int l, int h);
	int partition3(int l, int h);
	int partition(int l, int h);
	int findMedian(k a, k b, k c, int l, int m, int h);
	void heapify(int n, int i);
};

