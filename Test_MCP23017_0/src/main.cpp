#include <main.h>


#define SDA PC4
#define SCL PC5
#define SPEED 250

//see: https://elektro.turanis.de/html/prj128/index.html   (german)
uint8_t led;
uint8_t device = DEV_0;

void setup() {
  Serial.begin(19200);         // start serial communication for debug purposes
  Serial.println("init");
  Wire.begin();                // start I2C communication

}

void setupMCP(  ) {
  Wire.beginTransmission( device );
  Wire.write( IODIRA );           // IODIRA register
  Wire.write( 0x00 );           // set all of port A to outputs
  Wire.endTransmission();
  Wire.beginTransmission( device );
  Wire.write( IODIRB );           // IODIRB register
  Wire.write( 0x00 );           // set all of port B to outputs
  Wire.endTransmission();
  Serial.print("Adr: ");
  Serial.println( device );
}


void loop() {
  //if you want to loop over all 8 devices, just uncomment line 35 and 69
  //for ( device = 0x20; device <= 0x27; device++ ) {
    setupMCP();
    Serial.println("Port A");
    //Port A
    for (uint8_t i = 0; i<8; i++) {
      led = (1 << i);
      Serial.print( led ); Serial.print(" ");
      Wire.beginTransmission( device );
      Wire.write( GPIOA );    // address port A
      Wire.write( led );      // value to send
      Wire.endTransmission();
      delay( SPEED );
    }
    Wire.beginTransmission( device );
    Wire.write( GPIOA );    // address port A
    Wire.write( 0 );        // value to send
    Wire.endTransmission();
    Serial.println("");
    //Port B
    Serial.println("Port B");
    for (uint8_t i = 0; i<8; i++) {
      led = (1 << i);
      Wire.beginTransmission( device );
      Wire.write( GPIOB );    // address port A
      Wire.write( led );      // value to send
      Wire.endTransmission();
      delay( SPEED );
    }
    Wire.beginTransmission( device );
    Wire.write( GPIOB );    // address port A
    Wire.write( 0 );        // value to send
    Wire.endTransmission();


  //}






}