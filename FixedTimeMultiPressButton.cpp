

#include "FixedTimeMultiPressButton.h"


FixedTimeMultiPressButton::FixedTimeMultiPressButton( byte pin ) : SimpleButton (pin) {
}
FixedTimeMultiPressButton::FixedTimeMultiPressButton( byte pin , int pressIntervalTime ) : SimpleButton (pin) {
	pressInterval = pressIntervalTime;
}

int FixedTimeMultiPressButton::getState() {
	int output = 0;
	// how long has it been since we started
	int duration;

	if( isPressed() == true ) {
		output = -1;
		if ( inUse == false ) {
			// the button has just been pressed
			if ( counting == false ) {
				// the button has just been pressed for the first
				// time since it was reset. Lets remember that we're
				// now tracking how many presses
				counting = true;

				// start the timer
				start = millis();
			}

			duration = millis() - start;
			if ( duration < pressInterval ) {
				// add another press to the record
				pressState += 1;
				inUse = true;
			}
		}

		// let the caller know that the button is being pressed
		// but that we don't know what the total number of presses
		// is yet.
		return output;
	}

	if ( counting == true ) {
		duration = millis() - start;
		if( duration > pressInterval ) {
			// the user has stopped pressing the button for
			// the moment

			// send the number of presses to the caller
			output = pressState;
			// stop counting
			counting = false;
			// reset presses
			pressState = 0;
		} else {
			// let the caller know we're still counting presses
			output = -1;
		}
		inUse = false;
	}
	// button is no longer being pressed

	return output;
}


