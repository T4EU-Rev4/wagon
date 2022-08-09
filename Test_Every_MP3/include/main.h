#ifndef main_h
#define main_h

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define SOFTSER_RX      10
#define SOFTSER_TX      11
#define SOFTSER_SPEED   9600

#define MON_SPEED       115200



void mp3_setup();
void mp3_check();




#endif