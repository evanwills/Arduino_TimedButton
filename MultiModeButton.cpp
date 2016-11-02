#include "MultiModeButton.h"



MultiModeButton::MultiModeButton( byte pin ) : TimedButton (pin) {
}
MultiModeButton::MultiModeButton( byte pin , int pressIntervalTime ) : MultiPressButton( pin , maxNoPressInterval ) {
}

// int MultiModeButton::getState() : TimedButton.getState() : TimedButton.getState() {
int MultiModeButton::getState() {
	 return TimedButton.getState();
}
//	unsigned int MultiModeButton::pressed() inherrited from TimedButton

// int MultiModeButton::multiPress() : MultiPressButton.getState() {
int MultiModeButton::multiPress() {
	return TimedButton.getState();
}
