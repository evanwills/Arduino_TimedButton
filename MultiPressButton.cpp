#include "MultiPressButton.h"


MultiPressButton::MultiPressButton( byte pin ) : SimpleButton (pin) {
	// don't do anything here
}
MultiPressButton::MultiPressButton( byte pin , int maxNoPressInterval )  : SimpleButton (pin) {
	_maxNoPress = maxNoPressInterval;
}

int MultiPressButton::getState() {
	if( isPressed() == true ) {
		if ( _MultiPressBtnInUse == false ) {
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
			_pressState += 1;
			_MultiPressBtnInUse = true;
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
			if ( _MultiPressBtnInUse == true ) {
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
				output = _pressState;
				// stop counting
				_counting = false;
				// reset presses
				_pressState = 0;
				_notPressed = 0;
			} else {
				// let the caller know we're still counting presses
				output = -1;
			}
		}
		// button is no longer being pressed
		_MultiPressBtnInUse = false;
		return (int) output;
	}
}


