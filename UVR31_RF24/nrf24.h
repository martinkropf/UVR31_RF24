/*  
 ~~~~~~~~~~
 UVR31_RF24
 ~~~~~~~~~~
 Martin Kropf 2015 
 
 web.h:
 Hochladen der Datenrahmen via NRF24L01
 Upload data frames to the internet via Ethernet
 
 */

#ifndef DEBUG

namespace NRF24 {

#define CONCAT request += "&"
  String request;
  void start(); // konfiguriere NRF24
  void upload(); // transfers a data frame to the server
  boolean working();  // waits for the termination of the upload process
  void sensors(); // Sensoren
  void sensor();
}

#endif

