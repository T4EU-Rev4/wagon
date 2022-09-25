#ifndef main_h
#define main_h

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Wire.h"

#define SOFTSER_RX      12
#define SOFTSER_TX      11
#define SOFTSER_SPEED   9600

#define MON_SPEED       115200

#define SOUNDPIN        A0

#define topLED          A7

#define SDA PC4
#define SCL PC5

#define DEV_0   0x20
#define DEV_1   0x21
#define DEV_2   0x22
#define DEV_3   0x23
#define DEV_4   0x24
#define DEV_5   0x25
#define DEV_6   0x26
#define DEV_7   0x27

#define DEV     DEV_0

#define NR_OF_PORTS 2
#define PCF_PORT_A  0
#define PCF_PORT_B  1

#define I2C_CMD_NOP     0
#define I2C_CMD_STOP    1
#define I2C_CMD_PLAY    2
#define I2C_CMD_VOLUP   3
#define I2C_CMD_VOLDN   4
#define I2C_CMD_VOL     5

void mp3_setup();
void mp3_check();


void vumeter_setup();
void vumeter_measure();
void vumeter_Cler();



#endif