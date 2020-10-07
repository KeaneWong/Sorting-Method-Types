#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "Sorting.h"
#include "Sorting.cpp"
#include "Numcomparator.h"
#include "StringComparator.h"
#include <chrono>
using namespace std;
using namespace std::chrono;
int main(){
	cout << "Hello World!" << endl;
    string filename;
    cout << "Hello, welcome to the FBI HOME LOCATIONAL WATCHLIST SYSTEM. Please enter the file name of the data base to be processed: " << endl;
    cin >> filename;
    ifstream FBIwatchlist;
    FBIwatchlist.open(filename);
    if (!FBIwatchlist) //exiting if it doesnt work
    {
        cout << "INVALID FILE NAME TERMINATING IMMEDIATELY";
        exit(1); // terminate with error
    }
    int numElements = 0;
    cout << "Enter the size of the data" << endl;
    cin >> numElements;
    Sorting<int, string, Numcomparator> myInsertionSorter1(numElements);
    Sorting<string, int, StringComparator> myInsertionSorter2(numElements);
    Sorting<int, string, Numcomparator> myMergeSorter1(numElements);
    Sorting<string, int, StringComparator> myMergeSorter2(numElements);
    Sorting<int, string, Numcomparator> myQuickSorter1(numElements);
    Sorting<string, int, StringComparator> myQuickSorter2(numElements);
    Sorting<int, string, Numcomparator> myQuickSort3er1(numElements);
    Sorting<string, int, StringComparator> myQuickSort3er2(numElements);
    Sorting<int, string, Numcomparator> myHeapSorter1(numElements);
    Sorting<string, int, StringComparator> myHeapSorter2(numElements);
    Sorting<int, string, Numcomparator> myShellSorter1(numElements);
    Sorting<string, int, StringComparator> myShellSorter2(numElements);
    int curValue;
    while (FBIwatchlist >> curValue)
    {
        myInsertionSorter1.add( pair<int, string>(curValue, to_string(curValue) ));
        myInsertionSorter2.add(pair<string, int>(to_string(curValue), curValue));
        myMergeSorter1.add(pair<int, string>(curValue, to_string(curValue)));
        myMergeSorter2.add(pair<string, int>(to_string(curValue), curValue));
        myQuickSorter1.add(pair<int, string>(curValue, to_string(curValue)));
        myQuickSorter2.add(pair<string, int>(to_string(curValue), curValue));
        myQuickSort3er1.add(pair<int, string>(curValue, to_string(curValue)));
        myQuickSort3er2.add(pair<string, int>(to_string(curValue), curValue));
        myHeapSorter1.add(pair<int, string>(curValue, to_string(curValue)));
        myHeapSorter2.add(pair<string, int>(to_string(curValue), curValue));
        myShellSorter1.add(pair<int, string>(curValue, to_string(curValue)));
        myShellSorter2.add(pair<string, int>(to_string(curValue), curValue));
    }
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    myInsertionSorter1.insertionSort();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    double ms = 100 * time_span.count();


    myInsertionSorter2.insertionSort();
  

    myMergeSorter1.mergeSort();
    myMergeSorter2.mergeSort();
    myQuickSorter1.quickSort();
    myQuickSorter2.quickSort();
    myQuickSort3er1.quickSort3();
    myQuickSort3er2.quickSort();
    myHeapSorter1.heapSort();
    myHeapSorter2.heapSort();
    myShellSorter1.shellSort();
    myShellSorter2.shellSort();

    
    return 0;

}