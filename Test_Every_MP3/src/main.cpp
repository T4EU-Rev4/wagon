//#include <Arduino.h>
#include <main.h>
#include <i2c.h>

extern DFRobotDFPlayerMini mp3;   //defined in mp3.cpp

uint16_t state_delay = 2000;
int title = TITLE_MIN;    //actual title 1..TITLE_MAX

uint8_t  i2cCmd;




void setup() {
  delay( 500 );
  mp3_setup();
  i2c_setup();
  
}

void serialControl(){
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
      case '+' :  mp3.volumeUp();   break;
      case '-' :  mp3.volumeDown(); break;
      case 'm' :  mp3.volume( VOLUME_MAX );   break;
      case 'x' :  mp3.volume(1);    break;
    }
    Serial.println( inChar );
  }
}

void loop() {
  
  serialControl(  );

  i2cCmd = i2c_command();
  switch ( i2cCmd ) {
    case CMD_STOP   : Serial.println("CMD_STOP");
                      mp3.stop(); 
                      break;
    case CMD_START  : Serial.println("CMD_START");
                      mp3.play( title );
                      if (title < TITLE_MAX-1) {
                        title++;
                      } else {
                        title = TITLE_MIN;
                      }  
                      break;
    case CMD_PLAY   : Serial.println("CMD_PLAY");
                      mp3.play( i2c_value() );
                      mp3.volume( VOLUME_PLAY );
                      break;
    case CMD_SKIP   : Serial.println("CMD_SKIP");
                      mp3.next();
                      break;
    case CMD_VOLUP  : Serial.println("CMD_VOLUP");
                      mp3.volumeUp();
                      break;
    case CMD_VOLDOWN: Serial.println("CMD_VOLDOWN");
                      mp3.volumeDown();
                      break;
    case CMD_VOLSETTO: Serial.println("CMD_VOLSETTO");
                       mp3.volume( i2c_value() );      
                       break;           
    case CMD_VOLMAX : Serial.println("CMD_VOLMAX");
                      mp3.volume( VOLUME_MAX );
                      break;
    case CMD_NONE   : break;
  }

  mp3_check();
  delay( 1 );
}





