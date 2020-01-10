/* 
 *  A1: Blink!
 *  
 *  Makes four LEDs blink in a "rainbow" pattern (Red, Yellow, Green, Blue).
 *  
 *  created 8 January 2020
 *  by Gina Gross
 *  for HCDE 439
 */

//the setup function runs once when you press reset or power the board
void setup() {
  // initialize pins
  pinMode(2, OUTPUT);     // initialize red LED to digital pin 2
  pinMode(4, OUTPUT);     // initialize yellow LED to digital pin 4
  pinMode(6, OUTPUT);     // initialize green LED to digital pin 6
  pinMode(8, OUTPUT);     // initialize blue LED to digital pin 8
}

// the loop function runs over and over again forever
void loop() {

  // red LED
  digitalWrite(2, HIGH);    // turn red LED on
  delay(250);               // wait 250 millisec
  digitalWrite(2, LOW);     // turn red LED off by making the voltage LOW
  delay(250);               // wait 250 millisec

  // yellow LED
  digitalWrite(4, HIGH);    // turn yellow LED on
  delay(250);               // wait "
  digitalWrite(4, LOW);     // turn yellow LED off
  delay(250);               // wait "

  // green LED
  digitalWrite(6, HIGH);    // turn green LED on
  delay(250);               // wait "
  digitalWrite(6, LOW);     // turn green LED off
  delay(250);               // wait "

  // blue LED
  digitalWrite(8, HIGH);    // turn blue LED on
  delay(250);               // wait "
  digitalWrite(8, LOW);     // turn blue LED off
  delay(250);               // wait "
}
