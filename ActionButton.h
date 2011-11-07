// Jeff Hoefs
// ActionButton.h
//
// update 11/3/11
// 1/20/08

#ifndef ActionButton_h
#define ActionButton_h

// updated to be compatible with Arduino 1.0
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"	// for digitalRead, digitalWrite, etc
#else
#include "WProgram.h"
#endif

#define DEBOUNCE_INTERVAL	10    // set default debounce time to 10ms
#define SUSTAINED_INTERVAL	1000  // set default sustained time to 1000ms

class ActionButton;
extern "C" {
// callback function types
    typedef void (*buttonEventHandler)(ActionButton & btn);
}

class ActionButton
{

  public:
  
	enum {
		RELEASED,
		PRESSED,
		SUSTAINED,
		CHANGED,		
		PULL_UP,
		PULL_DOWN,
		PULL_UP_INTERNAL
	};
	
	ActionButton(byte pin, boolean mode);
	void update(); 
	void setDebounceInterval(byte interval);
	void setSustainedInterval(unsigned int interval);
	byte getDebounceInterval();
	unsigned int getSustainedInterval();
	byte getPin();
	byte getState();

	bool isPressed();
	bool isReleased();
	bool isSustained();
		
	void attach(byte eventType, buttonEventHandler newFunction);
	void detach(byte eventType);
	
  private:	 
	bool lastState; 
	bool dispatched;
	unsigned long buttonTimePressed;
	unsigned int sustainedInterval; 	
	byte buttonPin;
	byte buttonMode;
	byte debounceInterval;
	byte buttonState;

	// Button Events 
	bool buttonPressed; 
	bool buttonHeld; 
	bool buttonReleased;
	
	// callback functions
	buttonEventHandler onPressCallback;
	buttonEventHandler onReleaseCallback;
	buttonEventHandler onSustainedPressCallback;
	buttonEventHandler onChangeCallback;
};

#endif
