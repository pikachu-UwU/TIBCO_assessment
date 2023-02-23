/**
 *  TESTS
 *  Author: Yelyzaveta (Leeza) Andryushchenko
 * 
 *  DESCRIPTION:
 *  The following file contains unit tests for all functions
 *  in the technical description, look at the test name and
 *  comments to find corresponding tests for each function
 * 
*/


#include "gtest/gtest.h"
#include "./zeros/ZerosToTheFront.cpp"
#include "./endian/littleEndian.cpp"

using namespace std;

/*******************************************************************************/
//                          ZEROS TO THE FRONT TESTING
/*******************************************************************************/

TEST(zerosToTheFrontTest, emptyInput) {
    int* empty = nullptr;
    int count = 0;
    // testing empty input - NULL pointer and counter 0
    try {
        zerosToTheFront(empty, count);
        FAIL() << "expected throw on empty argument\n";
    } catch(std::invalid_argument const & err) {
        SUCCEED();
    }
}

TEST(zerosToTheFrontTest, smallArrays) {
    // create relatively small arrays that contain 0s
    for(int i = 1; i < 10; i++) {
        // create array
        int* array = new int[i];
        for(int j = 0; j < i; array[j++] = rand() % 3);
        zerosToTheFront(array, i);

        // check if the array does not contain any 0s after first number:
        int index = 0;
        for(; index < i && array[index] == 0; index++); // find last 0
        for(; index < i; index++) {
            ASSERT_NE(array[index], 0);
        }
        // free the memory:
        delete[] array;
    }
    // SUCCEED();
}

TEST(zerosToTheFrontTest, stressTesting) {
    // create random int array of increasing size (correct input)
    for(int i = 20; i < 1000; i++) {
        // STEP 1 - setup the array and call the function
        int* array = new int[i];
        for(int j = 0; j < i; array[j] = rand() % (10), j++);
        zerosToTheFront(array, i);

        // STEP 2 - check if all 0s are in the right order:
        int index;
        for(index = 0; index < i && array[index] == 0; index++); // find last 0
        // make sure no other zeros appear after non-zero number
        for(; index < i; index++) {
            ASSERT_NE(array[index], 0) << "ERROR: found a zero that is not at the beginning of the array";
        }
        // free memory:
        delete[] array;
    }
}

TEST(zerosToTheFrontTest, edgeCases) {
    // FIRST EDGE CASE - give array but count is 0:
    int* array = new int[10];                   // create array
    for(int i = 0; i < 10; array[i++] = i);     // fill some values (not important)
    try {
        zerosToTheFront(array, 0);
        FAIL() << "ERROR: expected a throw on an invalid size";
    } catch(std::invalid_argument const & err) {}

    // SECOND EDGE CASE - given size is less than the size of the array
    // expected behavior - only the 'count' part of the array will move 0s
    for(int i = 0; i < 10; array[i] = rand() % 3, i++);
    zerosToTheFront(array, 5);

    int index;
    for(index = 0; index < 5 && array[index] == 0; index++);
    for(;index < 5; index++) {
        ASSERT_NE(array[index], 0);
    }
}


/*******************************************************************************/
//                        LITTLE ENDIAN CONVERSION TESTING
/*******************************************************************************/



/*******************************************************************************/
//                                    MAIN
/*******************************************************************************/
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}