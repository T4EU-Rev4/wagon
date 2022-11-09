//#include <Arduino.h>
#include <main.h>

extern DFRobotDFPlayerMini mp3;   //defined in mp3.cpp

uint16_t state_delay = 2000;
int title = 1;

void setup() {
  delay( 500 );
  mp3_setup();
  
}

void loop() {
  
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



  
  mp3_check();
  delay( 1 );
}





