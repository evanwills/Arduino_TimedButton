#include TimedButton.h

public class IRotaryEncoder {

	public:
		virtual long getPosition( bool doRead = true );
}


public class RotaryEncoder : IRotaryEncoder {

	public:
		RotaryEncoder( int clockPin , int dataPin , int defaultPos = 0 );

		long getPosition( bool read = true );


	protected:
		int clkPin;
		int dtPin;
		int clk_value;
		int dt_value;
		long position;
		int previous_clk_value;
		int increment = 1;
}

// This BtnRotaryEncoder inherits from both rotaryEncoder and the
// interface for TimedButton, allowing it to be passed around as a
// button in its own right.
//
// BtnRotaryEncoder can be thought of as a decorator for TimedButtons
public class BtnRotaryEncoder : RotaryEncoder ITimedButton {

	public:
		BtnRotaryEncoder( int clockPin , int dataPin , int defaultPos , ITimedButton button );
		// these methods are required by the ITimedButton interface
		bool readButton();
		int pressed();

	protected:
		ITimedButton btn;

}
