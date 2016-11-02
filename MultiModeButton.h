/**
 * MultiModeButton alows for both long press and multi-press button
 * presses to be used on a single button by using a different method
 * call for multi-press
 *
 * Created by Evan Wills 2016-10-16
 * Released under GPL2 Licence
 */


#ifndef MultiModeButton_h
#define MultiModeButton_h


#include <Arduino.h>
#include <stdlib.h>
#include "TimedButton.h"




class MultiModeButton : public TimedButton {

	public:
		MultiModeButton( byte pin );
		MultiModeButton( byte pin , int _maxNoPressInterval );
		/**
		 * reads the button's state then returns how long the button
		 * was pressed for (or -1 if the button is currently being
		 * pressed)
		 */
		unsigned int pressed();

		/**
		 * reads the button's state then returns the number of
		 * times the buttons was pressed or -1 if the button is
		 * currently being pressed.
		 *
		 * functionality copied directly from MultiPressButton::pressed()
		 * The only difference is the variable _inUse is renamed to
		 * multiPressInUse
		 */
		int multiPress();

		// int MultiModeButton::pressed() inherrited from TimedButton

	private:

		/**
		 * start the time in milliseconds (from when the Arduino was
		 * turned on) the button was pressed.
		 */
		unsigned long _notPressed = 0;
		bool _multiPressInUse = false;
		bool _counting = false;
		byte _pressState = 0;
		/**
		 * the maximum number of milliseconds after the button was
		 * released that indicates no more pressing has finished.
		 */
		int _maxNoPress = 500;
};

#endif
