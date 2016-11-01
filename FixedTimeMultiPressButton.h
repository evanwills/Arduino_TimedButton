/**
 * FixedTimeMultiPressButton.h - counts the number of button presses
 * within a given time (by default 1 second)
 *
 * Useful for changing behaviour on fast double or tripple click
 *
 * Created by Evan Wills 2016-10-16
 * Released under GPL2 Licence
 */



#ifndef FixedTimeMultiPressButton_h
#define FixedTimeMultiPressButton_h

#include <Arduino.h>
#include <stdlib.h>
#include "SimpleButton.h"



class FixedTimeMultiPressButton : public SimpleButton {

	public:
		FixedTimeMultiPressButton( byte pin );
		FixedTimeMultiPressButton( byte pin , int pressIntervalTime );
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
		unsigned long start = 0;
		int pressInterval = 0;
		bool inUse = false;
		bool counting = false;
		byte pressState = 0;
		/**
		 * the maximum number of milliseconds after the button was
		 * released that indicates no more pressing has finished.
		 */
		int TimeLimit = 1000;
};



#endif
