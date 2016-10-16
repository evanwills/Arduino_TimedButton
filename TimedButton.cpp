#include TimedButton.h


DumbButton::DumbButton(byte pin) {
	btnPin = pin;
	pinMode(btnPin, INPUT);
}


bool DumbButton::readButton() {
	if (digitalRead(incrementBtn) == HIGH) {
		return true;
	} else {
		return false;
	}
}

int DumbButton::pressed() {
	if ( readButton() == true ) {
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
void DumbButton::makePinModePullup() {
	pinMode(btnPin, INPUT_PULLUP);
}


/**
 * How many seconds has the button been pressed for
 * If it's currently being pressed then it returns -1 to let caller
 * know that it can't give a final answer yet.
 * If it's not being pressed, then it returns zero.
 * If the button has just been released, it returns the number of
 * milliseconds the button was pressed for.
 */
int TimedButton::pressed() {
//	bool pressed = readButtion();

	if( readButtion() == true ) {
//	if( pressed == true ) {
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




MultiPressButton::MultiPressButton( byte pin , int maxNoPress ) {
	btnPin = pin;
	pinMode(btnPin, INPUT);
	noPress = maxNoPress;
}

int MultiPressButton::pressed() {
	if( readButtion() == true ) {
		if ( inUse == false ) {
			// the button has just been pressed
			if ( counting == false ) {
				// the button has just been pressed for the first
				// time since it was reset. Lets remember that we're
				// now tracking how many presses
				counting = true;
			}

			// because this may be called many times during a single
			// press we only want to increment once per presss so
			// this is done within this IF statement

			// add another press to the record
			presses = presses + 1;
			inUse = true;
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
			if ( inUse == true ) {
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
				output = presses;
				// stop counting
				counting = false;
				// reset presses
				presses = 0;
				notPressed = 0;
			} else {
				// let the caller know we're still counting presses
				output = -1;
			}
		}
		// button is no longer being pressed
		inUse = false;
		return output;
	}
}




FixedTimeMultiPressButton::FixedTimeMultiPressButton( byte pin , int pressIntervalTime ) {
	btnPin = pin;
	pinMode(btnPin, INPUT);
	pressInterval = pressIntervalTime;
}

int FixedTimeMultiPressButton::pressed() {
	int output = 0;
	// how long has it been since we started
	int duration;
	bool ended = true;

	if( readButtion() == true ) {
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
				presses = presses + 1;
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
			output = presses;
			// stop counting
			counting = false;
			// reset presses
			presses = 0;
		} else {
			// let the caller know we're still counting presses
			output = -1;
		}
		inUse = false;
	}
	// button is no longer being pressed

	return output;
}





MultiModeButton::MultiModeButton( byte pin , int pressIntervalTime ) {
	btnPin = pin;
	pinMode(btnPin, INPUT);
	noPress = maxNoPress;
}

// int MultiModeButton::pressed() inherrited from TimedButton

int MultiModeButton::multiPress() {
	if( readButtion() == true ) {
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
			presses = presses + 1;
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
				output = presses;
				// stop counting
				counting = false;
				// reset presses
				presses = 0;
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