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


#ifndef TimedButton_h
#define TimedButton_h


#include <Arduino.h>
#include <stdlib.h>
#include "SimpleButton.h"


class TimedButton : public SimpleButton {

	public:
		TimedButton( byte pin );
		int getState();

	private:

		/**
		 * start the time in milliseconds (from when the Arduino was
		 * turned on) the button was pressed.
		 */
		unsigned long start = 0;
		unsigned long pressDuration = 0;
		bool inUse = false;
};


#endif
