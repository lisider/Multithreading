#ifndef _LED_H_
#define _LED_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>


#define LP5523_LED_ON  (1)
#define LP5523_LED_OFF (0)

#define FIRST_DEVICE   (0x00)
#define SECOND_DEVICE  (0x01)
#define THIRD_DEVICE   (0x02)
#define FOURTH_DEVICE  (0x03)
#define ALL_DEVICE     (0x04)

#define LED_INDEX_FIRST  (0)
#define LED_INDEX_SECOND (1)
#define LED_INDEX_THIRD  (2)

#define COLOR_RED   (0x0)
#define COLOR_GREEN (0x1)
#define COLOR_BLUE  (0x2)

#define LED_BY_DEVICE_IDX (1)
#define LED_BY_LED_IDX    (0)

#define LED_FD  "/dev/ti-led"

int fd_led;

void led_horse_race(int light_duty, int color_index);

void led_blink(int light_duty, int blink_times, int color_index);

void led_light(int light_duty, int color_index);

void led_light_stop(void);

void led_light_eachone(int light_duty, int device_index, int color_index, int led_num);

void led_light_stop_eachone(int device_index, int led_num);

#endif