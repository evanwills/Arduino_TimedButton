/**
 * FlexibleButtons.h - base class for a set of objects that allows you to
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






// ==================================================================
// START: FlexibleButton interface


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


//  END:  FlexibleButton interface
// ==================================================================



// ==================================================================
// START: SimpleButton class


class SimpleButton : public FlexibleButtonInterface {

	public:
		SimpleButton(byte pin, bool pullup = false);

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


//  END:  SimpleButton class
// ==================================================================



// ==================================================================
// START: ToggleButton class


class ToggleButton : public SimpleButton {

	public:
		ToggleButton(byte pin, bool pullup = false, byte limit = 1);

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
		bool _inUse = false;

		/**
		 * How many times the button has been pressed since it last
		 * reset itself
		 */

		byte _pressCount = 0;
		/**
		 * the maximum number of milliseconds after the button was
		 * released that indicates no more pressing has finished.
		 */
		byte _maxPresses = 1;
};


//  END:  ToggleButton class
// ==================================================================



// ==================================================================
// START: TimedButton class


class TimedButton : public SimpleButton {

	public:
		TimedButton(byte pin, bool pullup = false);
		int getState();

	private:

		/**
		 * start the time in milliseconds (from when the Arduino was
		 * turned on) the button was pressed.
		 */
		unsigned long _start = 0;
		unsigned long _pressDuration = 0;
		bool _inUse = false;
};



//  END:  TimedButton class
// ==================================================================



// ==================================================================
// START: MultiPressButton class


class MultiPressButton : public SimpleButton {

	public:
		MultiPressButton( byte pin, bool pullup = false, int maxNoPressInterval = 250 );
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
		byte _pressCount = 0;
		/**
		 * the maximum number of milliseconds after the button was
		 * released that indicates no more pressing has finished.
		 */
		int _maxNoPress = 250;
};


//  END:  MultiPressButton class
// ==================================================================



// ==================================================================
// START: FixedTimeMultiPressButton class


class FixedTimeMultiPressButton : public SimpleButton {

	public:
		FixedTimeMultiPressButton( byte pin, bool pullup = false, int pressIntervalTime = 1000 );
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
		unsigned long _start = 0;
		int _pressInterval = 0;
		bool _inUse = false;
		bool _counting = false;
		byte _pressCount = 0;
		/**
		 * The time from when the button was first pressed to when it
		 * stops counting presses
		 */
		int _timeLimit = 500;
};


//  END:  FixedTimeMultiPressButton class
// ==================================================================





#endif
