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
    TEST_ASSERT_EQUAL_INT(validateDay(2000, 1, 32), 31);
    TEST_ASSERT_EQUAL_INT(validateDay(2000, 2, 30), 29);
    TEST_ASSERT_EQUAL_INT(validateDay(2000, 2, 29), 29);
    TEST_ASSERT_EQUAL_INT(validateDay(2001, 10, 31), 31);
    TEST_ASSERT_EQUAL_INT(validateDay(2000, 11, 31), 30);
    TEST_ASSERT_EQUAL_INT(validateDay(2000, 1, 32), 31);
}

void test_daysInMonth(void){
    TEST_ASSERT_EQUAL_INT(daysInMonth(2022, 4), 30);
    TEST_ASSERT_EQUAL_INT(daysInMonth(2022, 6), 30);
    TEST_ASSERT_EQUAL_INT(daysInMonth(2022, 9), 30);
    TEST_ASSERT_EQUAL_INT(daysInMonth(2022, 11), 30);
    TEST_ASSERT_EQUAL_INT(daysInMonth(2022, 2), 28);
    TEST_ASSERT_EQUAL_INT(daysInMonth(2022, 1), 31);
    TEST_ASSERT_EQUAL_INT(daysInMonth(2022, 3), 31);
    TEST_ASSERT_EQUAL_INT(daysInMonth(2022, 5), 31);
    TEST_ASSERT_EQUAL_INT(daysInMonth(2022, 7), 31);
    TEST_ASSERT_EQUAL_INT(daysInMonth(2022, 8), 31);
    TEST_ASSERT_EQUAL_INT(daysInMonth(2022, 10), 31);
    TEST_ASSERT_EQUAL_INT(daysInMonth(2022, 12), 31);

    TEST_ASSERT_EQUAL_INT(daysInMonth(2000, 2), 29);
}

int main(int argc, char **argv){
    UNITY_BEGIN();
  
    RUN_TEST(test_isLeapYear);
    RUN_TEST(test_daysInMonth);
    RUN_TEST(test_validateDay);

    UNITY_END(); // stop unit testing

    return 0;
}