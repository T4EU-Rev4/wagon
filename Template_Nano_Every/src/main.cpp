#include <main.h>
#include <i2c.h>

boolean runAnimation = false;   //becomes true, if animation should run


void setup() {
  Serial.begin(MON_SPEED);
  i2c_setup();

  //setup any other parts you need...

}

void startAnimation() {

    //put your code to start the animation here

}

void loopAnimation() {

  //put your code to loop the animation here. Code will run repeatedly while animation should run

}

void stopAnimation() {

    //put your code to stop the animation here

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