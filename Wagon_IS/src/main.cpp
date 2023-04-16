#include <main.h>
#include <i2c.h>

boolean runAnimation = false;   //becomes true, if animation should run

uint16_t  led_Delay = 0;
uint8_t   led=0;                //0=Off,  1=RED,  2=Green

void setLED() {
  switch( led ) {
    case 1: digitalWrite( LED_ROT, LOW);
            digitalWrite( LED_GRUEN, HIGH );
            break;
    case 2: digitalWrite( LED_ROT, HIGH);
            digitalWrite( LED_GRUEN, LOW );
            break;
    default: digitalWrite( LED_ROT, HIGH);
             digitalWrite( LED_GRUEN, HIGH );
  }
}

void setup() {
  Serial.begin(MON_SPEED);
  i2c_setup();

  //setup any other parts you need...
  pinMode( LED_ROT, OUTPUT );
  pinMode( LED_GRUEN, OUTPUT );
  led=0;  
  setLED();

  
}

/**
 * @brief Do all the things here to start your animation
 * 
 */
void startAnimation() {
  led = 1;
  led_Delay = LED_RED_ON;
  setLED();
}

/**
 * @brief This method will be called regularly, while the animation should run
 *        so place your code to run the animation here
 * 
 */
void loopAnimation() {
    if (led_Delay > 0) {
      led_Delay--;
    } else {
      switch (led)  {
      case 0: break;      //beide LEDs aus
      case 1: led = 2;  
              led_Delay = LED_GREEN_ON;
              break;
      case 2: led = 1;  
              led_Delay = LED_RED_ON;
              break;
      default: led = 1;  
               led_Delay = LED_RED_ON;
               break;
      }
      setLED();
    }
    

}

/**
 * @brief This method will be called to stop the animation and do some cleanup like 
 *        switching all LEDs of etc.
 * 
 */
void stopAnimation() {
  led = 0;
  setLED();
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