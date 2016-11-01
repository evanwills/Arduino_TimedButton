/**
 * TimedButton.h - useful for when you want to do time based things
 * with a button
 * e.g. a short click of the button (say, less than 1 second) is used
 *		for modifying settings but a long click is used for resetting
 *		to defaults
 *	or	multiple presses within a given time. Single click changes interface to modify setting for current mode. Double click changes modes. Tripple click
 *
 * Created by Evan Wills 2016-10-16
 * Released under GPL2 Licence
 */


#ifndef SimpleButton_h
#define SimpleButton_h

#include <Arduino.h>
#include <stdlib.h>


class SimpleButton { // : public ITimedButton {

	public:
		SimpleButton( byte pin );
		/**
		 * If button is pressed, starts counting the number of
		 * milliseconds since start and returns true. If not,
		 * resets the timer and returns false.
		 */
		bool pressed();

		/**
		 * reads the button's state then returns zero if the button
		 * is not pressed and one if it is.
		 */
		unsigned int readButton();

		/**
		 * Sometimes it's necessary to make the input mode PULLUP.
		 *
		 * Used for any buttont that doesn't include a pullup resistor.
		 * Includes rotaryEncoder and 8 button keypad
		 * 
		 */
		void makePinModePullup();

	protected:
		/*
		 * btnPin the Arduino Mega pin number used by the button
		 */
		byte btnPin = 0;
};

#endif
