/**
 * ToggleButton can be used to manage which index of an Array should
 * be used at any given time or to make a button behave like a switch
 *
 * Created by Evan Wills 2016-10-16
 * Released under GPL2 Licence
 */


#ifndef TimedButton_h
#define TimedButton_h


#include <Arduino.h>
#include <stdlib.h>
#include "SimpleButton.h"


class ToggleButton : public SimpleButton {

	public:
		ToggleButton( byte pin);
		ToggleButton( byte pin , byte limit);
		/**
		 * reads the button's state then returns the number of
		 * times the buttons was pressed.
		 */
		int getState();

	private:

		/**
		 * start the time in milliseconds (from when the Arduino was
		 * turned on) the button was pressed.
		 */
		bool inUse = false;

		/**
		 * How many times the button has been pressed since it last
		 * reset itself
		 */

		byte pressState = 0;
		/**
		 * the maximum number of milliseconds after the button was
		 * released that indicates no more pressing has finished.
		 */
		byte max = 1;
};

#endif
