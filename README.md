# FlexibleButtons

`FlexibleButtons` is a collection of classes/objects to make doing stuff with buttons easier

The classes are:
*	`SimpleButton` does nothing interesting except providing a simple interface for using buttons which all the following classes inherit.
*	`ToggleButton` makes a button work like a switch. This can be useful for toggling between items in an array. Or just switching something on or off (__*CURRENTLY NOT WORKING*__)
*	`TimedButton` makes the duration of a button press knowable useful if you want to do different things with a button depending on how long it was pressed
*	`MultiPressButton` tells you how many times a button has been pressed where the interval between presses does not excede a maximum number of milliseconds (Default is 500 milliseconds)
*	`FixedTimeMultiPressButton` how many times a button has been pressed within a given time (useful for doing the equivalent of double or tripple click on a computer) (__*CURRENTLY NOT WORKING*__)
*	`MultiModeButton` combines `TimedButton` and `MultiPressButton` in one object (has an extra multiPress() method to get number of presses)

## Methods:

### `bool isPressed()`
Returns `TRUE` if the button is currently being pressed. Or `FALSE` otherwise.

### `int getState()`
Returns an signed integer.
*	If nothing is happening with the button it returns `0`;
*	If the button is being pressed and it doesn't know the final output yet it ruturns `-1`;
*	If it knows the output it will return either the number of presses or the number of milliseconds the button was pressed for, depending on the class.

### `void makePinModePullup()`
Simply changes the mode of the button from INPUT to INPUT_PULLUP. (Useful if you don't want to have resisters on every button.)

__NOTE:__ `makePinModePullup()` should only be called once, during setup.
