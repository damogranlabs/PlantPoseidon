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

void test_getDigitCount(void){
    TEST_ASSERT_EQUAL(getDigitCount(0), 1);
    TEST_ASSERT_EQUAL(getDigitCount(1), 1);
    TEST_ASSERT_EQUAL(getDigitCount(9), 1);

    TEST_ASSERT_EQUAL(getDigitCount(10), 2);
    TEST_ASSERT_EQUAL(getDigitCount(99), 2);

    TEST_ASSERT_EQUAL(getDigitCount(100), 3);
}

void test_wrap(void){
    TEST_ASSERT_EQUAL(wrap(0, 0, 10), 0);
    TEST_ASSERT_EQUAL(wrap(1, 0, 10), 1);
    TEST_ASSERT_EQUAL(wrap(10, 0, 10), 10);

    TEST_ASSERT_EQUAL(wrap(11, 0, 10), 0);
    TEST_ASSERT_EQUAL(wrap(12, 0, 10), 0);

    TEST_ASSERT_EQUAL(wrap(0, 1, 10), 10);
}

int main(int argc, char **argv){
    UNITY_BEGIN();
  
    RUN_TEST(test_getDigitCount);
    RUN_TEST(test_wrap);
    
    UNITY_END(); // stop unit testing

    return 0;
}