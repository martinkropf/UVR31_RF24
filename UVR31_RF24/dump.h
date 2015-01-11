/*  
 ~~~~~~~~~~
 UVR31_RF24
 ~~~~~~~~~~
 Martin Kropf 2015 
 
 dump.h:
 Data output via serial interface
 
 */

#ifdef DEBUG

namespace Dump {
  boolean active; // dump active?
  void start(); // output all data
  void bytes();
  void bits();
  void sensors(); // Sensoren
  void sensor();  // output of particular elements
}

#endif



