#include <main.h>

uint16_t sensorValue = 0;
uint16_t offset      = 380;


#define VU_COUNT      9
#define VU_VALUES     6

#define LED_AN        LOW
#define LED_AUS       HIGH

#define SOUNDPIN       A0

uint8_t     vu[] = { 10, 9, 8, 7, 5, 4, 3, 2, 13 };
uint16_t    vuLimits[] = { 50, 100, 200, 300, 400, 500, 600, 700, 800  };

uint16_t    vuValues[] = {0, 0, 0, 0, 0, 0};



void vumeter_LampTest() {
    for (int i=0; i<VU_COUNT; i++) {
        digitalWrite( vu[i], LED_AN );
        delay(100);
        digitalWrite( vu[i], LED_AUS );
    }
}

void vumeter_out( uint16_t value ){
    for (int i=0; i<VU_COUNT; i++) {
      if (value >= vuLimits[i]) {
        digitalWrite( vu[i], LED_AN );
      }  else {
        digitalWrite( vu[i], LED_AUS );
      }   
    }
}

void vumeter_Cler() {
    for (int i = 0; i<VU_COUNT; i++) {
        digitalWrite( vu[i], LED_AUS );
    }    
}

void vumeter_setup() {
    //LED output
    for (int i = 0; i<VU_COUNT; i++) {
        pinMode( vu[i], OUTPUT );
    }
    vumeter_Cler();
    vumeter_LampTest();
}




void vumeter_measure() {
    sensorValue = analogRead( SOUNDPIN );
    if (sensorValue > offset) { sensorValue -= offset; }

    for (int i=0; i < VU_VALUES-1; i++){
        vuValues[i+1] = vuValues[i];  
    }; 
    vuValues[0] = sensorValue;
    
    for (int i=1; i < VU_VALUES; i++){
        sensorValue += vuValues[i];  
    }; 
    sensorValue /= VU_VALUES;
    
//    Serial.println( sensorValue, DEC );
    vumeter_out( sensorValue );
}


