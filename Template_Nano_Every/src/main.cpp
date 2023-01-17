#include <main.h>
#include <i2c.h>

boolean runAnimation = false;   //becomes true, if animation should run


void setup() {
  Serial.begin(MON_SPEED);
  i2c_setup();

  //setup any other parts you need...

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

}

/**
 * @brief This method will be called to stop the animation and do some cleanup like 
 *        switching all LEDs of etc.
 * 
 */
void stopAnimation() {

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

  if (runAnimation) {
    loopAnimation();
  }

  delay(1);   //propably not needed here, 
}