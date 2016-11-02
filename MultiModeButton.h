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
#include "MultiPressButton.h"




class MultiModeButton : public TimedButton , public MultiPressButton {

	public:
		MultiModeButton( byte pin );
		MultiModeButton( byte pin , int _maxNoPressInterval );
		/**
		 * Implements TimedButton version of getState()
		 * reads the button's state then returns how long the button
		 * was pressed for (or -1 if the button is currently being
		 * pressed)
		 */
		int getStatus();

		/**
		 * Implements MultiPressButton version of getState()
		 * reads the button's state then returns the number of
		 * times the buttons was pressed or -1 if the button is
		 * currently being pressed.
		 *
		 * functionality copied directly from MultiPressButton::pressed()
		 * The only difference is the variable _TimedBtnInUse is renamed to
		 * multiPressInUse
		 */
		int multiPress();


};

#endif
