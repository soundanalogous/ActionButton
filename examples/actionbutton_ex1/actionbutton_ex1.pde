/*
 * ActionButton example
 * Jeff Hoefs
 * 11/3/11
 *
 * This example demonstrates a few diffrent ways to use the ActionButton
 * library. You can attach event listeners, or poll for the changes in 
 * button state.
 *
 * Note that you must specify the button mode as the 2nd paramter of the
 * ActionButton constructor (PULL_UP, PULL_UP_INTERNAL, PULL_DOWN)
 * according to how you have wired the button to your Arduino.
 */

#include <ActionButton.h>

// wire button to pin 2 in pull-up configuration
ActionButton btn1 = ActionButton(2, ActionButton::PULL_UP);

// wire button to pin 4 in pull-down configuration
ActionButton btn2 = ActionButton(4, ActionButton::PULL_DOWN);

// button attached to pin A0 on an Arduino UNO (which is also digital pin 16)
// use internal pull-up (no external resistor required)
ActionButton btn3 = ActionButton(16, ActionButton::PULL_UP_INTERNAL);

void onPressed(ActionButton & btn) {
  Serial.print("button ");
  Serial.print(btn.getPin());
  Serial.println(" pressed"); 
}

void onReleased(ActionButton & btn) {
  Serial.print("button ");
  Serial.print(btn.getPin());
  Serial.println(" released");   
}

void onSustainedPress(ActionButton & btn) {
  Serial.print("button ");
  Serial.print(btn.getPin());
  Serial.println(" sustained"); 
}

// a change event is fired on each transition between pressed and
// released states
void onChange(ActionButton & btn) {
  String state = "";
  
  switch (btn.getState()) {
  	case ActionButton::PRESSED:
  	  state = " pressed";
  	  break;
  	case ActionButton::RELEASED:
  	  state = " released";
  	  break;
  }

  Serial.print("button ");
  Serial.print(btn.getPin());
  Serial.println(state);
}

void setup() {
  Serial.begin(57600);
  
  // example of using events
  btn1.attach(ActionButton::PRESSED, onPressed);
  btn1.attach(ActionButton::RELEASED, onReleased);
  btn1.attach(ActionButton::SUSTAINED, onSustainedPress);
  
  btn2.attach(ActionButton::CHANGED, onChange);
  
  // set the sustained press interval to 2 seconds (default is 1 second)
  btn3.setSustainedInterval(2000);
}

void loop() {
  btn1.update();
  btn2.update();
  btn3.update();
  
  // example of using polling technique
  if (btn3.isPressed()) Serial.println("buttonn 16 pressed");
  if (btn3.isReleased()) Serial.println("button 16 released");
  if (btn3.isSustained()) Serial.println("button 16 sustained");
}