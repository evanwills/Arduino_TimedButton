#include "SimpleButton.h"


//  END:  (basic) DumbButton class
// ========================================================
// START: (basic) DumbButton class

SimpleButton::SimpleButton(byte pin) {
	_btnPin = pin;
	if( SimpleButton::_alwaysPullup == true ) {
		pinMode(_btnPin, INPUT_PULLUP);
	} else {
		pinMode(_btnPin, INPUT);
	}
}

bool SimpleButton::isPressed() {
	if (digitalRead(_btnPin) == HIGH) {
		return false;
	} else {
		return true;
	}
}

int SimpleButton::getState() {
	if ( isPressed() == true ) {
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
	pinMode(_btnPin, INPUT_PULLUP);
}

void SimpleButton::makePinModeAlwaysPullup() {
	SimpleButton::_alwaysPullup = true;
}

bool SimpleButton::_alwaysPullup = false;