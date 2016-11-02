//#include "SimpleButton.h"
//#include "ToggleButton.h"
//#include "TimedButton.h"
//#include "MultiPressButton.h"
//#include "FixedTimeMultiPressButton.h"
#include "MultiModeButton.h"

//SimpleButton simpleButton(53);
//ToggleButton toggleButton(53);
//TimedButton timedButton(53);
//MultiPressButton multiPressButton(53);
//FixedTimeMultiPressButton fixedTimeMultiPressButton(53);
MultiModeButton multiModeButton(53);

void setup() {
	// put your setup code here, to run once:
//	simpleButton.makePinModePullup();
//	toggleButton.makePinModePullup();
//	timedButton.makePinModePullup();
//	multiPressButton.makePinModePullup();
//	fixedTimeMultiPressButton.makePinModePullup();
	multiModeButton.makePinModePullup();
	pinMode(13, OUTPUT);
}

void loop() {
	// turns the LED on if pressed
//	if ( simpleButton.getState() == 1 ) {
//		digitalWrite(13, HIGH);
//	} else {
//		digitalWrite(13, LOW);
//	}

//	// Turns the LED on if pressed for more than 1 second
//	if ( toggleButton.getState() > 1 ) {
//		digitalWrite(13, HIGH);
//	} else {
//		digitalWrite(13, LOW);
//	}

//	// Turns the board's LED on when button is pressed
//	// --------------------------------------------------
//	// for more than 1 second
//	if ( timedButton.getState() > 1000 ) {
//	// --------------------------------------------------
//	// at least twice in quick succession
//	if ( multiPressButton.getState() >= 2 ) {
//	// --------------------------------------------------
//	// at least three times within half a second
//	if ( fixedTimeMultiPressButton.getState() >= 3 ) {
//	// --------------------------------------------------
//		digitalWrite(13, HIGH);
//		delay(2000);
//	} else {
//		digitalWrite(13, LOW);
//	}

	// Turns the LED on if pressed at least twice in quick succession
//	if ( multiModeButton.getState() > 1000 ) {
	if ( multiModeButton.multiPress() >= 2 ) {
		digitalWrite(13, HIGH);
		delay(2000);
	} else {
		digitalWrite(13, LOW);
	}

}
