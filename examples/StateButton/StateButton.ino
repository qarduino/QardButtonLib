#include "Arduino.h"
#include <StateButton.h>

const int buttonPin = 4;      // D2
StateButton* button = new StateButton(buttonPin);

void setup() {
  Serial.begin(115200);
}

void loop() {
  button->handle();
  if (button->isChanged) {
	  Serial.print("Button value: ");
	  Serial.println(button->value);
  }
}