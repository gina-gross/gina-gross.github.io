/* 
 *  A4: Higher voltage and transistors!
 *  
 *  Created 2/15/20
 *  by Gina Gross
 *  for HCDE 439
 *  Modified from example code: http://www.circuitbasics.com/arduino-ir-remote-receiver-tutorial/
 */
 
#include <IRremote.h>                 // Include the IRRemote library.

// Initializing variables and constants
const int RECV_PIN = 6;               // The pin that the IR reciever breakout board is connected to.
                                      // I used an analog pin because I want to control the LED strip's output using analogWrite().
                                      // I'm not actually sure if the IR reciever needs to be on an analog pin for this, but for the sake of
                                      // simplicity and continuity I am connecting it to an analog pin, just like I will the LED strip.

IRrecv irrecv(RECV_PIN);              // For any IR communication using the IRremote library, we need to create an object called irrecv 
                                      // and specify the pin number where the IR receiver is connected (in this case, pin 6).
                                      // This object will take care of the protocol and processing of the information from the receiver.

decode_results results;               // Next we need to create a results object from the decode_results class, 
                                      // which will be used by the irrecv object to share the decoded information with our application. 

const int ledStrip = 10;              // The pin that the LED strip is connected to.

// Setup code - This code will run once.
void setup(){
  Serial.begin(9600);                 // Initialize serial communication.
  irrecv.enableIRIn();                // enableIRIn() is a member function of IRrecv. We are calling it to start the IR reciever.
  irrecv.blink13(true);               // This will blink the built-in LED on the Arduino board every time the reciever gets a signal from the remote control.
  pinMode(ledStrip, OUTPUT);          // Initialize the LED strip as output.
}

// After setup executes, this code will run repeatedly.
void loop(){
  if (irrecv.decode(&results)){       // irrecv.decode() will return 'true' if a code (signal from the remote) is recieved, and the 'if' statement will then be executed.
                                      // The recieved code will be stored in results.value.
      
      switch(results.value){          // Since I am only programming functionality to one button on the remote, I probably don't actually have to use switch/case
                                      // (as opposed to if I programmed several different buttons to do different things - I would absolutely need switch/case then),
                                      // but I am using it to keep this code efficient and allow the possibility for more cases/functionality to be added in the future.
                                      // For now, the switch block only handles one case, and that's the case of recieving the IR code for the remote's keypad button 5.
                                  
        case 0xFF38C7:                // Keypad button "5"
        Serial.println("5");          // Print "5" to the serial monitor.
        analogWrite(ledStrip, 255);   // Turn on the LED strip (HIGH).
        delay(2000);                  // Wait 2 seconds.
        digitalWrite(ledStrip, 0);    // Turn off the LED strip (LOW).
      }    
      
      irrecv.resume();                // This will reset the reciever and prepare it to recieve the next code.
  }
}
