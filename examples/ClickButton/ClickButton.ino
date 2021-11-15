#include "Arduino.h"
#include <ClickButton.h>

const int buttonPin = 4;      // D2
ClickButton* button = new ClickButton(buttonPin);

void setup() {
  Serial.begin(115200);
}

void loop() {
  button->handle();
  if (button->isChange) {
    if (button->clickType == MBTN_CLICK_SINGLE) {
      Serial.println("Click SINGLE");
    } else if (button->clickType == MBTN_CLICK_DOUBLE) {
      Serial.println("Click DOUBLE");
    } else {
      Serial.println("Click LONG");
    }
  }
}
