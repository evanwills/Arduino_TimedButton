

#include "FixedTimeMultiPressButton.h"


FixedTimeMultiPressButton::FixedTimeMultiPressButton( byte pin ) : SimpleButton (pin) {
}
FixedTimeMultiPressButton::FixedTimeMultiPressButton( byte pin , int pressIntervalTime ) : SimpleButton (pin) {
	_pressInterval = pressIntervalTime;
}

int FixedTimeMultiPressButton::getState() {
	int output = 0;
	// how long has it been since we started
	int duration;

	if( isPressed() == true ) {
		output = -1;
		if ( _inUse == false ) {
			// the button has just been pressed
			if ( _counting == false ) {
				// the button has just been pressed for the first
				// time since it was reset. Lets remember that we're
				// now tracking how many presses
				_counting = true;

				// start the timer
				_start = millis();
			}

			duration = millis() - _start;
			if ( duration < _timeLimit ) {
				// add another press to the record
				_pressState += 1;
				_inUse = true;
			} else {
				// We have reach the maximum time in which to count
				// presses. Send what we have to the caller and reset
				// everything.

				// send the number of presses to the caller
				output = _pressState;
				// reset presses
				_pressState = 0;
				// stop counting
				_counting = false;

				_inUse = false;
			}
		}

		// let the caller know that the button is being pressed
		// but that we don't know what the total number of presses
		// is yet.
		return output;
	}

	if ( _counting == true ) {
		duration = millis() - _start;
		if( duration > _timeLimit ) {
			// the user has stopped pressing the button for
			// the moment

			// send the number of presses to the caller
			output = _pressState;
			// stop counting
			_counting = false;
			// reset presses
			_pressState = 0;
		} else {
			// let the caller know we're still counting presses
			output = -1;
		}
		_inUse = false;
	}
	// button is no longer being pressed

	return output;
}


