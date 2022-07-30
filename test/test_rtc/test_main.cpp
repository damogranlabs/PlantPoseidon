#include <unity.h>
#include <Arduino.h>

#include "DS1338.h"

void setup(void){};

void setUp(void){
    
}

void tearDown(void) { }

void test_i2c(void){
    Wire.beginTransmission(DS1338_ADDR);
	Wire.write(DS1338_REG_SECONDS);
	TEST_ASSERT_EQUAL(0, Wire.endTransmission());

    Wire.requestFrom(DS1338_ADDR, 1);
    TEST_ASSERT_EQUAL(1, Wire.available());
}

void test_setup_rtc(void){
    TEST_ASSERT_EQUAL(0, ds1338_clean_osf());
    TEST_ASSERT_EQUAL(0, ds1338_disable_sqw());
}

void read_write(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint16_t dly){
    struct rtctime_t t;
    make_time(&t, year, month, day, hour, minute, second);

    TEST_ASSERT_EQUAL(0, ds1338_write_time(&t));
    delay(dly + 100);
    memset(&t, 0, sizeof(t));
    TEST_ASSERT_EQUAL(0, ds1338_read_time(&t));

    TEST_ASSERT_EQUAL(year, t.year);
    TEST_ASSERT_EQUAL(month, t.month);
    TEST_ASSERT_EQUAL(day, t.day);

    TEST_ASSERT_EQUAL(hour, t.hour);
    TEST_ASSERT_EQUAL(minute, t.minute);
    TEST_ASSERT_EQUAL(second + dly/1000, t.second);
}

void test_rw_years(void){
    for(int y = 22; y <= 52; y++){
        read_write(y, 7, 23, 23, 58, 56, 10);
    }
}

void test_rw_months(void){
    for(int m = 1; m <= 12; m++){
        read_write(22, m, 27, 23, 58, 56, 10);
    }
}

void test_rw_days(void){
    for(int d = 1; d <= 31; d++){
        read_write(22, 1, d, 23, 58, 56, 10);
    }
}

void test_rw_hours(void){
    for(int h = 0; h <= 23; h++){
        read_write(22, 1, 13, h, 58, 56, 10);
    }
}

void test_rw_minutes(void){
    for(int m = 0; m <= 59; m++){
        read_write(22, 1, 13, 13, m, 56, 10);
    }
}

void test_rw_seconds(void){
    for(int s = 0; s <= 59; s++){
        read_write(22, 1, 13, 13, 58, s, 10);
    }
}

void test_rw_delay(void){
    read_write(22, 1, 31, 23, 58, 52, 3000);
}

void loop(void){
    Wire.begin();

    UNITY_BEGIN();

    RUN_TEST(test_i2c);
    RUN_TEST(test_setup_rtc);

    RUN_TEST(test_rw_years);
    RUN_TEST(test_rw_months);
    RUN_TEST(test_rw_days);

    RUN_TEST(test_rw_hours);
    RUN_TEST(test_rw_minutes);
    RUN_TEST(test_rw_seconds);

    RUN_TEST(test_rw_delay);

    UNITY_END(); // stop unit testing
}