#include "Arduino.h"
#include <SwitchButton.h>

const int buttonPin = 4;      // D2
SwitchButton* button = new SwitchButton(buttonPin);

void setup() {
  Serial.begin(115200);
}

void loop() {
  button->handle();
  if (button->isChanged) {
    if (button->value == HIGH) {
		  Serial.println("Switch is ON");
    } else {
		  Serial.println("Switch is OFF");
	  }
  }
}