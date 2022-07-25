#include "main.h"


#define NR_OF_PORTS 2
#define PCF_PORT_A  0
#define PCF_PORT_B  1

//define the port pins, acting as one of the 16 pins of a PCF8575
//The position in the array corresponds with the bit nr
uint8_t portA[] = {2, 3, 4, 5, 6, 7, 8, 9};
uint8_t portB[] = {10, 11, 12, 13, A0, A1, A2, A3};


void setup() {
    Serial.begin(115200);
  for (uint8_t i = 0; i<8; i++) {
    pinMode( portA[i], OUTPUT);
    pinMode( portB[i], OUTPUT);

    digitalWrite( portA[i], LOW);
    digitalWrite( portB[i], LOW);
  }
  
}

void loop()
{
 
  for (uint8_t i = 0; i<8; i++) {
    Serial.print( "Port A, Bit " );  Serial.println( portA[i] );
    for( uint8_t k=0; k<4; k++) {
      // turn the LED on (HIGH is the voltage level)
      digitalWrite( portA[i], HIGH);
      // wait for a second
      delay(200);
      // turn the LED off by making the voltage LOW
      digitalWrite( portA[i], LOW);
      // wait for a second
      delay(200);
    }  
  } 


  for (uint8_t i = 0; i<8; i++) {
    Serial.print( "Port B, Bit " );  Serial.println( portB[i] );
    for( uint8_t k=0; k<4; k++) {
      // turn the LED on (HIGH is the voltage level)
      digitalWrite( portB[i], HIGH);
      // wait for a second
      delay(200);
      // turn the LED off by making the voltage LOW
      digitalWrite( portB[i], LOW);
      // wait for a second
      delay(200);
    }  
  } 




}