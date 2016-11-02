/**
 * MultiPressButton.h - Makes it simple to use multiple presses to do
 * different stuff with a single button
 *
 * e.g. multiple presses within a given time. Single click changes
 *		interface to modify setting for current mode. Double click
 *		changes modes. Tripple click
 *
 * Created by Evan Wills 2016-10-16
 * Released under GPL2 Licence
 */


#ifndef MultiPressButton_h
#define MultiPressButton_h


#include <Arduino.h>
#include <stdlib.h>
#include "SimpleButton.h"


class MultiPressButton : public SimpleButton {

	public:
		MultiPressButton( byte pin );
		MultiPressButton( byte pin , int maxNoPressInterval );
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
		unsigned long _notPressed = 0;
		bool _inUse = false;
		bool _counting = false;
		byte _pressState = 0;
		/**
		 * the maximum number of milliseconds after the button was
		 * released that indicates no more pressing has finished.
		 */
		int _maxNoPress = 500;
};

#endif
