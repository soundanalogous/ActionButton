/*
 * ActionButton example
 * Jeff Hoefs
 * 11/3/11
 */

#include <ActionButton.h>

ActionButton btn1 = ActionButton(2, ActionButton::PULL_UP);

// button attached to pin A0 on an Arduino UNO (which is also digital pin 16)
ActionButton btn2 = ActionButton(16, ActionButton::PULL_DOWN);

void onPressed(ActionButton & btn) {
  Serial.print("\r\nbutton ");
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

void setup() {
  Serial.begin(57600);
  
  // example of using events
  btn1.attach(ActionButton::PRESSED, onPressed);
  btn1.attach(ActionButton::RELEASED, onReleased);
  btn1.attach(ActionButton::SUSTAINED, onSustainedPress);
  
  // set the sustained press interval to 2 seconds (default is 1 second)
  btn2.setSustainedInterval(2000);
  /*
  btn2.attach(ActionButton::PRESSED, onPressed);
  btn2.attach(ActionButton::RELEASED, onReleased);
  btn2.attach(ActionButton::SUSTAINED, onSustainedPress);
  */
}

void loop() {
  btn1.update();
  btn2.update();
  
  // example of using polling technique
  if (btn2.isPressed()) Serial.println("\r\nbuttonn 16 pressed");
  if (btn2.isReleased()) Serial.println("button 16 released");
  if (btn2.isSustained()) Serial.println("button 16 sustained");
}