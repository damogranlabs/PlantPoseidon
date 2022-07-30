#include <unity.h>

#include "util.h"

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void test_isLeapYear(void){
    TEST_ASSERT_TRUE(isLeapYear(2000));
    TEST_ASSERT_TRUE(isLeapYear(2004));
    TEST_ASSERT_TRUE(isLeapYear(1912));

    TEST_ASSERT_FALSE(isLeapYear(1900));
    TEST_ASSERT_FALSE(isLeapYear(2001));
    TEST_ASSERT_FALSE(isLeapYear(2002));
}

void test_validateDay(void){
    TEST_ASSERT_EQUAL_INT(31, validateDay(2000, 1, 32));
    TEST_ASSERT_EQUAL_INT(29, validateDay(2000, 2, 30));
    TEST_ASSERT_EQUAL_INT(29, validateDay(2000, 2, 29));
    TEST_ASSERT_EQUAL_INT(31, validateDay(2001, 10, 31));
    TEST_ASSERT_EQUAL_INT(30, validateDay(2000, 11, 31));
    TEST_ASSERT_EQUAL_INT(31, validateDay(2000, 1, 32));
}

void test_daysInMonth(void){
    TEST_ASSERT_EQUAL_INT(30, daysInMonth(2022, 4));
    TEST_ASSERT_EQUAL_INT(30, daysInMonth(2022, 6));
    TEST_ASSERT_EQUAL_INT(30, daysInMonth(2022, 9));
    TEST_ASSERT_EQUAL_INT(30, daysInMonth(2022, 11));
    TEST_ASSERT_EQUAL_INT(28, daysInMonth(2022, 2));
    TEST_ASSERT_EQUAL_INT(31, daysInMonth(2022, 1));
    TEST_ASSERT_EQUAL_INT(31, daysInMonth(2022, 3));
    TEST_ASSERT_EQUAL_INT(31, daysInMonth(2022, 5));
    TEST_ASSERT_EQUAL_INT(31, daysInMonth(2022, 7));
    TEST_ASSERT_EQUAL_INT(31, daysInMonth(2022, 8));
    TEST_ASSERT_EQUAL_INT(31, daysInMonth(2022, 10));
    TEST_ASSERT_EQUAL_INT(31, daysInMonth(2022, 12));

    TEST_ASSERT_EQUAL_INT(29, daysInMonth(2000, 2));
}

void test_compareHours_same(void){
    TEST_ASSERT_TRUE(compareHours(7, 7, 12));
    TEST_ASSERT_TRUE(compareHours(7, 7, 24));
    
    TEST_ASSERT_TRUE(compareHours(23, 23, 12));
    TEST_ASSERT_TRUE(compareHours(23, 23, 24));

    TEST_ASSERT_TRUE(compareHours(7, 7, 48));
    TEST_ASSERT_TRUE(compareHours(7, 7, 7*24));
}

void test_compareHours_12(void){
    TEST_ASSERT_TRUE(compareHours(7, 19, 12));

    TEST_ASSERT_TRUE(compareHours(23, 23, 12));

    TEST_ASSERT_TRUE(compareHours(11, 23, 12));
}

void test_compareHours_different(void){
    TEST_ASSERT_FALSE(compareHours(8, 7, 12));
    TEST_ASSERT_FALSE(compareHours(8, 7, 24));
}

void test_hourDelta(void){
    // 7:00 - 19:00
    TEST_ASSERT_EQUAL(12,       hourDelta(2022,1,1,19, 2022,1,1,7));
    // jan. 1st 20:00 - jan. 2nd 8:00
    TEST_ASSERT_EQUAL(12,       hourDelta(2022,1,2,8,  2022,1,1,20));

    // 1 day
    TEST_ASSERT_EQUAL(24,       hourDelta(2022,1,2,7,  2022,1,1,7));
    // 1 month
    TEST_ASSERT_EQUAL(31*24,    hourDelta(2022,2,1,7,  2022,1,1,7));
    // 2 months
    TEST_ASSERT_EQUAL(31*24 + 28*24, hourDelta(2022,3,1,7,  2022,1,1,7));

    // negative delta
    TEST_ASSERT_EQUAL(-1, hourDelta(2022,3,1,6,  2022,3,1,7));
}

int main(int argc, char **argv){
    UNITY_BEGIN();
  
    RUN_TEST(test_isLeapYear);
    RUN_TEST(test_daysInMonth);
    RUN_TEST(test_validateDay);
    RUN_TEST(test_hourDelta);

    RUN_TEST(test_compareHours_same);
    RUN_TEST(test_compareHours_12);
    RUN_TEST(test_compareHours_different);

    UNITY_END(); // stop unit testing

    return 0;
}