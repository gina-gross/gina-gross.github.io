/* 
 *  Final Project: Pet the Cat
 *  Stroke sensors sewn into a cat hat cause the ears to wiggle.
 *  
 *  Created 3/4/20
 *  by Gina Gross
 *  for HCDE 439
 *  Modified from my own code for an old DXArts class
  */


#include <Servo.h>                // Include the servo library to control the servo

Servo myservoL;                   // Create servo object to control the left servo 
                                  // A maximum of eight servo objects can be created 

Servo myservoR;                   // Create servo object to control the right servo  

int pos = 0;                      // Variable to store the servo position 

int statusPin = LED_BUILTIN;      // Set up a pin we are going to use to indicate our status using an LED.

const int sensorLeft = A1;        // The left stroke sensor is connected to pin A5
const int sensorRight = A2;       // The right stroke sensor is connected to pin A2

const int outputPinL = 5;         // Initializing pin 5 for output
const int outputPinR = 10;        // Initializing pin 10 for output

int sensorValL = 0;               // Initialize the sensor values
int sensorValR = 0;


// Put your setup code here, to run once:
void setup() {
  myservoL.attach(outputPinL);   // attaches the servo on pin 5 (the left servo) to the servo object
  myservoR.attach(outputPinR);   // attached the servo on pin 10 (the right servo) to the servo object
  
  // Begin by setting up the Serial Port so we can output our results.
  Serial.begin(9600);

  // Ready an LED to indicate our status.
  pinMode(LED_BUILTIN, OUTPUT);

  // We want the stroke sensors to ensure a known state for the signal, so we are initializing their pins as INPUT_PULLUP
  pinMode(sensorLeft, INPUT_PULLUP);
  pinMode(sensorRight, INPUT_PULLUP); 
}

// Put your main code here, to run repeatedly:
void loop() {

  // Read the values of the sensors and write them to the holding variables.
  sensorValL = analogRead(sensorLeft);
  sensorValR = analogRead(sensorRight);
  
  // Write these values to serial and wait very briefly before writing to the servos.
  Serial.println(sensorValL);
  Serial.println(sensorValR);
  delay(1);

  // Wiggle both ears at once

  if(sensorValL < 500 || sensorValR < 500) { 
    digitalWrite(LED_BUILTIN, HIGH);
    
    for (pos = 0; pos <= 180; pos += 1) {    // left ear goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservoL.write(pos);   // tell left servo to go to position in 'posL'
      myservoR.write(pos);   // tell right servo to go to position in 'posR'
      delay(10);              // wait 15ms for servo to reach position
    }
    for (pos = 180; pos >= 0; pos -= 1) {    // ears go from 180 to 0 degrees
      myservoL.write(pos);
      myservoR.write(pos);
      delay(10);
    }

// This is optional code for expanded functionality where stroking the left sensor triggers
// the left servo, and stroking the right sensor triggers the right servo. Currently trying to
// make this work caused more bugs than it was worth, so stroking the left sensor will trigger
// BOTH motors. I am keeping this code though so I still can work with it in the future.

 /* } if (sensorValR < 500) {
    for (posR = 0; posR <= 180; posR += 1) {    // right ear goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservoR.write(posR);   // tell servo to go to position in 'posL'
      delay(15);              // wait 15ms for servo to reach position
    }
    for (posR = 180; posR >= 0; posR -= 1) {    // right ear goes from 180 to 0 degrees
      myservoR.write(posR);
      delay(15);
    }
  } if (sensorValL < 500 && sensorValR < 500) {
     for (posR = 0; posR <= 180; posR += 1) {    // right ear goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservoR.write(posR);   // tell servo to go to position in 'posL'
      myservoL.write(posR);
      delay(15);              // wait 15ms for servo to reach position
    }
    for (posR = 180; posR >= 0; posR -= 1) {    // right ear goes from 180 to 0 degrees
      myservoR.write(posR);
      myservoL.write(posR);
      delay(15);
    } */
  // Now the code goes back to the else case for the left stroke sensor.  
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    
  }

}
