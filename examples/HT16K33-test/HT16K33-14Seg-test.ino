/****************************************************************
 * Simple test of ht16k33 library showing fake lat'long co-ordinates of Nxxx and xxxE
 */

#include <Wire.h>
#include "14-Segment-ASCII_BIN.h"

// Requires the following library on GitHub to control the ht6k33 driver chip
// https://github.com/wotupfoo/ht16k33.git
#include <ht16k33.h>

// Define the class
HT16K33 HT;

/****************************************************************/
void setup() {
  Serial.begin(57600);
  Serial.println(F("ht16k33 test of 14 seg digits"));
  Serial.println();

  // initialize everything, 0x00 is the i2c address for the first one (0x70 is added in the class).
  HT.begin(0x00,true);
  HT.define16segFont((uint16_t*) &FourteenSegmentASCII);

  byte led; 
  HT.clearAll();

  Serial.println(F("Turn on all LEDs"));
  // first light up all LEDs
  for (led=0; led<128; led++) {
    HT.setLedNow(led);
    delay(10);
  } // for led

  Serial.println(F("Clear all LEDs"));
  //Next clear them
  for (led=0; led<128; led++) {
    HT.clearLedNow(led);
    delay(10);
  }
  //delay(5000);
}

/****************************************************************/
void loop() {
  short i;

  for (i=0;i<=360;i++){
    byte ones = (i/1)%10;
    byte tens = (i/10)%10;
    byte hunds = (i/100)%10;
    byte thous = (i/1000)%10;
    
    HT.set16Seg(0,'N'-' ');
    HT.set16Seg(1,hunds+16);
    HT.set16Seg(2,tens+16);
    HT.set16Seg(3,ones+16);
    HT.sendLed();
    delay(25);
  }

  for (i=0;i<=360;i++){
    byte ones = (i/1)%10;
    byte tens = (i/10)%10;
    byte hunds = (i/100)%10;
    byte thous = (i/1000)%10;
    
    HT.set16Seg(0,hunds+16);
    HT.set16Seg(1,tens+16);
    HT.set16Seg(2,ones+16);
    HT.set16Seg(3,'E'-' ');
    HT.sendLed();
    delay(25);
  }

  for (i=0;i<=360;i++){
    byte ones = (i/1)%10;
    byte tens = (i/10)%10;
    byte hunds = (i/100)%10;
    byte thous = (i/1000)%10;
    
    HT.set16Seg(0,'n'-' ');
    HT.set16Seg(1,hunds+16);
    HT.set16Seg(2,tens+16);
    HT.set16Seg(3,ones+16);
    HT.sendLed();
    delay(25);
  }

  for (i=0;i<=360;i++){
    byte ones = (i/1)%10;
    byte tens = (i/10)%10;
    byte hunds = (i/100)%10;
    byte thous = (i/1000)%10;
    
    HT.set16Seg(0,hunds+16);
    HT.set16Seg(1,tens+16);
    HT.set16Seg(2,ones+16);
    HT.set16Seg(3,'e'-' ');
    HT.sendLed();
    delay(25);
  }

//  HT.clearAll();
//  delay(100);

/*
  for (i=0;i<=sizeof(FourteenSegmentASCII);i++){
    Serial.println(i+' ');
    HT.set16Seg(0,i%sizeof(FourteenSegmentASCII));
    HT.set16Seg(1,(i-1)%sizeof(FourteenSegmentASCII));
    HT.set16Seg(2,(i-2)%sizeof(FourteenSegmentASCII));
    HT.set16Seg(3,(i-3)%sizeof(FourteenSegmentASCII));
    HT.sendLed();
    delay(250);
  }
  */
} // loop  
    
