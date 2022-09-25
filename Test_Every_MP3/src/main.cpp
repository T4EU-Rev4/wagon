//#include <Arduino.h>
#include <main.h>
#include <timer.h>

extern DFRobotDFPlayerMini mp3;   //defined in mp3.cpp
extern union TTimer timerFlags;       //keep all the flags in one byte


//uint16_t state_delay = 2000;
//int title = 1;
uint8_t ports[ NR_OF_PORTS ];       //I2C Interface
uint8_t changed = 0;                //I2C Interface
uint8_t bytes_received;             //I2C Interface

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
      case '+' :  mp3.volumeUp();  break;
      case '-' :  mp3.volumeDown(); break;
      
    }
    Serial.println( inChar );
  }
}

void check_i2c() {
  if (changed > 0) {
    switch( ports[PCF_PORT_A] ) {
      case I2C_CMD_STOP : mp3.stop();
                          break;
      case I2C_CMD_PLAY : mp3.play( ports[PCF_PORT_B] );
                          break;
      case I2C_CMD_VOLUP: mp3.volumeUp();
                          break;
      case I2C_CMD_VOLDN: mp3.volumeDown();
                          break;
      case I2C_CMD_VOL  : mp3.volume( ports[PCF_PORT_B] );
    default : ;  //I2C_CMD_NOP
    }
    changed = 0;
    Serial.print("cmd=");      Serial.print( ports[PCF_PORT_A] );     //Command to debug output
    Serial.print("   val=");   Serial.println( ports[PCF_PORT_B] );
  }  
}

/*
 * Give values back to the master. Not used here.
 */
void requestI2C( void ) {
    Serial.print('.');  
}

/*
 * Fetch bytes from the master and store them in array port
 */
void receiveI2C( int nrOfBytes ) {
  uint8_t index = 0;
  uint8_t rec;
  bytes_received = 0;
  while ( Wire.available() ) {
    rec = Wire.read();   //invert the bit pattern
    ports[ index ] = rec;
    bytes_received++;
    index = (index + 1) % NR_OF_PORTS;  
    changed = 1;  //set flag to notify main loop
  }  
}

void setup() {
  delay( 500 );
  mp3_setup();
  vumeter_setup();
  
  testpinLow = true;
  pinMode( topLED, OUTPUT );
  digitalWrite( topLED, LOW );

  for (int i=0; i<NR_OF_PORTS; i++) {
    ports[ i ] = 0;  
  }
  Wire.begin( DEV );                //initialize i2c interface
  Wire.onRequest( requestI2C );     //callback on transmit
  Wire.onReceive( receiveI2C );     //callback on receive

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
  check_i2c();            //evaluate commans via i2c
  
}




