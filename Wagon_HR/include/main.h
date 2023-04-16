#ifndef main_h
#define main_h

#include "Arduino.h"

#define MON_SPEED       115200

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 12

void colorWipe(uint32_t color, int wait) ;


#endif