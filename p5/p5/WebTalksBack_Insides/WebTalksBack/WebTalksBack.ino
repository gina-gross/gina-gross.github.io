/* 
 *  A5 & A6: Talking to the Web / The Web Talks Back
 *  
 *  Created 2/24/20
 *  by Gina Gross
 *  for HCDE 439
 *  Modified from example code provided in class (in slides and on GitHub)
 *  Modified from example code on Medium: https://medium.com/@yyyyyyyuan/tutorial-serial-communication-with-arduino-and-p5-js-cd39b3ac10ce
 */

// This code runs once:
void setup() {
  Serial.begin(9600);             // Initialize serial communication
  Serial.setTimeout(10);          // Set the timeout for parseInt
  pinMode(5, OUTPUT);             // Initialize pin 5 (my LED) as OUTPUT
}

// After setup is finished, this code will run repeatedly:
void loop() {
  // This part talks to the web:
  int s1 = analogRead(1);                               // Pin corresponding to VRx on the joystick.
  int s2 = analogRead(2);                               // Pin corresponding to VRy on the joystick.
  // This code takes the input from the joystick and prints it
  // to the serial monitor, so that p5 can parse it:
  Serial.print("[");
  Serial.print(s1);
  Serial.print(",");
  Serial.print(s2);
  Serial.println("]");

  // This part has the web talk back:
  if (Serial.available() > 0) {                         // If there is serial data,
    int inByte = Serial.read();                         // read it,
    Serial.write(inByte);                               // and send it back out as raw binary data.
    int ledBrightness = map(inByte, 0, 255, 0, 255);    // Map the input value to the LED brightness.                         
    analogWrite(5, ledBrightness);                      // Write the brightness to the LED.  
  }
}
