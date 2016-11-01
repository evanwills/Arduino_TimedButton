#include "TimedButton.h"

SimpleButton simpleButton(53);
TimedButton timedButton(51);

void setup() {
  // put your setup code here, to run once:
  simpleButton.makePinModePullup();
  timedButton.makePinModePullup();
  pinMode(13, OUTPUT);
}

void loop() {
/*
  // put your main code here, to run repeatedly:
  if ( simpleButton.pressed() ) {
	  	digitalWrite(13, HIGH);
	} else {
		digitalWrite(13, LOW);
	}
*/

if ( timedButton.readButton() > 1000 ) {
	  	digitalWrite(13, HIGH);
	  	delay(2000);
	} else {
		digitalWrite(13, LOW);
	}

}
