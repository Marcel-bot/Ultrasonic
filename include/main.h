#ifndef MAIN
#define MAIN

#include<Arduino.h>
#include<Wire.h>

#define I2C_ADDRESS 0x08

#define FRONT_LEFT_ECHO 4
#define FRONT_LEFT_TRIG 6

#define FRONT_MIDDLE_ECHO 7
#define FRONT_MIDDLE_TRIG 5

#define FRONT_RIGHT_ECHO 8
#define FRONT_RIGHT_TRIG 3

#define BACK_LEFT_ECHO 0
#define BACK_LEFT_TRIG 0

#define BACK_MIDDLE_ECHO 0
#define BACK_MIDDLE_TRIG 0

#define BACK_RIGHT_ECHO 0
#define BACK_RIGHT_TRIG 0

#define SOUND_SPEED 0.034

#define UP_MESSAGE "Base up"

#define UP_CHAR '*'

#endif