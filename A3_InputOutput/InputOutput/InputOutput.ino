/* 
 *  A3: Input Output!
 *  
 *  Uses buttons and resistors to limit the current flowing through LEDs, causing them to fade.
 *  Each time you press the button, it turns on the circuit.
 *  
 *  Created 1/28/20
 *  by Gina Gross
 *  for HCDE 439
 *  Modified from code by MertArduino: https://www.instructables.com/id/Arduino-LDR-With-LED/ 
 *  Modified from example code on Sparkfun: https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/experiment-6-reading-a-photoresistor
 */

//Initializing variables, constants
const int led = 13;      // the pin that the LED is attached to
const int ldr = A0;    // the pin that the photoresistor is attached to

// setup code - this will run once
void setup() {
  Serial.begin(9600);       // initialize serial communication
  pinMode(led, OUTPUT);     // initialize LED as output
  pinMode(ldr, INPUT);    // initialize photoresistor as input
}

// this code will run repeatedly:
void loop() {
  // since the arduino can’t directly interpret resistance (rather, it reads voltage), we need to use a voltage divider to use our photoresistor. 
  // this voltage divider will output a high voltage (up to 255) when it is getting a lot of light and a low voltage (down to 0) when little or no light is present.
  
  int ldrStatus = analogRead(ldr);              // read the output of the voltage divider, aka, how much resistance is the photoresistor giving us?

  if (ldrStatus <= 300) {                       // if the photoresistor detects less than full light
    digitalWrite(led, HIGH);                    // turn the LED on
    Serial.println("LDR is DARK, LED is ON");   // write to the serial monitor
  }
  else {                                        // otherwise, if the photoresistor does detect light
    digitalWrite(led, LOW);                     // turn the LED off
    Serial.println("---------------");
  }
}
