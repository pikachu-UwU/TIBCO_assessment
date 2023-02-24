/**
 *  TIME PARSE
 *  Author: Yelyzaveta (Leeza) Andryushchenko
 * 
 *  DESCRIPTION:
 *  this file contains 3 distinct functions for handling and converting
 *  standart system time to human-interpreted dates and vice versa. Check each
 *  header comment for more information about each function
 *  RUNTIME:
 *  O(1) time manipulations take constant number of steps
 * 
 *  TESTING: Tests.cpp
 *  Look for comments in the file to find unit tests for this function
*/


#include "timeParse.h"

/**
 * getHMS
 * 
 * given time_t variable, populate variables hour min and sec
 * with current time of the day
 * 
 * NOTE: does not account for any timezone conversion, if given
 * standard system time will return the UTC time
 * 
*/
void getHMS(time_t someTime, int *hour, int *min, int *sec) {
    // STEP1 - separate the last seconds:
    *sec = someTime % 60;   // since time_t is seconds, %60 returns cur value within minute
    someTime /= 60;         // convert to minutes

    // STEP2 - get last minutes count:
    *min = someTime % 60;   // last counted number of minutes within an hour
    someTime /= 60;         // convert to hours

    // STEP3 - get number of hours from last current day:
    *hour = someTime % 24;
}

/**
 * getDayOfWeek
 * 
 * given the time_t object, parses the time variable and finds
 * the current day of the week, returns int representing the day:
 * 0 - Sunday to 6 - Saturday
 * 
 * NOTE: for the edge case of days hitting midnight, a new day will be returned
 * For example: in the night between Wednesday and Thursday,at midnight,
 * function will return 4
 * 
*/
int getDayOfWeek(time_t curTime) {
    // get the # of days since epoch:
    int num_days = ((curTime /60) /60) /24;     // int division drops remainder - don't care about current time of the day, only the day
    int weekday = num_days % 7;                 // 0 is Thursday
    return (weekday + 4) % 7;
}


/**
 * getTime
 * 
 * Given the infromation about current day in the following format:
 * month = int from 0 to 11 representing month
 * day - current day of the month (1 to 31 but depents on specific month)
 * year - 0based AD year (for example 2023)
 * hour, min, sec - current day time in military form (hour 0-23)
 * 
 * converts it to system time_t variable, WITHOUT accounting for time zones
 * NOTE: does not do any error checking if provided date is invalid, for example:
 * 
 * month: 1
 * day: 32
 * 
 * Would not cause an error, therefore it is up to the user to provide correct input
 * 
 * */
time_t getTime(int month, int day, int year, int hour, int min, int sec) {
    // first add the obvious hour minute and second
    time_t result = hour*3600 + min*60 + sec;
    // add year
    result += (year - 1970)*365*60*60*24;
    // add date
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days_passed = day;
    for(int i = 0; i < month; days_passed += days[i++]);
    result += days_passed*24*60*60;
    // count leap years:
    int leap_years = (year/4) - (year/100) + (year/400) - ((month < 2) ? 1 : 0);       // until given year
    int start_leap = (1970/4) - (1970/100) + (1970/400);                              // until epoch start (1970)
    result += (leap_years - start_leap)*24*60*60;

    return result;
}