#include "Sorting.h"
#include <iostream>
#include <fstream>
#include <typeinfo>
using namespace std;

template<typename k, typename v, typename C>
Sorting<k, v, C>::Sorting(int Size)
{
	myArr = new pair<k, v>[Size];
	size = 0;//size variable initialized
	keyCompares = 0;
	dataMoves = 0;
}

template<typename k, typename v, typename C>
Sorting<k,  v,  C>::~Sorting()
{
	delete myArr;
}

template<typename k, typename v, typename C>
void Sorting<k, v, C>::add(pair<k,v> myPair)//function intended for intializing myArray, NOT for sorting itself. Only adds to end of myArray and assumes myArray is filled up to index size with no empty spots
{
	myArr[size] = myPair;
	size++;
}

template<typename k, typename v, typename C>
void Sorting<k, v, C>:: insert(int position, pair<k, v> myPair) {
	myArr[position] = myPair;
	size++;//incrementing size in case for some reason you're inserting
}

template<typename k, typename v, typename C>
int Sorting<k, v, C>::Size()
{
	return size;
}

template<typename k, typename v, typename C>
void Sorting<k, v, C>::remove(int position)//probably never use this
{
	for (int i = position; i < size - 2;i++)
	{
		myArr[i] = myArr[i + 1];
	}
		myArr[size-1] = nullptr;//clearing up old last index
		size--;
}

template<typename k, typename v, typename C>
void Sorting<k, v, C>::swap(int position1, int position2)//helper swap function
{
	pair<k, v> temp = myArr[position1]; //assigning to a variable, even temporary, is a data move
	myArr[position1] = myArr[position2];//assigning between elements is a data move
	myArr[position2] = temp;
	dataMoves += 3;
}

template<typename k, typename v, typename C>
void Sorting<k, v, C>::insertionSort()
{
	dataMoves = 0;
	keyCompares = 0;
	pair<k, v> curPair;
	int j;
	for (int i = 1; i < size; i++)
	{
		curPair = myArr[i];
		dataMoves++;
		int j = i;
		//cout << "P" << endl;
		while (j > 0 && isGreater(myArr[j-1].first, curPair.first)) //while j hasnt reached the beginning and j is greater than key
		{
			keyCompares++;//we just made a comparison
			//cout << "j" << endl;
			myArr[j] = myArr[j-1];
			dataMoves++;
			j--;
		}
		if (j > 0)
		{
			keyCompares++;//if j>0 it means we broke the loop when our comparison evaluated false. We need to account for that comparison
		}
		myArr[j] = curPair;
		dataMoves++;
		
	}

}

template<typename k,typename v, typename C>
void Sorting<k, v, C>::mergeSort()//wrapper function so we dont have to mess with the left and right arguments
{
	dataMoves = 0;
	keyCompares = 0;
	int x = size - 1; //for some reason using size-1 directly causes an error
	mergeSort1(0, x);

}

template<typename k, typename v, typename C>
void Sorting<k, v, C>::mergeSort1(int l, int r)//recursive function used to split the array in the middle over and over
{
	if (l < r)//stop when l reaches r. then we have split it as much as we can or we've hit array size = 1
	{
		int p = ((l+r) / 2);

		mergeSort1(l, p); //partitioning and sorting
		mergeSort1(p + 1, r);//partitioning and sorting
		merge(l, p, r);
	}
}

template<typename k, typename v, typename C>
void Sorting<k, v, C>::merge(int l, int m, int r)
{
	int i;
	int j;
	int t;
	int length1 = m - l + 1;//partitioning again
	int length2 = r - m;
	pair<k,v> *left = new pair<k,v>[length1];
	pair<k,v> *right = new pair<k,v>[length2];
	for (i = 0; i < length1; i++)
	{
		left[i] = myArr[l + i];
		dataMoves++;
	}
	for (j = 0; j < length2; j++)
	{
		right[j] = myArr[m + 1 + j];
		dataMoves++;//assigning data
	}
	i = 0;
	j = 0;
	t = l;
	while (i < length1 && j < length2)
	{
		if (!isGreater(left[i].first,right[j].first))//we parse through the array and add to the left and right arrays according to our comparator
		{
			myArr[t] = left[i];
			i++;
		}
		else
		{

			myArr[t] = right[j];
			j++;
		}
		keyCompares++;//no matter the result we made 1 comparison and 1 data move
		dataMoves++;
		t++;
	}
	while (i < length1)
	{
		myArr[t] = left[i];
		dataMoves++;
		i++;
		t++;

	}
	while (j < length2)
	{
		myArr[t] = right[j];
		dataMoves++;
		j++;
		t++;
	}
	
}

template<typename k, typename v, typename C>//wrapper function
void Sorting<k, v, C>::quickSort3()
{
	dataMoves = 0;
	keyCompares = 0;
	int r = size - 1;//using size-1 is kinda buggy
	quickSort31(0, r);

}
template<typename k, typename v, typename C>
void Sorting<k, v, C> ::quickSort31(int l, int h)
{
	if (l < h)//means we havent hit l = h and theres more than 1 thing in our partition
	{
		int piv = partition3(l, h);//finds our new pivot point
		quickSort31(l, piv - 1);//essentially splitting our new array into two centered about the pivot value
		quickSort31(piv + 1, h);
	}
}

template<typename k, typename v, typename C>
int Sorting<k, v, C> ::findMedian(k a, k b, k c, int l, int m, int h)//need to put into respective order
{
	
	if ((isGreater(b, a) && isGreater(c, b)) || (isGreater(b, c) && isGreater(a, b)))
	{
		keyCompares += 4;
		return m;
	}


	else if ((isGreater(a, b) && !isGreater(c, a)) || (isGreater(c, a) && isGreater(b, a)))
	{
		keyCompares += 8;//includes comparisons above
		return l;
	}

	else
	{
		keyCompares += 8;
		return h;
	}
}

