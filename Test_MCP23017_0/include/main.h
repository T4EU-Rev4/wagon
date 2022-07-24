#ifndef main_h
#define main_h

#include "Arduino.h"
#include "Wire.h"


#define DEV_0   0x20
#define DEV_1   0x21
#define DEV_2   0x22
#define DEV_3   0x23
#define DEV_4   0x24
#define DEV_5   0x25
#define DEV_6   0x26
#define DEV_7   0x27

#define IODIRA  0x00
#define IODIRB  0x01        //if BANK=0
#define GPIOA   0x12        //if BANK=0
#define GPIOB   0x13        //if BANK=0

#define DEV     DEV_0

#endif