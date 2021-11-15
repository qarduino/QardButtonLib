#ifndef MYX_BUTTONS_CLICKBUTTON_H
#define MYX_BUTTONS_CLICKBUTTON_H

#include "Arduino.h"

#define MBTN_CLICK_SINGLE 1
#define MBTN_CLICK_DOUBLE 2
#define MBTN_CLICK_LONG 3

#define MBTN_STATE_NO_CLICK 0
#define MBTN_STATE_LONG_CLICK 1
#define MBTN_STATE_SINGLE_CLICK 2


class ClickButton {
  public:
    bool isChanged = 0; // Is val chagned on current handle tick
    int clickType = 0;
    
    ClickButton(int pin, int lgTime, int dbTime, int debounceTime){
      this->pin = pin;
      this->debounce = debounceTime;
      this->lgTime = lgTime;
      this->dbTime = dbTime;
      pinMode(pin, INPUT);
    }
    ClickButton(int pin, int lgTime, int dbTime){
      this->pin = pin;
      this->lgTime = lgTime;
      this->dbTime = dbTime;
      pinMode(pin, INPUT);
    }
    ClickButton(int pin){
      this->pin = pin;
      pinMode(pin, INPUT);
    }
    
    void handle(){
        isChanged = false; 
        int readedVal = digitalRead(pin);
        int prevReadedVal = this->prevReadedVal;
        this->prevReadedVal = readedVal;
        if (readedVal != prevReadedVal) {
            this->lastChangeMillis = millis();
            return;
        }
        if (millis() - this->lastChangeMillis < this->debounce) return;
        
        
        int lastVal = this->lastValue;
        this->lastValue = readedVal;
        int state = this->state;
        int changeTime = this->changeTime;

        if (readedVal == HIGH) {
          if (lastVal == LOW) {
            this->changeTime = millis();
            if (state == MBTN_STATE_NO_CLICK) {
                this->state = MBTN_STATE_LONG_CLICK;
            }  
            return;
          }
          if (state == MBTN_STATE_LONG_CLICK && millis() - changeTime > this->lgTime) {
            click(MBTN_CLICK_LONG);
            return;  
          }
          if (state == MBTN_STATE_SINGLE_CLICK) {
            click(MBTN_CLICK_DOUBLE);
            return;  
          }
        } else {
          if (lastVal == HIGH) {
            this->changeTime = millis();
            if (state != MBTN_STATE_NO_CLICK) {
                this->state = MBTN_STATE_SINGLE_CLICK;
            }  
            return;
          }
          if (state == MBTN_STATE_SINGLE_CLICK && millis() - changeTime > this->dbTime) {
            click(MBTN_CLICK_SINGLE);
            return;  
          }
        }
    }
  private:
    // Settings
    int pin;  
    int debounce = 50;

    // Vars for debounce
    int prevReadedVal = 0;
    long lastChangeMillis = 0;

    // Vars for clicks
    int lgTime = 700;
    int dbTime = 150;
    int lastValue = 0;
    long changeTime = 0;
    int state = MBTN_STATE_NO_CLICK;

    // funcs
    void click(int type) {
      this->isChanged = true;
      this->clickType = type;
      this->state = MBTN_STATE_NO_CLICK;  
    }
};

#endif
