#include <main.h>
#include <i2c.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel wifi(WIFI_NR_OF_LEDS, WIFI_PIN, NEO_GRB + NEO_KHZ800);     //Wifi "LED-Streifen" definieren (Anzahl LEDS, Port, Typ, Fequenz)
Adafruit_NeoPixel satelite(SAT_NR_OF_LEDS, SAT_PIN, NEO_GRB + NEO_KHZ800);   //Satelite "LED-Streifen" definieren (Anzahl LEDS, Port, Typ, Fequenz)


boolean runAnimation = false;   //becomes true, if animation should run

uint8_t   stateWiFi = 0;
uint8_t   stateSat = 0;
uint16_t  stepsWiFi = 0;
uint16_t  stepsSat = 0;



void setup() {
  Serial.begin(MON_SPEED);
  i2c_setup();

  wifi.begin();       //Wifi "LED-Streifen" initiieren
  wifi.clear();
  wifi.show();
  satelite.begin();   //Satelite "LED-Streifen" initiieren
  satelite.setBrightness(60);   //Heligkeit der Sateliten LED einstellen (0 - 100%)
  satelite.clear();
  satelite.show();
  
  stateWiFi = 0;
  stateSat = 0;

//Test:  
  //  startAnimation();
  //  runAnimation = true;
}


/**
 * @brief Do all the things here to start your animation
 * 
 */
void startAnimation() {
  stateWiFi = 1;
  stateSat = 1;
  stepsWiFi = DELAY_WIFI;
  stepsSat = 0;
  wifi.setPixelColor(0, wifi.Color(0, 255, 0));           //Datencode für die LEDs definieren (ROT)
  wifi.show(); 

}

void animateSatellite() {
  switch (stateSat)  {
  case  0: break;    //do nothing
  case  1: if (stepsSat > 0) { stepsSat--; }    //wait while red LED is on
           if (stepsSat == 0) {
             satelite.setPixelColor(0, satelite.Color(0, 0, 255));   //Datencode für die LEDs definieren (ROT)
             satelite.show();                                        //Daten an LED schicken
             stepsSat = DELAY_SAT;
             stateSat = 2; 
           } 
           break;
  case  2: if (stepsSat > 0) { stepsSat--; }
           if (stepsSat == 0) {
             satelite.setPixelColor(0, satelite.Color(0, 0, 0));     //Sateliten LED ausschalten
             satelite.show();                                        //Daten an LED schicken
             stepsSat = DELAY_SAT;
             stateSat = 1; 
           } 
           break;
  default: break;
  }
}

void animateWiFi() {
  switch (stateWiFi) {
    case 0: break;     //do nothing
    case 1: if (stepsWiFi > 0) { stepsWiFi--; }    //wait while red LED is on
            if (stepsWiFi == 0) {
              wifi.setPixelColor(1, wifi.Color(55, 255, 0));          //Datencode für die LEDs definieren (ORANGE)
              wifi.show();
              stepsWiFi = DELAY_WIFI;
              stateWiFi = 2; 
            }
            break;
    case 2: if (stepsWiFi > 0) { stepsWiFi--; }    //wait while stepsa are running
            if (stepsWiFi == 0) {
              wifi.setPixelColor(2, wifi.Color(155, 255, 0));         //Datencode für die LEDs definieren (GELB)
              wifi.show(); 
              stepsWiFi = DELAY_WIFI;
              stateWiFi = 3; 
            }
             break;
    case 3: if (stepsWiFi > 0) { stepsWiFi--; } 
            if (stepsWiFi == 0) {
              wifi.setPixelColor(3, wifi.Color(255, 0, 0));           //Datencode für die LEDs definieren (GRÜN)
              wifi.show();  
              stepsWiFi = DELAY_WIFI;
              stateWiFi = 4; 
            }
            break;      
    case 4: if (stepsWiFi > 0) { stepsWiFi--; } 
            if (stepsWiFi == 0) {
              wifi.clear();
              wifi.setPixelColor(0, wifi.Color(0, 255, 0));           //Datencode für die LEDs definieren (ROT)
              wifi.show(); 
              stepsWiFi = DELAY_WIFI;
              stateWiFi = 1;
            }
            break;
    default: break;
  }
}

/**
 * @brief This method will be called regularly, while the animation should run
 *        so place your code to run the animation here
 * 
 */
void loopAnimation() {
  animateSatellite();
  animateWiFi();
}

/**
 * @brief This method will be called to stop the animation and do some cleanup like 
 *        switching all LEDs of etc.
 * 
 */
void stopAnimation() {
  stateWiFi = 0;
  stateSat = 0;
  wifi.clear();       //Alle Daten löschen die eventuell noch vorhanden sind
  satelite.clear();   //Alle Daten löschen die eventuell noch vorhanden sind
  wifi.show();
  satelite.show();
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