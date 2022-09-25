#ifndef main_h
#define main_h

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define SOFTSER_RX      12
#define SOFTSER_TX      11
#define SOFTSER_SPEED   9600

#define MON_SPEED       115200

#define SOUNDPIN        A0

#define topLED          A7

void mp3_setup();
void mp3_check();


void vumeter_setup();
void vumeter_measure();
void vumeter_Cler();



#endif