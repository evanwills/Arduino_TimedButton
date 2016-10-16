#include RotaryEncoder.h

//		int clkPin;
//		int dtPin;
//		int btnPin;
//		int clk_value;
//		int dt_value;
//		long position;
//		int previous_clk_value;
//		int increment = 1;

//void rotaryEncoder::RotaryEncoder(int clockPin, int dataPin, int buttonPin ) {
//}
RotaryEncoder::RotaryEncoder( int clockPin , int dataPin , int defaultPos ) {
	clkPin = clockPin;
	dtPin = dataPin;
	position = defaultPos;

	pinMode(clkPin, INPUT); // clk
	pinMode(dtPin, INPUT); // dt
}


long RotaryEncoder::getPosition( bool doRead ) {
	clk_value = digitalRead(clkPin);
	dt_value  = digitalRead(dtPin);

	if ((clk_value != previous_clk_value) && (clk_value != LOW)) {
		if (dt_value == LOW) {
			position += increment;
		} else {
			position -= increment;
		}
	}
	previous_clk_value = clk_value;
	return position;
}



BtnRotaryEncoder::BtnRotaryEncoder(  int clockPin , int dataPin , int defaultPos , ITimedButton button ) {
	clkPin = clockPin;
	dtPin = dataPin;
	position = defaultPos;
	btn = button;

	pinMode(clkPin, INPUT); // clk
	pinMode(dtPin, INPUT); // dt
}


bool BtnRotaryEncoder::readButton() {
	return btn->readButton();
}

int BtnRotaryEncoder::pressed() {
	return btn->pressed();
}
