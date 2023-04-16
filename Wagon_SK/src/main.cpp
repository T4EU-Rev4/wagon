#include <main.h>
#include <i2c.h>
#include <Servo.h>

boolean runAnimation = false;   //becomes true, if animation should run

Servo myservo;
int       pos   = POS_MAX; 
uint8_t   state = 0;
uint16_t  steps = 0;

void moveToMin() {
  for (pos = POS_MAX; pos >= POS_MIN; pos -= 1) { 
    myservo.write(pos);              
    delay(10);                       
  } 
}

void moveToMax(){
  for (pos = 5; pos <= 55; pos += 1) { 
    myservo.write(pos);              
    delay(10);                       
  }  
}

void setup() {
  Serial.begin(MON_SPEED);
  i2c_setup();

  //setup any other parts you need...
  myservo.attach(SERVO);

  pinMode(LED_ROT, OUTPUT);
  pinMode(LED_GRUEN, OUTPUT);

  myservo.write( pos );
  digitalWrite(LED_ROT, LOW);
  digitalWrite(LED_GRUEN, LOW);

  state = 0;


//Test:  
//  state = 1;
//  digitalWrite(LED_ROT, HIGH); 
//  steps = DELAY_RED;
}

/**
 * @brief Do all the things here to start your animation
 * 
 */
void startAnimation() {
  state = 1;
  digitalWrite(LED_ROT, HIGH); 
  steps = DELAY_RED;
}

/**
 * @brief This method will be called regularly, while the animation should run
 *        so place your code to run the animation here
 * 
 */
void loopAnimation() {
  switch (state) {
    case 0: break;     //do nothing
    case 1: if (steps > 0) { steps--; }    //wait while red LED is on
            if (steps == 0) {
              pos = POS_MAX;
              steps = DELAY_SERVO;
              state = 2; 
            }
            break;
    case 2: if (steps > 0) { steps--; }    //wait while stepsa are running
            if (steps == 0) {
              myservo.write(pos); 
              pos--;
              steps = DELAY_SERVO;
              if (pos < POS_MIN ) {
                digitalWrite(LED_ROT, LOW); 
                steps = DELAY_CLOSE;
                state = 3;
              }      
            }
             break;
    case 3: if (steps > 0) { steps--; } 
            if (steps == 0) {
              digitalWrite(LED_GRUEN, HIGH); 
              steps = DELAY_GREEN;
              state = 4;
            }
            break;      
    case 4: if (steps > 0) { steps--; } 
            if (steps == 0) {
              digitalWrite(LED_GRUEN, LOW);
              steps = DELAY_CLOSE;
              state = 5;
            }
            break;
    case 5: if (steps > 0) { steps--; } 
            if (steps == 0) {
              digitalWrite(LED_ROT, HIGH); 
              steps = DELAY_RED;
              state = 6;
            }
            break;
    case 6: if (steps > 0) { steps--; } 
            if (steps == 0) {
              pos = POS_MIN;
              steps = DELAY_SERVO;
              state = 7; 
            }
            break;
    case 7: if (steps > 0) { steps--; }    //wait while stepsa are running
            if (steps == 0) {
              myservo.write(pos); 
              pos++;
              steps = DELAY_SERVO;
              if (pos > POS_MAX ) {
                digitalWrite(LED_ROT, LOW); 
                steps = DELAY_GREEN;
                state = 8;
              }      
            }
            break;
    case 8: if (steps > 0) { steps--; } 
            if (steps == 0) {
              steps = DELAY_RED;
              state = 1;
            }
            break;
    case 9: break;
    default: break;
  }

}

/**
 * @brief This method will be called to stop the animation and do some cleanup like 
 *        switching all LEDs of etc.
 * 
 */
void stopAnimation() {
  state = 0;
  digitalWrite(LED_ROT, LOW);
  digitalWrite(LED_GRUEN, LOW);
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