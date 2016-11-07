#include "ToggleButton.h"


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
			Serial.print(_pressCount);

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


