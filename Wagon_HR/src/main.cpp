#include <main.h>
#include <i2c.h>
#include <Adafruit_NeoPixel.h>

boolean runAnimation = false;   //becomes true, if animation should run
uint8_t nextColor = 0;          //step the animation forward

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


void setup() {
  Serial.begin(MON_SPEED);
  i2c_setup();

  //setup any other parts you need...
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255)
}

/**
 * @brief Do all the things here to start your animation
 * 
 */
void startAnimation() {

}

/**
 * @brief This method will be called regularly, while the animation should run
 *        so place your code to run the animation here
 * 
 */
void loopAnimation() {
  // Fill along the length of the strip in various colors...
  switch (nextColor) {
    case 0: colorWipe(strip.Color(255,   0,   0), 50); // Red
            nextColor++;
            break;
    case 1: colorWipe(strip.Color(  0, 255,   0), 50); // Green
            nextColor++;
            break;
    case 2: colorWipe(strip.Color(  0,   0, 255), 50); // Blue
            nextColor = 0;
            break;
    default: nextColor = 0;
  }

}

/**
 * @brief This method will be called to stop the animation and do some cleanup like 
 *        switching all LEDs of etc.
 * 
 */
void stopAnimation() {
    strip.clear();
    strip.show();  
}



void loop() {
  I2CCommands i2cCmd = i2c_command();   //fetch a new command via I2C
  switch ( i2cCmd ) {
    case CMD_STOP   : Serial.println("CMD_STOP");
                      runAnimation = false;
                      stopAnimation(); 
                      break;
    case CMD_START  : Serial.println("CMD_START");
                      startAnimation();
                      runAnimation = true;
                      break;
    case CMD_NONE   : break;
  }

  //runAnimation = true;    //test

  if (runAnimation) {
    loopAnimation();
  }

  delay(1);   //propably not needed here, 
}




// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}