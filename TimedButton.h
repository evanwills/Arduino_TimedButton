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


// ========================================================
// START: ITimedButton interface
//
// class ITimedButton {
//
// 	public:
// 		/**
// 		 * If button is pressed, starts counting the number of
// 		 * milliseconds since start and returns true. If not,
// 		 * resets the timer and returns false.
// 		 */
// 		virtual bool readButton();
//
// 		/**
// 		 * reads the button's state then returns the number of
// 		 * milliseconds the buttons was pressed for.
// 		 */
// 		virtual unsigned int pressed();
// };


//  END:  ITimedButton interface
// ========================================================
// START: (basic) DumbButton class


class DumbButton { // : public ITimedButton {

	public:
		DumbButton( byte pin );
		/**
		 * If button is pressed, starts counting the number of
		 * milliseconds since start and returns true. If not,
		 * resets the timer and returns false.
		 */
		bool readButton();

		/**
		 * reads the button's state then returns zero if the button
		 * is not pressed and one if it is.
		 */
		unsigned int pressed();

		void makePinModePullup();

	protected:
		/*
		 * btnPin the Arduino Mega pin number used by the button
		 */
		byte btnPin = 0;
};


//  END:  (basic DumbButton class
// ========================================================
// START: TimedButton class


// class TimedButton : public DumbButton {
//
// 	public:
//
// //		TimedButton(byte pin); // inherrited from DumbButton
// 		/**
// 		 * reads the button's state then returns the number of
// 		 * milliseconds the buttons was pressed for.
// 		 */
// 		unsigned int pressed();
//
// 	private:
//
// 		/**
// 		 * start the time in milliseconds (from when the Arduino was
// 		 * turned on) the button was pressed.
// 		 */
// 		unsigned long start = 0;
// 		unsigned long pressDuration = 0;
// 		bool inUse = false;
// };


//  END:  TimedButton class
// ========================================================
// START: MultiPressButton class


// class MultiPressButton : public DumbButton {
//
// 	public:
// 		MultiPressButton( byte pin , int maxNoPressInterval = 500 );
// 		/**
// 		 * reads the button's state then returns the number of
// 		 * times the buttons was pressed.
// 		 */
// 		unsigned int pressed();
//
// 	private:
//
// 		/**
// 		 * start the time in milliseconds (from when the Arduino was
// 		 * turned on) the button was pressed.
// 		 */
// 		unsigned long notPressed = 0;
// 		bool inUse = false;
// 		bool counting = false;
// 		byte presses = 0;
// 		/**
// 		 * the maximum number of milliseconds after the button was
// 		 * released that indicates no more pressing has finished.
// 		 */
// 		int maxNoPress = 500;
// };


//  END:  MultiPressButton class
// ========================================================
// START: ToggleButton class

// ToggleButton can be used to manage which index of an Array should
// be used at any given time

// class ToggleButton : public DumbButton {
//
// 	public:
// 		ToggleButton( byte pin , byte limit = 1 );
// 		/**
// 		 * reads the button's state then returns the number of
// 		 * times the buttons was pressed.
// 		 */
// 		unsigned int pressed();
//
// 	private:
//
// 		/**
// 		 * start the time in milliseconds (from when the Arduino was
// 		 * turned on) the button was pressed.
// 		 */
// 		bool inUse = false;
// 		byte presses = 0;
// 		/**
// 		 * the maximum number of milliseconds after the button was
// 		 * released that indicates no more pressing has finished.
// 		 */
// 		byte max = 1;
// };


//  END:  ToggleButton class
// ========================================================
// START: FixedTimeMultiPressButton class


// class FixedTimeMultiPressButton : public DumbButton {
//
// 	public:
// 		FixedTimeMultiPressButton( byte pin , int pressIntervalTime = 1000 );
// 		/**
// 		 * reads the button's state then returns the number of
// 		 * times the buttons was pressed.
// 		 */
// 		unsigned int pressed();
//
// 	private:
//
// 		/**
// 		 * start the time in milliseconds (from when the Arduino was
// 		 * turned on) the button was pressed.
// 		 */
// 		unsigned long start = 0;
// 		int pressInterval = 0;
// 		bool inUse = false;
// 		bool counting = false;
// 		byte presses = 0;
// 		/**
// 		 * the maximum number of milliseconds after the button was
// 		 * released that indicates no more pressing has finished.
// 		 */
// 		int TimeLimit = 1000;
// };


//  END:  FixedTimeMultiPressButton class
// ========================================================
// START: MultiModeButton class


// MultiModeButton alows for both long press and multi-press button
// presses to be used on a single button
// class MultiModeButton : public TimedButton {

// 	public:
// 		MultiModeButton( byte pin , int maxNoPressInterval = 500 );
// 		/**
// 		 * reads the button's state then returns how long the button
// 		 * was pressed for (or -1 if the button is currently being
// 		 * pressed)
// 		 */
// 		unsigned int pressed();
//
// 		/**
// 		 * reads the button's state then returns the number of
// 		 * times the buttons was pressed or -1 if the button is
// 		 * currently being pressed.
// 		 *
// 		 * functionality copied directly from MultiPressButton::pressed()
// 		 * The only difference is the variable inUse is renamed to
// 		 * multiPressInUse
// 		 */
// 		int multiPress();
//
// 		// int MultiModeButton::pressed() inherrited from TimedButton
//
// 	private:
//
// 		/**
// 		 * start the time in milliseconds (from when the Arduino was
// 		 * turned on) the button was pressed.
// 		 */
// 		unsigned long notPressed = 0;
// 		bool multiPressInUse = false;
// 		bool counting = false;
// 		byte presses = 0;
// 		/**
// 		 * the maximum number of milliseconds after the button was
// 		 * released that indicates no more pressing has finished.
// 		 */
// 		int maxNoPress = 500;
// };

#endif
