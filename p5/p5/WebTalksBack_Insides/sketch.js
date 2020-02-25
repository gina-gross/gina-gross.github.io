var serial;                                 // variable to hold an instance of the serialport library
var portName = 'COM3'                       // rename to the name of your port
var dataarray = [];                         // some data coming in over serial!
var xPos = 0;                               // initialize variable for X position
var slider;                                 // add a slider component
var outData;                                // for data OUTPUT (to arduino)

function setup() {
  serial = new p5.SerialPort();             // make a new instance of the serialport library
  serial.on('list', printList);             // set a callback function for the serialport list event
  serial.on('connected', serverConnected);  // callback for connecting to the server
  serial.on('open', portOpen);              // callback for the port opening
  serial.on('data', serialEvent);           // callback for when new data arrives
  serial.on('error', serialError);          // callback for errors
  serial.on('close', portClose);            // callback for the port closing
 
  serial.list();                            // list the serial ports
  serial.open(portName);                    // open a serial port
  // set up the webpage
  createCanvas(1200, 800);                  
  background(0x08, 0x16, 0x40);

  // setup slider
  slider = createSlider(0, 255, 0);  // indicate the value range for slider
  slider.position(width/2 + (width/2-300)/2 , height-100);
  slider.style('width', '300px');
}
 
// get the list of ports:
function printList(portList) {
 // portList is an array of serial port names
 for (var i = 0; i < portList.length; i++) {
 // Display the list the console:
   print(i + " " + portList[i]);
 }
}

// This group of functions are for debugging.
function serverConnected() {
  print('connected to server.');
}
 
function portOpen() {
  print('the serial port opened.')
}
 
function serialError(err) {
  print('Something went wrong with the serial port. ' + err);
}
 
function portClose() {
  print('The serial port closed.');
}

// Here's what the page does upon a serial event.
function serialEvent() {
  if (serial.available()) {                 // If there's serial data,
    var datastring = serial.readLine();     // read it.
    var newarray; 
    try {
      newarray = JSON.parse(datastring);    // If we can parse the serial, load it into a temp array.
      } catch(err) {
          //console.log(err);
    }
    if (typeof(newarray) == 'object') {     
      dataarray = newarray;                 // Load the temp array into the array for serial data.
    }
    console.log("got back " + datastring);
  } 
}

function graphData(newData) {
  // map the range of the input to the window height:
  var yPos = map(newData, 0, 1023, 0, height);
  // draw the line
  line(xPos, height, xPos, height - yPos);
  // at the edge of the screen, go back to the beginning:
  if (xPos >= width) {
    xPos = 0;
    // clear the screen by resetting the background:
    background(0x08, 0x16, 0x40);
  } else {
    // pass
  }
}

function draw() {
  stroke('rgba(0,255,0,0.25)'); // green
  graphData(dataarray[0]);

  stroke('rgba(0,80,255,0.5)'); // blue
  graphData(dataarray[1]);
  xPos++;

  // slider
  var brightness = map(slider.value(), 0, 255, 0, 255);  // convert slider input to brightness
  fill(brightness);  // change visualization in p5
  rect(width/2,0,width/2,height);

  outData = brightness;  // setup the serial output
  serial.write(outData);  // write to serial for Arduino to pickup

  var textColor = map(brightness, 0, 255, 255, 0);  // draw the text
  fill(textColor);
  textSize(12);
  text("BRIGHTNESS LEVEL: " + brightness, 30, 30);
}