template<typename k, typename v, typename C>
int Sorting<k, v, C> :: partition3(int l, int h)
{
	int middle = (l + h) / 2;
	int median = findMedian(myArr[l].first, myArr[middle].first, myArr[h].first, l, middle, h);//finds index of the median
	
	swap(median, h);//so we essentially do the exact same thing we did for regular quicksort but we move things around so the median is at the end and used as the pivot instead of what used to be the end value
	//increases runtime on a  linear scale
	pair<k, v> piv = myArr[h];
	dataMoves++;
	int i = (l - 1);//l-1 because we need to account for the all elements, including the one preceding l
	for (int g = l; g < h; g++)//skips median index
	{
		if (!isGreater(myArr[g].first, piv.first))//if our index is greater we move it into the sorted area
		{
			i++;
			swap(i, g);
		}
		keyCompares++;//no matter what we made a key compare here
	}
	swap(i + 1, h);//swaps out our most recent i as it becomes the new pivot
	return(i + 1);
}

template<typename k, typename v, typename C>//wrapper function
void Sorting<k, v, C>::quickSort()
{
	dataMoves = 0;
	keyCompares = 0;
	int r = size - 1;//using size-1 is kinda buggy
	quickSort1(0, r);

}

template<typename k, typename v, typename C>
void Sorting<k, v, C>::quickSort1(int l, int h)
{
	if (l < h)//means we havent hit l = h and theres more than 1 thing in our partition
	{
		int piv = partition(l, h);//finds our new pivot point
		quickSort1(l, piv - 1);//essentially splitting our new array into two centered about the pivot value
		quickSort1(piv + 1, h);
	}
}

template<typename k, typename v, typename C>
int Sorting<k, v, C>::partition(int l, int h)
{
	pair<k,v> piv = myArr[h];//the pivot is the one at the end, so h or the high value
	dataMoves++;
	int i = (l - 1);//l-1 because we need to account for the all elements, including the one preceding l
	for (int g = l; g <= h-1; g++)
	{
		if (!isGreater(myArr[g].first,piv.first))//if our index is greater we move it into the sorted area
		{
			i++;
			swap(i, g);
			
		}
		keyCompares++;
	}
	swap(i + 1, h);//swaps out our most recent i as it becomes the new pivot
	return(i + 1);
}

template<typename k, typename v, typename C>
void Sorting<k, v, C> :: heapSort()
{
	// Build heap (rearrange array) 
	for (int i = size / 2 - 1; i >= 0; i--)
		heapify( size, i);

	for (int i = size - 1; i >= 0; i--) {
		// Move root to end 
		swap(0, i);

		// heapify on the new smaller heap 
		heapify( i, 0);
	}
}

template<typename k, typename v, typename C>
void Sorting<k, v, C> :: heapify(int n, int i)//iterator and local ending index
{
	keyCompares = 0;
	dataMoves = 0;
	int large = i; 
	int l = 2 * i + 1; 
	int r = 2 * i + 2; 

	
	if (l < n && isGreater(myArr[l].first,myArr[large].first))//finding the biggest one so far
	{
		keyCompares++;
		large = l;
	}
	if (r < n && isGreater(myArr[r].first,myArr[large].first))
	{
		keyCompares++;
		large = r;
	}

	if (large != i) 
	{
		swap(i, large);
		// Recursively heapify the affected sub-tree 
		heapify(n, large);
		
	}
}

template<typename k, typename v, typename C>
void Sorting<k, v, C>::shellSort()
{
	keyCompares = 0;
	dataMoves = 0;
	// Start with a big gap, then reduce the gap 
	for (int gap = size / 2; gap > 0; gap /= 2)//gap is how we increment ourselves
	{

		for (int i = gap; i < size; i++)
		{

			pair<k, v> temp = myArr[i];
			dataMoves++;
			int j;
			for (j = i; j >= gap && isGreater(myArr[j - gap].first, temp.first); j -= gap)//we go gap by gap in the same equivalent indices and go all the way down to the beginning of the array
			{
				keyCompares++;
				myArr[j] = myArr[j - gap];
				dataMoves++;
			}

			myArr[j] = temp;//reinserting our temp, swapping  our earliest array value with temp. Nested loop replacement
			dataMoves++;
		}
	}
}
	

template<typename k, typename v, typename C>
void Sorting<k, v, C>::testPrint()
{
	for (int i = 0; i < 5; i++)
	{
		cout << myArr[i].second << endl;
	}
	for (int i = size - 6; i < size; i++)
	{
		cout << myArr[i].second << endl;
	}
}

template<typename k, typename v, typename C>
void Sorting<k, v, C>::outputFile(string filename, string sortingMethod, double milliSeconds)
{
	ofstream myFile;
	myFile.open(filename);
	myFile << "Sorting Method: " << sortingMethod << endl;
	myFile << "Filename: " << filename << endl;
	myFile << "Number of Elements: " << size << ". Key type: " << typeinfo(k).name() << endl;
	cout << "Key Comparisons: " << keyCompares << ". Data moves: " << dataMoves << endl;
	cout << "Seconds taken: " << milliSeconds << " milliseconds" << endl;
	for (int i = 0; i < 5; i++)
	{
		myFile << myArr[i].second << endl;
	}
	for (int i = size - 6; i < size; i++)
	{
		myFile << myArr[i].second << endl;
	}
}