#ifndef MYX_BUTTONS_STATEBUTTON_H
#define MYX_BUTTONS_STATEBUTTON_H

#include "Arduino.h"

class StateButton {
  public:
    int value = 0; // current value
    bool isChanged = 0; // Is val chagned on current handle tick
    
    StateButton(int pin, int debounceTime){
      this->pin = pin;
      this->debounce = debounceTime;
      pinMode(pin, INPUT);
    }
    StateButton(int pin){
      this->pin = pin;
      pinMode(pin, INPUT);
    }
    
    void handle(){
        this->isChanged = false; 
        int readedVal = digitalRead(pin);
        int prevReadedVal = this->prevReadedVal;
        this->prevReadedVal = readedVal;
        if (readedVal != prevReadedVal) {
            this->lastChangeMillis = millis();
            return;
        }
        if (millis() - this->lastChangeMillis < this->debounce) return;

        if (this->value != readedVal) this->isChanged = true; 
        this->value = readedVal;
    }
  private:
    // Settings
    int pin;  
    int debounce = 50;

    // Vars for debounce
    int prevReadedVal = 0;
    long lastChangeMillis = 0;
};

#endif
