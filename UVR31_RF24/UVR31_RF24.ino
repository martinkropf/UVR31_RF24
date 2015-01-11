/*  
 ~~~~~~~~~~
 UVR31_RF24
 ~~~~~~~~~~
 Martin Kropf 2015 
 
 UVR31_RF24.ino:
 Phase change between receiving and processing
 
 */


// If DEBUG is defined all dump commands (dump.h/dump.ino) are compiled and 
// output occurs via Serial. If DEBUG is commented out, the web upload 
// (web.h/web.ino) is compiled and used instead. Both at once doesn't work
// (on the Leonardo) because the RAM storage is too small.

//#define DEBUG

// if USINGPC is defined, output is displayed on the Serial Monitor.
// Should be turned on if the Arduino is used on the PC,
// as soon as it is used with own power supply, you should comment it out.

//#define USINGPC

// adjust these values to your needs, for that remove the comments /*  */ (the values in the comments are examples)

const byte dataPin = 2; // pin with data stream
 // interrupt for data pin, see:
// http://arduino.cc/en/Reference/AttachInterrupt
const byte interrupt = 0;

// ======================

#include <SPI.h>

#include "receive.h"
#include "process.h"
#include "dump.h"
#include "NRF24.h"

void setup() {
#ifdef USINGPC
  Serial.begin(115200);
#endif
  // in DEBUG mode output via serial, otherwise web upload (see above)
#ifdef DEBUG
  Serial.println("Press key for detailed output.");
#else
  NRF24::start();  
#endif
  Receive::start();
}

void loop() {
  if (!Receive::receiving) {
    Process::start();  // process data
    Receive::start(); // receive data    
  }

#ifdef DEBUG
  if (Serial.available()) {
    while (Serial.available())
      Serial.read(); 
    if (Dump::active)
      Serial.println("\nDetails deactivated.");
    else
      Serial.println("\nDetails activated.");
    Dump::active = !Dump::active;
  }
#endif
}



