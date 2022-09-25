//#include <Arduino.h>
#include <main.h>
#include <timer.h>

extern DFRobotDFPlayerMini mp3;   //defined in mp3.cpp
extern union TTimer timerFlags;       //keep all the flags in one byte


//uint16_t state_delay = 2000;
//int title = 1;


bool testpinLow;

void check_Input() {
  while (Serial.available() > 0) {  
    char inChar = Serial.read();  
    switch (inChar) {
      case '0' :  mp3.stop();      break;
      case '1' :  mp3.play( 1 );   break;
      case '2' :  mp3.play( 2 );   break;
      case '3' :  mp3.play( 3 );   break;
      case '4' :  mp3.play( 4 );   break;
      case '5' :  mp3.play( 5 );   break;
      case '6' :  mp3.play( 6 );   break;
      case '7' :  mp3.play( 7 );   break;
      case '8' :  mp3.play( 8 );   break;
      case '9' :  mp3.play( 9 );   break;
      case '+' : mp3.volumeUp(); break;
      case '-' : mp3.volumeDown(); break;
      
    }
    Serial.println( inChar );
  }
}


void setup() {
  delay( 500 );
  mp3_setup();
  vumeter_setup();
  
  testpinLow = true;
  pinMode( topLED, OUTPUT );
  digitalWrite( topLED, LOW );

  timer_Setup();   //last line in this function
}

void loop() {
  timer_Trigger();    //call this method often to keep the timer running



  if (timerFlags.flags.b10MS) {
    vumeter_measure();
    timer_Clear10MS();    //prepare next period
  }

  if (timerFlags.flags.b100MS){
      if (testpinLow) {
        testpinLow = false;
        digitalWrite( topLED, HIGH );
    } else {
        testpinLow = true;
        digitalWrite( topLED, LOW );
    }
    timer_Clear100MS();
  }


  mp3_check();            //check for status of the mp3-player
  check_Input();          //evaluate any commands from serial monitor
  
  
}




