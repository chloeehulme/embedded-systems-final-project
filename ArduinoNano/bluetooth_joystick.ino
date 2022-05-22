/**
   Reads in values from joystick movement and sends to paired device via serial bluetooth communication. 
   Uses:  Arduino Nano, Joystick, Joystick Breakout Board, HC-05 bluetooth module
   Author: Chloe Hulme
*/

const int HORIZ = 1; 
int horizontal;

void setup() {
  
  // Baud rate for serial Bluetooth communication.
  Serial.begin( 9600 );    
}

void loop() {
  
  // Joystick has a value range of 0-1023
  horizontal = analogRead(HORIZ); 

  // Paramaters that register joystick movement.
  if ( horizontal > 900 || horizontal < 100 )
  {
      Serial.println(String(horizontal));
  }

  delay(1000);
}
