#include <main.h>

// Set i2c address
PCF8575 pcf8575(0x20);


void setup() {
	Serial.begin(115200);

	// Set pinMode to OUTPUT:  all Pins to output
	for (uint8_t i=P0; i<=P15; i++) {
	  pcf8575.pinMode(i, OUTPUT);
	}

	pcf8575.begin();
}

void loop() {
  for (uint8_t i=P0; i<=P15; i++) {
   if (i==0) { 
      pcf8575.digitalWrite(P15, HIGH);
   } else {
      pcf8575.digitalWrite(i-1, HIGH);
   }
    delay(10);
    pcf8575.digitalWrite( i, LOW);   
    delay(250);
  }
}