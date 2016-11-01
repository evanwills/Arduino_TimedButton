#include "MultiModeButton.h"



MultiModeButton::MultiModeButton( byte pin ) : TimedButton (pin) {
}
MultiModeButton::MultiModeButton( byte pin , int pressIntervalTime ) : TimedButton (pin) {
	maxNoPress = pressIntervalTime;
}

//	unsigned int MultiModeButton::pressed() inherrited from TimedButton

int MultiModeButton::multiPress() {
	if( isPressed() == true ) {
		if ( multiPressInUse == false ) {
			// the button has just been pressed
			if ( counting == false ) {
				// the button has just been pressed for the first
				// time since it was reset. Lets remember that we're
				// now tracking how many presses
				counting = true;
			}
			// because this may be called many times during a single
			// press we only want to increment once per presss so
			// this is done within an IF statement

			// add another press to the record
			pressState += 1;
			multiPressInUse = true;
		}

		// let the caller know that the button is being pressed
		// but that we don't know what the total number of presses
		// is yet.
		return -1;
	} else {
		int output = 0;
		if ( counting == true ) {
			// we know we're counting now we'll check how long it was
			// since the button was released
			if ( multiPressInUse == true ) {
				// this is the first time we've noticed the button
				// has been released let's record that time
				notPressed = millis();
			}

			// set how many milliseconds ago was the button released
			int duration = millis() - notPressed;
			if( duration > maxNoPress ) {
				// the user has stopped pressing the button for
				// the moment

				// send the number of presses to the caller
				output = pressState;
				// stop counting
				counting = false;
				// reset presses
				pressState = 0;
				// reset the not pressed value
				notPressed = 0;
			} else {
				// let the caller know we're still counting presses
				output = -1;
			}
		}
		// button is no longer being pressed
		multiPressInUse = false;
		return output;
	}
}
