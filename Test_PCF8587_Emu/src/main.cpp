#include <main.h>

/*
 * This program demonstrates the emulation of a PCF8575 by the nano every
 * In this example, only the outputs are used. Input capabilities as well as the interrupt
 * service of the PCF8575 is not used here, but of course could be.
 * For this simple case, no additional library is used. Just Wire.
 * 
 */

uint8_t portA[] = {2, 3, 4, 5, 6, 7, 8, 9};
uint8_t portB[] = {10, 11, 12, 13, A0, A1, A2, A3};

uint8_t ports[ NR_OF_PORTS ]; 
uint8_t changed = 0;
uint8_t bytes_received;
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
    rec = Wire.read() ^ 0xFF;   //invert the bit pattern
    ports[ index ] = rec;
    bytes_received++;
    index = (index + 1) % NR_OF_PORTS;  
    changed = 1;  //set flag to notify main loop
  }  
}

void setPortA( uint8_t data ) {
  for (int i=0; i<8; i++) {
    if ( (data & ( 1 << i ) ) > 0 ) {
      digitalWrite( portA[i], HIGH );
    } else {
      digitalWrite( portA[i], LOW );
    }
  }
}

void setPortB( uint8_t data ){
  for (int i=0; i<8; i++) {
    if ( (data & ( 1 << i ) ) > 0 ) {
      digitalWrite( portB[i], HIGH );
    } else {
      digitalWrite( portB[i], LOW );
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  Wire.begin( DEV );
  Wire.onRequest( requestI2C );
  Wire.onReceive( receiveI2C );

  for (int i=0; i<8; i++ ){
    pinMode( portA[i], OUTPUT );
    pinMode( portB[i], OUTPUT );
  }
  for (int i=0; i<8; i++ ){
    digitalWrite( portA[i], LOW );
    digitalWrite( portB[i], LOW );
  }

  for (int i=0; i<NR_OF_PORTS; i++) {
    ports[ i ] = 0;  
  }
 
}

void loop() {
  uint8_t n;

  if (changed > 0) {
  
    n = ports[PCF_PORT_A];
    setPortA( n );
    
    n = ports[PCF_PORT_B];
    setPortB( n );

    changed = 0;
  }


}