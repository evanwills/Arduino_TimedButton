# FlexibleButtons

`FlexibleButtons` is a collection of classes/objects to make doing stuff with buttons easier

The classes are:
*	`SimpleButton`
*	`ToggleButton`
*	`TimedButton`
*	`MultiPressButton`
*	`FixedTimeMultiPressButton`

## Methods:

### `bool isPressed()`
Returns `TRUE` if the button is currently being pressed. Or `FALSE` otherwise.

### `int getState()`
Returns an signed integer.
*	If nothing is happening with the button it returns `0`;
*	If the button is being pressed and it doesn't know the final output yet it ruturns `-1`;
*	If it knows the output it will return either the number of presses or the number of milliseconds the button was pressed for, depending on the class.

## Sub classes:

### `SimpleButton(byte pin, bool pullup = false)`
Does nothing interesting except providing a simple interface for using buttons which all the following classes inherit.

`byte pin` The number of the pin the button is plugged into.

`bool pullup = false` If the button doesn't have a resistor somewhere in the circuit, pullup needs to be true to make the input mode `INPUT_PULLUP`

### `ToggleButton(byte pin, bool pullup = false, byte limit = 1)`
Makes a button work like a switch. This can be useful for toggling between items in an array. Or just switching something on or off

(see `SimpleButton` above for info on __`pin`__ and __`pullup`__ parameters)

`byte limit = 1` by default the ToggleButton toggles between `1` and `0` by setting a limit, you can make the button toggle between `0` and up to `254`

### `TimedButton(byte pin, bool pullup = false)`

Makes the duration of a button press knowable. useful if you want to do different things with a button depending on how long it was pressed

(see `SimpleButton` above for info on __`pin`__ and __`pullup`__ parameters)


### `MultiPressButton(byte pin, bool pullup = false, int maxNoPressInterval = 250)`

Tells you how many times a button has been pressed where the interval between presses does not excede a maximum number of milliseconds (Default is 250 milliseconds)

(see `SimpleButton` above for info on __`pin`__ and __`pullup`__ parameters)

`int maxNoPressInterval = 250` the maximum number of milliseconds after the button was released that indicates no more pressing has finished.

__NOTE:__ The higher the `maxNoPressInterval` value the more lag between when you finish pressing the button and when the button can give it's state - in this case the number of presses.


### `FixedTimeMultiPressButton(pin, pullup, pressIntervalTime)`

How many times a button has been pressed within a given time (useful for doing the equivalent of double or tripple click on a computer)

(see `SimpleButton` above for info on __`pin`__ and __`pullup`__ parameters)

`int pressIntervalTime = 500` The time from when the button was first pressed to when it stops counting presses


---------------

## Using Multiple Modes on a single physical button

There are times where you might have a single physical button but in different contexts you want it to behave in different ways.

e.g. You have one button:
*	in normal mode, it needs to register when there is a 1 second long press which moves program into config mode.
*	In config mode, the button needs to toggle between 5 different states.
*	a fast double click ends the config and stores all the changes.

In this scenario you would create three separate button objects

``` C++
SimpleButton::makePinModeAlwaysPullup();

TimedButton configMode( 23 );
ToggleButton configInput( 23 , 5 );
MultiPressButton configEnd( 23 );
bool action = true;

void loop() {
	if( configMode.getState() > 1000 || action == false ) {
		action = false;

		int inputMode = configInput.getState();
		if( inputMode == 0 ) {
			getValueForInput_0();
		} else if( inputMode == 1 ) {
			getValueForInput_1();
		} else if( inputMode == 2 ) {
			getValueForInput_2();
		} else if( inputMode == 3 ) {
			getValueForInput_3();
		} else if( inputMode == 4 ) {
			getValueForInput_4();
		}

		if( configEnd.getState() == 2 ) {
			applyChanges();
			action = true;
		}
	}
}
```
