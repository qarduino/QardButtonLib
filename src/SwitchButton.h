#ifndef MYX_BUTTONS_SWITCHBUTTON_H
#define MYX_BUTTONS_SWITCHBUTTON_H

#include "Arduino.h"
#define MBTN_SWITCH_MODE_ON 1
#define MBTN_SWITCH_MODE_OFF 2

class SwitchButton {
  public:
    int value = 0; // current value
    bool isChanged = false; // Is val chagned on current handle tick
    
    SwitchButton(int pin, int switchMode, int debounceTime){
      this->pin = pin;
      this->switchMode = switchMode;
      this->debounce = debounceTime;
      pinMode(pin, INPUT);
    }
    SwitchButton(int pin, int switchMode){
      this->pin = pin;
      this->switchMode = switchMode;
      pinMode(pin, INPUT);
    }
    SwitchButton(int pin){
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

        int state = readedVal;
        int prevState = this->prevState;
        int mustBeState = HIGH; int mustBePrevState = LOW;
        if (this->switchMode == MBTN_SWITCH_MODE_OFF) {
          mustBeState = LOW; mustBePrevState = HIGH; 
        }
        if (state == mustBeState && prevState == mustBePrevState) {
            this->isChanged = true; 
            if (this->value == LOW) this->value = HIGH;
            else this->value = LOW;
        }
        this->prevState = state;
    }
  private:
    // Settings
    int pin;  
    int switchMode = MBTN_SWITCH_MODE_ON;
    int debounce = 50;

    // Vars for debounce
    int prevReadedVal = 0;
    long lastChangeMillis = 0;

    // Vars for switch
    int prevState = 0;
};


#endif
