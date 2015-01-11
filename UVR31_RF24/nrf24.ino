/*  
 ~~~~~~~~~~
 UVR31_RF24
 ~~~~~~~~~~
 Martin Kropf 2015 
 
 web.ino:
 Upload data frames via RF24
 
 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 9 & 10 
RF24 radio(9,10);

byte addresses[][10] = {"UVR2NRF24"};


#ifndef DEBUG

namespace NRF24 {
  void start() {   
  #ifdef USINGPC
    Serial.begin(115200);
    printf_begin();
  #endif
  // Setup and configure rf radio
  radio.begin();                          // Start up the radio
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.setRetries(15,15);                // Max delay between retries & number of retries
  radio.openWritingPipe(addresses[0]);
  #ifdef USINGPC
    radio.printDetails();                   // Dump the configuration of the rf unit for debugging
  #endif

  }

  void upload() {
    request="";
    sensors();
    //printf("Now sending: %s\n\r",request);
    char outBuffer[32]= "";
    request.toCharArray(outBuffer, 32);

    if (!radio.write( outBuffer, 32 )){  printf("failed.\n\r");  }
    // Try again 1s later
    delay(1000);
  }

  void sensors() {
    for (int i = 1; i <= 3; i++) {
      Process::fetch_sensor(i);
      sensor();
    }
    Process::fetch_output();
    request += Process::output;

    #ifdef USINGPC
      Serial.print(request);
    #endif
    //request = "";
  }

  // number&value*10&type&mode
  void sensor() {
    //request += Process::sensor.number;
    //CONCAT;
    if (Process::sensor.invalid)
      request += "-";
    else
      request += (int) (Process::sensor.value * 10);
    CONCAT;    
  }
}
#endif

