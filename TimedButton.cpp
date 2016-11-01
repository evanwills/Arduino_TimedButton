#include "TimedButton.h"




TimedButton::TimedButton (byte pin) : SimpleButton (pin) {
	//btnPin = pin;
	//pinMode(btnPin, INPUT);
}

/**
 * How many seconds has the button been pressed for
 * If it's currently being pressed then it returns -1 to let caller
 * know that it can't give a final answer yet.
 * If it's not being pressed, then it returns zero.
 * If the button has just been released, it returns the number of
 * milliseconds the button was pressed for.
 *
 * NOTE: It is assumed that the button will be pressed for less than
 *		 65 seconds. (Otherwise, You'll probabaly have to think of
 *		 another way of using this class.)
 */
int TimedButton::getState() {
	if( isPressed() == true ) {
		if (start == 0 ) {
			start = millis();
		}
		// update how long the button has been pressed for
		pressDuration = millis() - start;
		inUse = true;

		// let the caller know that the button is being pressed
		// but that we don't know for how long yet.
		return -1;
	} else {
		// button is no longer being pressed.
		// we keep the press duration for one call so
		// that buttonPressedFor() can be used effectively
		if( inUse == false ) {
			// button was being pressed two calls ago
			// reset for next press
			start = 0;
			pressDuration = 0;
		}
		// button is no longer being pressed
		inUse = false;
		return (int) pressDuration;
	}
}
