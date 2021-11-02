/****************************************************************
 * Simple test of ht16k33 library showing fake lat'long co-ordinates of Nxxx and xxxE
 */

#include <Wire.h>
#include <14-Segment-ASCII_BIN.h>

// Requires the following library on GitHub to control the ht6k33 driver chip
// https://github.com/wotupfoo/ht16k33.git
#include <ht16k33.h>

#define CONTROLLERS 2
#define DIGITS (4*CONTROLLERS)
#define SEGMENTS (8*DIGITS)

// Define the class
HT16K33 HT[CONTROLLERS];

/****************************************************************/
void setup() {
  Serial.begin(57600);
  Serial.println(F("ht16k33 test of 14 seg digits - mimics the Lat Long of GPS"));
  Serial.println();

  // initialize everything, 0x00 is the i2c address for the first one (0x70 is added in the class).
  for(byte i=0; i<CONTROLLERS; i++)
  {
	  HT[i].begin(i,true);
	  HT[i].define16segFont((uint16_t*) &FourteenSegmentASCII);
	  HT[i].clearAll();
  }

  byte led; 

  Serial.println(F("Turn on all LEDs"));
  for(byte i=0; i<CONTROLLERS; i++)
  {
	  // first light up all LEDs
	  for (led=0; led<SEGMENTS; led++) 
	  {
		HT[i].setLedNow(led);
		delay(10);
	  }
  }

  Serial.println(F("Clear all LEDs"));
  //Next clear them
  for(byte i=0; i<CONTROLLERS; i++)
  {
	  // first light up all LEDs
	  for (led=0; led<SEGMENTS; led++) 
	  {
		HT[i].clearLedNow(led);
		delay(10);
	  }
  }
}

/****************************************************************/
void loop() {

	// Pretend to be a Lat/Long GPS display.
	// Assumes 2 CONTROLLERS
	// Assumes 4 DIGITS per CONTROLLERS
	short ns, ew;
	ns = 15 + rand()%2;
	ew = 164 + rand()%2;

	byte ones = (ns/1)%10;
	byte tens = (ns/10)%10;
	byte hunds = (ns/100)%10;
	byte thous = (ns/1000)%10;

	HT[0].set16Seg(0,'N'-' ');
	HT[0].set16Seg(1,tens+16);
	HT[0].set16Seg(2,ones+16);
	HT[0].setDot(2,true);
	HT[0].set16Seg(3,0); // space
	HT[0].sendLed();

	ones = (ew/1)%10;
	tens = (ew/10)%10;
	hunds = (ew/100)%10;
	thous = (ew/1000)%10;
	HT[1].set16Seg(0,hunds+16); // space
	HT[1].set16Seg(1,tens+16);
	HT[1].set16Seg(2,ones+16);
	HT[1].setDot(2,true);
	HT[1].set16Seg(3,'E'-' ');
	HT[1].sendLed();
	delay(200);

} // loop  
    