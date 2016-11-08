#include "FlexibleButtons.h"


// ==================================================================
// START: SimpleButton class


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


//  END:  SimpleButton class
// ==================================================================





// ==================================================================
// START: ToggleButton class


ToggleButton::ToggleButton( byte pin ) : SimpleButton (pin) {
	// just do SimpleButton constructor
}
ToggleButton::ToggleButton( byte pin , byte limit ) : SimpleButton (pin) {
	_maxPresses = limit;
}


/**
 * returns how many times the button has been pressed since it was
 * last reset
 */
int ToggleButton::getState() {

	if( isPressed() == true ) {
		// This is the first time we've noticed this button has been
		// pressed
		if ( _inUse == false ) {
			// because this may method be called many times during a
			// single press, we only want to increment once per press
			// so this is done within this IF statement

			// add another press to the record
			_pressCount += 1;

			// check how many times the button has been pressed. If
			// it has exceded the maximum set it back to zero
			if ( _pressCount > _maxPresses ) {
				_pressCount = 0;
			}
			_inUse = true;
		}
	} else {
		_inUse = false;
	}

	// make the value returned match what the prototype expects
//	return  _pressCount;
	return (int) _pressCount;
}


//  END:  ToggleButton class
// ==================================================================





// ==================================================================
// START: TimedButton class


TimedButton::TimedButton (byte pin) : SimpleButton (pin) {
	// just do SimpleButton constructor
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
		if (_start == 0 ) {
			_start = millis();
		}
		// update how long the button has been pressed for
		_pressDuration = millis() - _start;
		_inUse = true;

		// let the caller know that the button is being pressed
		// but that we don't know for how long yet.
		return -1;
	} else {
		// button is no longer being pressed.
		// we keep the press duration for one call so
		// that buttonPressedFor() can be used effectively
		if( _inUse == false ) {
			// button was being pressed two calls ago
			// reset for next press
			_start = 0;
			_pressDuration = 0;
		}
		// button is no longer being pressed
		_inUse = false;
		return (int) _pressDuration;
	}
}


//  END:  TimedButton class
// ==================================================================





// ==================================================================
// START: MultiPressButton class


MultiPressButton::MultiPressButton( byte pin ) : SimpleButton (pin) {
	// just do SimpleButton constructor
}
MultiPressButton::MultiPressButton( byte pin , int maxNoPressInterval )  : SimpleButton (pin) {
	_maxNoPress = maxNoPressInterval;
}

int MultiPressButton::getState() {
	if( isPressed() == true ) {
		if ( _inUse == false ) {
			// the button has just been pressed
			if ( _counting == false ) {
				// the button has just been pressed for the first
				// time since it was reset. Lets remember that we're
				// now tracking how many presses
				_counting = true;
			}

			// because this may be called many times during a single
			// press we only want to increment once per presss so
			// this is done within this IF statement

			// add another press to the record
			_pressCount += 1;
			_inUse = true;
		}

		// let the caller know that the button is being pressed
		// but that we don't know what the total number of presses
		// is yet.
		return -1;
	} else {
		int output = 0;
		if ( _counting == true ) {
			// we know we're counting now we'll check how long it was
			// since the button was released
			if ( _inUse == true ) {
				// this is the first time we've noticed the button
				// has been released let's record that time
				_notPressed = millis();
			}

			// set how many milliseconds ago was the button released
			int duration = millis() - _notPressed;
			if( duration > _maxNoPress ) {
				// the user has stopped pressing the button for
				// the moment

				// send the number of presses to the caller
				output = _pressCount;
				// stop counting
				_counting = false;
				// reset presses
				_pressCount = 0;
				_notPressed = 0;
			} else {
				// let the caller know we're still counting presses
				output = -1;
			}
		}
		// button is no longer being pressed
		_inUse = false;
		return (int) output;
	}
}


//  END:  MultiPressButton class
// ==================================================================





// ==================================================================
// START: FixedTimeMultiPressButton class


FixedTimeMultiPressButton::FixedTimeMultiPressButton( byte pin ) : SimpleButton (pin) {
	// just do SimpleButton constructor
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
				_pressCount += 1;
				_inUse = true;
			} else {
				// We have reach the maximum time in which to count
				// presses. Send what we have to the caller and reset
				// everything.

				// send the number of presses to the caller
				output = _pressCount;
				// reset presses
				_pressCount = 0;
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
			output = _pressCount;
			// stop counting
			_counting = false;
			// reset presses
			_pressCount = 0;
		} else {
			// let the caller know we're still counting presses
			output = -1;
		}
		_inUse = false;
	}
	// button is no longer being pressed

	return output;
}


//  END:  FixedTimeMultiPressButton class
// ==================================================================
