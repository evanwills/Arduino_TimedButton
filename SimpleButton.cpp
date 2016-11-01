#include "SimpleButton.h"


//  END:  (basic) DumbButton class
// ========================================================
// START: (basic) DumbButton class

SimpleButton::SimpleButton(byte pin) {
	btnPin = pin;
	pinMode(btnPin, INPUT);
}

bool SimpleButton::pressed() {
	if (digitalRead(btnPin) == HIGH) {
		return false;
	} else {
		return true;
	}
}

unsigned int SimpleButton::readButton() {
	if ( pressed() == true ) {
		return 1;
	} else {
		return 0;
	}
}

/**
 * sometimes it's necessary to make the input mode PULLUP.
 *
 * This is primarily for the rotaryEncoder class but may be
 * useful elsewhere
 */
void SimpleButton::makePinModePullup() {
	pinMode(btnPin, INPUT_PULLUP);
}
