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


#include "gtest/gtest.h"    // google tests
#include <arpa/inet.h>      // testing little endian implementation
#include <thread>           // better test runtime performance
#include <bits/stdc++.h>    // time parse testing

// tested files
#include "./zeros/ZerosToTheFront.cpp"
#include "./endian/littleEndian.cpp"
#include "./timeParse/timeParse.cpp"

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

TEST(littleEndianShort, noEdgeBytes) {
    unsigned short test = 28;           // 00000000 00011100
    ASSERT_EQ(my_ntohs(test), 7168);    // 00011100 00000000

    test = 22642;                       // 01011000 01110010
    ASSERT_EQ(my_ntohs(test), 29272);   // 01110010 01011000

    test = 0;                           // 00000000 00000000
    ASSERT_EQ(my_ntohs(test), 0);       // 00000000 00000000

    test = 21760;                       // 01010101 00000000
    ASSERT_EQ(my_ntohs(test), 85);      // 00000000 01010101
}

TEST(littleEndianShort, edgeBytes) {
    unsigned short test = 38317;        // 10010101 10101101
    ASSERT_EQ(my_ntohs(test), 44437);   // 10101101 10010101

    test = 64257;                       // 11111011 00000001
    ASSERT_EQ(my_ntohs(test), 507);     // 00000001 11111011

    test = 65535;                       // 11111111 11111111
    ASSERT_EQ(my_ntohs(test), 65535);   // 11111111 11111111
}

TEST(littleEndianShort, stressTesting) {
    // using original htons function to test the output:

    // last byte combinations
    for(unsigned short i = 0; i < 255; i++) {
        ASSERT_EQ(my_ntohs(i), ntohs(i));
    }

    // first byte combinations
    unsigned short i = 256;
    for(unsigned short i = 256; i <= 65535 && i != 0; i += 256) {
        ASSERT_EQ(my_ntohs(i), ntohs(i));
    }

    // every possible value:
    for(int i = 257; i <= 65535 && i != 0; i++) {
        ASSERT_EQ(my_ntohs(i), ntohs(i));
    }
}


// HELPER FUNCTION - used by test below to run stress testing
// on different threads for faster results  286331153
void thread_separation(unsigned int id) {
    int bound = id*16711935 + 16711935;
    for(unsigned int i = id*16711935; i <= 16711935 && i < bound; i++) {
        ASSERT_EQ(my_ntohl(i), ntohl(i));
    }
}


TEST(littleEndianLong, stressTesting) {
    // separate testing into different threads for better performance
    std::thread t_arr[257];
    for(int i = 0; i < 257; i++) {
        t_arr[i] = std::thread(thread_separation, i);
    }
    // wait for every thread to finish
    for(int i = 0; i < 257; t_arr[i++].join());
}


/*******************************************************************************/
//                              TIME PARSE TESTING
/*******************************************************************************/

TEST(getHMSTest, currentTime) {
    // get current timestamp
    time_t curTime = time(0);
    int hour, min, sec;
    getHMS(curTime, &hour, &min, &sec);

    // find current hour/minute/second
    tm* cur = localtime(&curTime);
    // cout << "Actual parsing is:  " << cur->tm_hour << "-" << cur->tm_min << "-" << cur->tm_sec << endl;
    ASSERT_EQ(sec, cur->tm_sec);
    ASSERT_EQ(min, cur->tm_min);
    ASSERT_EQ(hour, (cur->tm_hour + 6) % 24);   // local time defaults to chicago timezone, convert to UTC
}

TEST(getHMSTest, stressTesting) {
    // try every possible second within a 24-hour span:
    for(int i = 0; i < 86400; i++) {    // NOTE: 86400 -> 60*60*24
        time_t t = i;
        int hour, min, sec;
        // get time parse
        getHMS(t, &hour, &min, &sec);

        // get correct & compare
        tm* cur = localtime(&t);
        ASSERT_EQ(sec, cur->tm_sec);
        ASSERT_EQ(min, cur->tm_min);
        ASSERT_EQ(hour, (cur->tm_hour + 6) % 24);
    }
}


TEST(getDayOfWeekTest, currentTime) {
    time_t curTime = time(0);
    int day = getDayOfWeek(curTime);
    tm* cur = localtime(&curTime);
    
    ASSERT_EQ(day, cur->tm_wday);
}

TEST(getDayOfWeekTest, stressTesting) {
    // attempt to run the test for days within current given year:
    time_t start = time(0);
    time_t end = start + 31536000;                  // 31,536,000 -> seconds in a year
    for(time_t t = start; t < end; t += 86400 ) {   // 86400 -> seconds in a day
        tm* cur = localtime(&t);
        ASSERT_EQ(getDayOfWeek(t), cur->tm_wday);
    }
}

TEST(getTimeTest, currentTime) {
    time_t curTime = time(0);
    tm* cur = localtime(&curTime);
    time_t result = getTime(cur->tm_mon, cur->tm_mday, 2023, cur->tm_hour + 6, cur->tm_min, cur->tm_sec);
    ASSERT_EQ(curTime, result);    // UTC is 6 hours ahead - hour + 6 in params
}


time_t get_start_date(int day) {
    time_t cur = time(0);
    tm* t = localtime(&cur);
    // restructure current time to be the given day:
    t->tm_yday = day;
    // construct time object again:
    return mktime(t);
}

void helper_time(int id) {
    time_t start = get_start_date(id);
    // test for the given time frame of the year:
    for(time_t i = start; i < start + 86400; i++) {
        tm* cur = localtime(&i);
        time_t result = getTime(cur->tm_mon, cur->tm_mday, 2023, cur->tm_hour + 6, cur->tm_min, cur->tm_sec);
        ASSERT_EQ(i, result);
        return;
    }
}


TEST(getTimeTest, stressTesting) {
    // try every possible second within this year
    // split the work between 365 threads, each runs 1 day of the year:
    thread t_array[365];
    for(int i = 0; i<365; i++) {
        t_array[i] = thread(helper_time, i);
    }
    // wait for each thread to finish
    for(int i =0; i < 365; i++) {
        t_array[i].join();
    }
}


/*******************************************************************************/
//                                    MAIN
/*******************************************************************************/
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}