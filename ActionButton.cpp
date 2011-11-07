// Jeff Hoefs
// ActionButton.cpp
//
// 11/3/11
// 1/20/08

#include "ActionButton.h"

ActionButton::ActionButton(byte pin, byte mode) {  
    buttonPin = pin;
    buttonMode = mode;
    
    // to do: update these to use bits
    buttonPressed = false;
    buttonReleased = false;
    buttonHeld = false;
    lastState = true; 
    dispatched = true;
    buttonState = ActionButton::RELEASED;

    buttonTimePressed = millis();

    // set default values
    sustainedInterval = SUSTAINED_INTERVAL; 
    debounceInterval = DEBOUNCE_INTERVAL;    
    
    pinMode(buttonPin, INPUT);

    if (buttonMode == ActionButton::PULL_UP_INTERNAL) {
      // enable internal pull-up resistor
      digitalWrite(buttonPin, HIGH);
    }
}

void ActionButton::attach(byte eventType,  buttonEventHandler newFunction) {
	switch(eventType) {
		case ActionButton::PRESSED:
			onPressCallback = newFunction;
			break;
		case ActionButton::RELEASED:
			onReleaseCallback = newFunction;
			break;
		case ActionButton::SUSTAINED:
			onSustainedPressCallback = newFunction;
			break;
    case ActionButton::CHANGED:
      onChangeCallback = newFunction;
      break;
	}
}

void ActionButton::detach(byte eventType) {
	switch(eventType) {
		case ActionButton::PRESSED:
			onPressCallback = NULL;
			break;
		case ActionButton::RELEASED:
			onReleaseCallback = NULL;
			break;
		case ActionButton::SUSTAINED:
			onSustainedPressCallback = NULL;
			break;
    case ActionButton::CHANGED:
      onChangeCallback = NULL;
      break;
	}
}

void ActionButton::update() { 
  bool reading;

  // reset button state on each loop
  // this way user can poll button state if they do not
  // want to use interrupts
  buttonPressed = false;
  buttonReleased = false;
  buttonHeld = false;
  
  // store current button state 
  reading = digitalRead(buttonPin);
  
  if (buttonMode == ActionButton::PULL_DOWN) reading = !reading;
  
  if (reading != lastState) {
     buttonTimePressed = millis();
     dispatched = false;
  } 
  // check for sustained press
  else {
  	if (buttonState == ActionButton::PRESSED || buttonState == ActionButton::SUSTAINED) {
  		if (millis() - buttonTimePressed >= sustainedInterval) {
  			buttonHeld = true;
        buttonState = ActionButton::SUSTAINED;
  			if (onSustainedPressCallback) (*onSustainedPressCallback)(*this);
	 		  buttonTimePressed = millis();
  		}
  	}
  }
  
  // if time specificed by debounceInterval has passed since last button state change
  if ((millis() - buttonTimePressed) >= debounceInterval) {
  	if (!reading && !dispatched) {
  	   buttonPressed = true;  // set state
  	   buttonReleased = false;
       buttonState = ActionButton::PRESSED;
  	   if (onPressCallback) (*onPressCallback)(*this);
       if (onChangeCallback) (*onChangeCallback)(*this);
  	   dispatched = true;
  	} else if (reading && !dispatched) {
  		buttonReleased = true;  // set state
  		buttonPressed = false;
  		buttonHeld = false;
      buttonState = ActionButton::RELEASED;
		  if (onReleaseCallback) (*onReleaseCallback)(*this);
      if (onChangeCallback) (*onChangeCallback)(*this);
		  dispatched = true;
  	}
  }
  
  lastState = reading;
  
}

byte ActionButton::getState() {
  return buttonState;
}

byte ActionButton::getPin() {
  return buttonPin;
}

bool ActionButton::isPressed() {
  return buttonPressed;
}

bool ActionButton::isReleased() {
  return buttonReleased;
}

bool ActionButton::isSustained() {
  return buttonHeld;
}

void ActionButton::setDebounceInterval(byte interval) {
  if (interval > 0 && interval < 256) {
    debounceInterval = interval;
  }
}

void ActionButton::setSustainedInterval(unsigned int interval) {
  if (interval > 0) {
    sustainedInterval = interval;
  }
}

byte ActionButton::getDebounceInterval() {
  return debounceInterval;
}

unsigned int ActionButton::getSustainedInterval() {
  return sustainedInterval;
}
