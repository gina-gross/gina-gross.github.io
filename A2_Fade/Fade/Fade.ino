/* 
 *  A2: Fade!
 *  
 *  Uses buttons and resistors to limit the current flowing through LEDs, causing them to fade.
 *  Each time you press the button, it turns on the circuit.
 *  
 *  Created 1/13/20
 *  by Gina Gross
 *  for HCDE 439
 *  Modified from code by Shahir Nasar 
 *  "Simple RGB LED Light with Fade": https://create.arduino.cc/projecthub/SHAHIR_nasar/simple-rgb-led-light-with-fade-635bc2
 *  Modified from code by Muhammad Aqib 
 *  "Arduino Button Tutorial Using Arduino DigitalRead Function": https://create.arduino.cc/projecthub/muhammad-aqib/arduino-button-tutorial-using-arduino-digitalread-function-08adb5
 *  Modified from example code StateChangeDetection
 */
 
// Initializing variables and constants

// constants won't change. They're used here to set pin numbers:
const int rPin = 11;                // the pin that the red LED is attached to
const int gPin = 10;                // " green LED
const int bPin = 9;                 // " blue LED
const int ledPins[] = {11, 10, 9};  // an array for the pin numbers of the LEDs
const int pinCount = 3;             // the number of pins (i.e. length of the array)
const int buttonPin = 2;            // the pin that the pushbutton is attached to

// variables will change:
int rVal = 254;             // variable to hold the red LED value
int gVal = 1;               // " green LED value
int bVal = 127;             // " blue LED value
int rDir = -1;              // starting direction for red to fade
int gDir = 1;               // " for green
int bDir = -1;              // " for blue
int buttonPushCounter = 0;  // counter for the number of button presses
int buttonState = 0;        // current state of the button
int lastButtonState = 0;    // previous state of the button

// setup code - this will run once
void setup() {
  pinMode(buttonPin, INPUT); // initialize the button pin as input

  // I'm using the for loop to initialize my LEDs as outputs. I know, I know, that's
  // practically cheating. But the fade I want to do works better with if statements,
  // and if all I have to do is include a for loop somewhere in this code, I would
  // rather do this than convert the fading to for loops (which I have tried, and I
  // like this result the best; I know it can be done with for loops but I'd rather not
  // try to convert it if I can implement a for loop elsewhere).
  
  for (int thisPin = 0; thisPin < pinCount; thisPin ++) {    // the array elements are numbered from 0 to (pinCount - 1)
    pinMode(ledPins[thisPin], OUTPUT);
  }
  Serial.begin(9600);       // initialize serial communication
}

// this code will run repeatedly:
void loop() {
  buttonState = digitalRead(buttonPin);   // read the pushbutton input pin
  
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {            
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;                
      // Communicate to the serial monitor:
      Serial.println("on");
      Serial.println("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;

  // when you push the button, start the colors fading on the LED
  if (buttonState == HIGH) {

    analogWrite(rPin, rVal);
    analogWrite(gPin, gVal);
    analogWrite(bPin, bVal);

    //change the values of the LEDs
    rVal = rVal + rDir;
    gVal = gVal + gDir;
    bVal = bVal + bDir;

    // for each color, change direction if you reached 0 or 255
    if (rVal >= 255 || rVal <= 0) {
      rDir = rDir * -1;
    }

    if (gVal >= 255 || gVal <= 0) {
      gDir = gDir * -1;
    }

    if (bVal >= 255 || bVal <= 0) {
      bDir = bDir * -1;
    }

    // slight delay so it doesn't rotate color too quickly
    delay(33);
  } else {
    digitalWrite(rPin, LOW);
    digitalWrite(gPin, LOW);
    digitalWrite(bPin, LOW);
  }
}
