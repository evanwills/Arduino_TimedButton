/**
 * SimpleButton.h - base class for a set of objects that allows you to
 * do useful time based things with a button.
 *
 * The SimpleButton class does very little but provide a standard
 * interface for other classes to inherit from
 *
 * e.g. a short click of the button (say, less than 1 second) is used
 *		for modifying settings but a long click is used for resetting
 *		to defaults
 *	or	multiple presses within a given time. Single click changes
 * interface to modify setting for current mode. Double click changes
 * modes. Tripple click
 *
 * Created by Evan Wills 2016-10-16
 * Released under GPL2 Licence
 */


#ifndef SimpleButton_h
#define SimpleButton_h

#include <Arduino.h>
#include <stdlib.h>

class FlexibleButtonInterface {
	public:
		/**
		 * If button is pressed, starts counting the number of
		 * milliseconds since start and returns true. If not,
		 * resets the timer and returns false.
		 */
		virtual bool isPressed();

		/**
		 * reads the button's state then returns zero if the button
		 * is not pressed and one if it is.
		 */
		virtual int getState();
};


class SimpleButton : public FlexibleButtonInterface {

	public:
		SimpleButton( byte pin );

		/**
		 * If button is pressed, starts counting the number of
		 * milliseconds since start and returns true. If not,
		 * resets the timer and returns false.
		 */
		bool isPressed();

		/**
		 * reads the button's state then returns zero if the button
		 * is not pressed and one if it is.
		 */
		int getState();

		/**
		 * Sometimes it's necessary to make the input mode PULLUP.
		 *
		 * Used for any buttont that doesn't include a pullup resistor.
		 * Includes rotaryEncoder and 8 button keypad
		 *
		 */
		void makePinModePullup();

		static void makePinModeAlwaysPullup();

	protected:
		/*
		 * _btnPin the Arduino Mega pin number used by the button
		 */
		byte _btnPin = 0;

		static bool _alwaysPullup;
};

#endif
