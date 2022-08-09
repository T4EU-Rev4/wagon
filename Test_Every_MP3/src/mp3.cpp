#include <main.h>

SoftwareSerial mySoftwareSerial(SOFTSER_RX, SOFTSER_TX);    // RX=10, TX=11
DFRobotDFPlayerMini mp3;
void mp3_printDetail(uint8_t type, int value);      //prototype is local


void mp3_setup() {
  mySoftwareSerial.begin(SOFTSER_SPEED);
  Serial.begin(MON_SPEED);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  mp3.begin(mySoftwareSerial);
  delay( 3000 );

  Serial.println(F("DFPlayer Mini online."));
  
  mp3.volume(5);  //Set volume value. From 0 to 30
  //myDFPlayer.play(2);  //Play the first mp3

}


void mp3_check() {
  if (mp3.available()) {
    mp3_printDetail(mp3.readType(), mp3.read());      //Print the detail message from DFPlayer to handle different errors and states.
  }
}


void mp3_printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:  Serial.println(F("Time Out!"));
      break;
    case WrongStack:  Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:  Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:   Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:    Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:  Serial.print(F("Number:"));
                                Serial.print(value);
                                Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:         
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:              Serial.println(F("Card not found"));    break;
        case Sleeping:          Serial.println(F("Sleeping"));          break;
        case SerialWrongStack:  Serial.println(F("Get Wrong Stack"));          break;
        case CheckSumNotMatch:  Serial.println(F("Check Sum Not Match"));       break;
        case FileIndexOut:      Serial.println(F("File Index Out of Bound"));   break;
        case FileMismatch:      Serial.println(F("Cannot Find File"));          break;
        case Advertise:         Serial.println(F("In Advertise"));      break;
        default:          break;
      }
      break;
    default:
      break;
  }
}
