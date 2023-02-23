/**
 *  ZEROS TO THE FRONT
 *  Author: Yelyzaveta (Leeza) Andryushchenko
 * 
 *  DESCRIPTION:
 *  Given a dynamically-allocated array of integers (int *array)
 *  and its size (int count), the function moves all of the elements
 *  of value 0 to the front of the array. The order of other elements
 *  is not guaranteed. Function will throw exception on invalid
 *  argument if given array is NULL or if the size is 0. If the
 *  array is smaller than the given count the behavior is unpredictable.
 *  RUNTIME:
 *  The algorithm uses single traversal until indexes reach the end
 *  of the array, thus the total runtime is within linear bounds.
 * 
 *  TESTING: Tests.cpp
 *  Look for comments in the file to find unit tests for this function
 * 
*/



#include "ZerosToTheFront.h"


using namespace std;

void zerosToTheFront(int* array, int count) {
    // EDGE CASE - empty array:
    if(array == nullptr || count == 0)  throw invalid_argument("Empty argument passed"); // find the first non-zero element;

    // Find first 0 and non-0 elements
    int index = 0;  // 0
    for(; index < count && array[index] != 0; index++);
    int num = 0;    // non0
    for(; num < count && array[num] == 0; num++);

    // EDGE CASE - no 0s or all 0s
    if(index == count || num == count)  return;

    // Swap elements puttin 0s at the front
    while(true) {
        // found a 0 out of the order
        if(index > num) {
            // swap the numbers
            array[index] = array[num];
            array[num] = 0;
            // find next number and next 0:
            for(;index < count && array[index] != 0; index++);
            for(;num < count && array[num] == 0; num++);
        } else {
            // found 0 in the correct position, look for a next 0
            for(index = index +1;index < count && array[index] != 0; index++);
        }

        // could not find another 0, or all 0s are already at the front --> DONE
        if(num == count || index == count)   break;
    }

}