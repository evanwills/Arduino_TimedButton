/**
 * ITimedButton is useful for when you want to do time
 * based things with a button
 * e.g. a short click of the button (say, less than 1 second) is used
 *		for modifying settings but a long click is used for resetting
 *		to defaults
 *	or	multiple presses within a given time.
 */
public class ITimedButton {

	public:
		/**
		 * If button is pressed, starts counting the number of
		 * milliseconds since start and returns true. If not,
		 * resets the timer and returns false.
		 */
		virtual bool readButton();

		/**
		 * reads the button's state then returns the number of
		 * milliseconds the buttons was pressed for.
		 */
		virtual int pressed();

	private:
		/*
		 * btnPin the Arduino Mega pin number used by the button
		 */
		byte btnPin = 0;
}


public class DumbButton : ITimedButton {

	public:
		CleverButton( byte pin );
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
		int pressed();

		void makePinModePullup();
}


public class TimedButton : DumbButton {

	public:
		CleverButton(byte pin);
		/**
		 * reads the button's state then returns the number of
		 * milliseconds the buttons was pressed for.
		 */
		int pressed();

	private:

		/**
		 * start the time in milliseconds (from when the Arduino was
		 * turned on) the button was pressed.
		 */
		unsigned long start = 0;
		unsigned long pressDuration = 0;
		bool inUse = false;
}



public class MultiPressButton : DumbButton {

	public:
		MultiPressButton( byte pin , int maxNoPressInterval = 500 );
		/**
		 * reads the button's state then returns the number of
		 * times the buttons was pressed.
		 */
		int presed();

	private:

		/**
		 * start the time in milliseconds (from when the Arduino was
		 * turned on) the button was pressed.
		 */
		unsigned long notPressed = 0;
		bool inUse = false;
		bool counting = false;
		byte presses = 0;
		/**
		 * the maximum number of milliseconds after the button was
		 * released that indicates no more pressing has finished.
		 */
		int maxNoPress = 500;
}



public class FixedTimeMultiPressButton : DumbButton {

	public:
		FixedTimeMultiPressButton( byte pin , int pressIntervalTime = 1000 );
		/**
		 * reads the button's state then returns the number of
		 * times the buttons was pressed.
		 */
		int presed();

	private:

		/**
		 * start the time in milliseconds (from when the Arduino was
		 * turned on) the button was pressed.
		 */
		unsigned long start = 0;
		int pressInterval = 0;
		bool inUse = false;
		bool counting = false;
		byte presses = 0;
		/**
		 * the maximum number of milliseconds after the button was
		 * released that indicates no more pressing has finished.
		 */
		int TimeLimit = 1000;
}



public class MultiModeButton : TimedButton {

	public:
		MultiModeButton( byte pin , int maxNoPressInterval = 500 );
		/**
		 * reads the button's state then returns the number of
		 * times the buttons was pressed.
		 */
		int pressed();

		/**
		 * reads the button's state then returns the number of
		 * times the buttons was pressed or -1 if the button is
		 * currently being pressed.
		 *
		 * functionality copied directly from MultiPressButton::pressed()
		 * The only difference is the variable inUse is renamed to
		 * multiPressInUse
		 */
		int multiPress();

		// int MultiModeButton::pressed() inherrited from TimedButton

	private:

		/**
		 * start the time in milliseconds (from when the Arduino was
		 * turned on) the button was pressed.
		 */
		unsigned long notPressed = 0;
		bool multiPressInUse = false;
		bool counting = false;
		byte presses = 0;
		/**
		 * the maximum number of milliseconds after the button was
		 * released that indicates no more pressing has finished.
		 */
		int maxNoPress = 500;
}
