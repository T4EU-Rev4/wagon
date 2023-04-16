#include <Arduino.h>
#include "Wire.h"
#include <i2c.h>

uint8_t  ports[ NR_OF_PORTS ]; 
uint8_t  changed = 0;               //0 = no changed   1 = chanaged since last call
uint8_t  bytes_received;
uint16_t cnt = 0;                   //overall nr of bytes received

/*
 * Give values back to the master. Not used here.
 */
void i2c_request( void ) {
    Serial.print('.');  
}

/*
 * Fetch bytes from the master and store them in array port
 * This method is called by the Wire-library, if something is received
 */
void i2c_receive( int nrOfBytes ) {
  uint8_t index = 0;
  uint8_t rec;
  bytes_received = 0;
  while ( Wire.available() ) {
    rec = Wire.read() ^ 0xFF;  
    ports[ index ] = rec;
    bytes_received++;
    index = (index + 1) % NR_OF_PORTS;  
    changed = 1;  //set flag to notify main loop
    cnt++;
  }  
  Serial.print("Rec:");
  Serial.print( ports[CMD] );
  Serial.print(" ");
  Serial.print( ports[VAL] );
  Serial.print( " " );
  Serial.println( changed );
}

void i2c_setup() {
  Wire.begin( DEVICE );
  Wire.onRequest( i2c_request );
  Wire.onReceive( i2c_receive );  
  Serial.println("i2c_setup...");
}

boolean i2c_avail() {
    return (changed > 0);
}

I2CCommands i2c_command() {
    if (changed > 0) {
      changed = 0;   //report every new value only once
      if ( ports[ CMD ] < CMD_NONE )  {             //limit the values received via I2C 
        return (  (I2CCommands)ports[ CMD ]  );     //to the known constant values
      } else {
        return CMD_NONE;
      }
    } else {
        return CMD_NONE;
    }
}

uint8_t i2c_value(){
    return ports[ VAL ];
}