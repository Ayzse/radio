#include <wiringPi.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

int init();

int time_init();

int set_output(uint8_t data);

int send_data(uint8_t output_sel);
