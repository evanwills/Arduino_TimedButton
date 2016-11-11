
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>


#include "FlexibleButtons.h"

Adafruit_SSD1306 OLEDScreen(4); //OLED_RESET

//SimpleButton::makePinModeAlwaysPullup();

// Artbot buttons & pins:
//	0 - 37
//	1 - 35
//	2 - 33
//	3 - 31
//	4 - 29
//	5 - 27
//	6 - 25
//	7 - 23
//SimpleButton btn(23, true);
//ToggleButton btn(23, true, 5);
//TimedButton btn(23, true);
//MultiPressButton btn(23, true);
FixedTimeMultiPressButton btn(23, true);


void setup() {
	// put your setup code here, to run once:

	// Initialise the OLED display
	// Note: it is necessary to change a value in the Adafruit_SSD1306 library to set the screen size to 128x64
	OLEDScreen.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	OLEDScreen.clearDisplay();

	// Set some default values for writing to the OLED screen
	OLEDScreen.setTextColor(WHITE);
}

void loop() {
	OLEDScreen.clearDisplay();

	// Write "Hello" in small
	OLEDScreen.setTextSize(1);
	OLEDScreen.setCursor(0, 0);
	OLEDScreen.print("Testing: ");
	OLEDScreen.setCursor(16, 12);
	OLEDScreen.print("FlexibleButtons"); //this copies some text to the screens memory

	int state = btn.getState();


	OLEDScreen.setCursor(28, 40);
	OLEDScreen.print("state: "); //this copies some text to the screens memory
	OLEDScreen.print(state); //this copies some text to the screens memory


//	// Turns the LED on if pressed for more than 1 second
//	if ( btn.getState() > 1 ) {
//		digitalWrite(13, HIGH);
//	} else {
//		digitalWrite(13, LOW);
//	}

//	// Turns the board's LED on when button is pressed
//	// --------------------------------------------------
//	// for more than 1 second
//	if ( btn.getState() > 1000 ) {
//	// --------------------------------------------------
//	// at least twice in quick succession
//	if ( btn.getState() >= 2 ) {
//	// --------------------------------------------------
//	// at least three times within half a second
//	if ( btn.getState() >= 3 ) {
//	// --------------------------------------------------
//		digitalWrite(13, HIGH);
//		delay(2000);
//	} else {
//		digitalWrite(13, LOW);
//	}


//	// ==============================================================
//	// Testing how many times the multi press buttons were pressed


	//Serial.begin(9600);
	//Serial.begin(115200);
	//Serial.print(state);
//	while ( state > 0 ) {
//		OLEDScreen.setCursor(0, 32);
//		OLEDScreen.print("inside loop"); //this copies some text to the screens memory
//		digitalWrite(13, HIGH);delay(500);
//		digitalWrite(13, LOW);delay(500);
//		state -= 1;
//
//		OLEDScreen.setCursor(0, 48);
//		OLEDScreen.print("state = ");
//		OLEDScreen.print(state);
//	}
//
//	OLEDScreen.setCursor(0, 56);
//	OLEDScreen.print("finished loop"); //this copies some text to the screens memory
//	delay(2000);
//
//
//	digitalWrite(13, HIGH); delay(50); digitalWrite(13, LOW); delay(50);
//	digitalWrite(13, HIGH); delay(50); digitalWrite(13, LOW); delay(50);
//	digitalWrite(13, HIGH); delay(50); digitalWrite(13, LOW); delay(50);
//	digitalWrite(13, HIGH); delay(50); digitalWrite(13, LOW); delay(50);
//	delay(2000);

	OLEDScreen.display();
}
