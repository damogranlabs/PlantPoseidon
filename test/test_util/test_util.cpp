#include <Arduino.h>
#include <unity.h>

#include "util.h"

using namespace fakeit;


void setUp(void)
{
    ArduinoFakeReset();
}

void tearDown(void) {
    // clean stuff up here
}

void test_request(void)
{
    TEST_ASSERT_EQUAL(3, 3);
    TEST_ASSERT_TRUE(true);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_request);

    return UNITY_END();
}